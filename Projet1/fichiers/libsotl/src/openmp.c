
#include "default_defines.h"
#include "global_definitions.h"
#include "device.h"
#include "openmp.h"
#include "sotl.h"

#ifdef HAVE_LIBGL
#include "vbo.h"
#endif

#include <stdio.h>

static int *atom_state = NULL;

#ifdef HAVE_LIBGL

#define SHOCK_PERIOD  50

// Colorier atome en fonction du numéro du thread
//
void color_atom(int n){
  int num_thread = atom_state[n];
  float ratio = (float) ((float) atom_state[n] / (float) omp_get_max_threads());
  switch(num_thread){
  case(0):
    // Blue
    vbo_color[n*3 + 0] = 0.0;
    vbo_color[n*3 + 1] = 0.0;
    vbo_color[n*3 + 2] = atom_color[0].B ;
    break;
  case(1):
    // Green
    vbo_color[n*3 + 0] = 0.0;
    vbo_color[n*3 + 1] = atom_color[0].G ;
    vbo_color[n*3 + 2] = 0.0;
    break;
  case(2):
    // Red
    vbo_color[n*3 + 0] = atom_color[0].R ;
    vbo_color[n*3 + 1] = 0.0;
    vbo_color[n*3 + 2] = 0.0;
    break;
  case(3):
    // Cyan
    vbo_color[n*3 + 0] = 0.0;
    vbo_color[n*3 + 1] = atom_color[0].G;
    vbo_color[n*3 + 2] = atom_color[0].B;
    break;
  case(4):
    // Violet
    vbo_color[n*3 + 0] = atom_color[0].R;
    vbo_color[n*3 + 1] = 0.0;
    vbo_color[n*3 + 2] = atom_color[0].B;
    break;
  case(5):
    // Yellow
    vbo_color[n*3 + 0] = atom_color[0].R;
    vbo_color[n*3 + 1] = atom_color[0].G;
    vbo_color[n*3 + 2] = 0.0;
    break;
  default:
    vbo_color[n*3 + 0] = (1.0 - ratio) * atom_color[0].R + ratio * 1.0;
    vbo_color[n*3 + 1] = (1.0 - ratio) * atom_color[0].G + ratio * 0.0;
    vbo_color[n*3 + 2] = (1.0 - ratio) * atom_color[0].B + ratio * 0.0;
    break;
  }
}
// Update OpenGL Vertex Buffer Object
//
static void omp_update_vbo (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
  sotl_domain_t *domain = &dev->domain;
#pragma omp parallel for //schedule(runtime)
  for (unsigned n = 0; n < set->natoms; n++) {
    vbo_vertex[n*3 + 0] = set->pos.x[n];
    vbo_vertex[n*3 + 1] = set->pos.y[n];
    vbo_vertex[n*3 + 2] = set->pos.z[n];

    // Atom color depends on z coordinate
    {
      //color_atom(n);
      float ratio = (set->pos.z[n] - domain->min_ext[2]) / (domain->max_ext[2] - domain->min_ext[2]);
      //float ratio = (float) ((float) atom_state[n] / (float) omp_get_max_threads());
      vbo_color[n*3 + 0] = (1.0 - ratio) * atom_color[0].R + ratio * 1.0;
      vbo_color[n*3 + 1] = (1.0 - ratio) * atom_color[0].G + ratio * 0.0;
      vbo_color[n*3 + 2] = (1.0 - ratio) * atom_color[0].B + ratio * 0.0;
      atom_state[n]--;
    }
  }
}
#endif

// Update positions of atoms by adding (dx, dy, dz)
//
static void omp_move (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
#pragma omp parallel for //schedule(runtime)
  for (unsigned n = 0; n < set->natoms; n++) {
    set->pos.x[n] += set->speed.dx[n];
    set->pos.y[n] += set->speed.dy[n];
    set->pos.z[n] += set->speed.dz[n];
  }
}

// Apply gravity force
//
static void omp_gravity (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
  const calc_t g = 0.005;
#pragma omp parallel for //schedule(runtime)
  for (unsigned n = 0; n < set->natoms; n++) {
    set->speed.dy[n] -= g;
  }
}

static void omp_bounce (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
  sotl_domain_t *domain = &dev->domain;
#pragma omp parallel for //schedule(runtime)
  for (unsigned n = 0; n < set->natoms; n++) {
    if (set->pos.x[n] < domain->min_ext[0] || set->pos.x[n] > domain->max_ext[0]){
      set->speed.dx[n] = -set->speed.dx[n];
      atom_state[n] = SHOCK_PERIOD;
    }
    if (set->pos.y[n] < domain->min_ext[1] || set->pos.y[n] > domain->max_ext[1]){
      set->speed.dy[n] = -set->speed.dy[n];
      atom_state[n] = SHOCK_PERIOD;
    }
    if (set->pos.z[n] < domain->min_ext[2] || set->pos.z[n] > domain->max_ext[2]){
      set->speed.dz[n] = -set->speed.dz[n];
      atom_state[n] = SHOCK_PERIOD;
    }
  }
}

static calc_t squared_distance (sotl_atom_set_t *set, unsigned p1, unsigned p2)
{
  calc_t *pos1 = set->pos.x + p1,
    *pos2 = set->pos.x + p2;

  calc_t dx = pos2[0] - pos1[0],
         dy = pos2[set->offset] - pos1[set->offset],
         dz = pos2[set->offset*2] - pos1[set->offset*2];

  return dx * dx + dy * dy + dz * dz;
}

static calc_t z_distance (sotl_atom_set_t *set, unsigned p1, unsigned p2)
{
  calc_t * pos1 = set->pos.x + p1,
    *  pos2 = set->pos.x + p2;
  calc_t dz = pos2[set->offset*2] - pos1[set->offset*2];
  return dz * dz;
}

static calc_t lennard_jones (calc_t r2)
{
  calc_t rr2 = 1.0 / r2;
  calc_t r6;
  
  r6 = LENNARD_SIGMA * LENNARD_SIGMA * rr2;
  r6 = r6 * r6 * r6;

  return 24 * LENNARD_EPSILON * rr2 * (2.0f * r6 * r6 - r6);
}

static void omp_force (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
#pragma omp parallel for  //schedule(runtime)
  for (unsigned current = 0; current < set->natoms; current++) {
    calc_t force[3] = { 0.0, 0.0, 0.0 };
    for (unsigned other = current-1; other < set->natoms; other--)
      {
	if (z_distance(set, current, other) > LENNARD_SQUARED_CUTOFF)
	  break;
	calc_t sq_dist = squared_distance (set, current, other);
	if (sq_dist < LENNARD_SQUARED_CUTOFF) {
	  calc_t intensity = lennard_jones (sq_dist);
	  calc_t * /*restrict*/ posx = set->pos.x ;
	  force[0] += intensity * (posx[current] - posx[other]);
	  force[1] += intensity * (posx[set->offset + current] -
				   posx[set->offset + other]);
	  force[2] += intensity * (posx[set->offset * 2 + current] -
				   posx[set->offset * 2 + other]);
	}
      }
    for (unsigned other = current + 1; other < set->natoms; other++)
      {
	if (z_distance(set, current, other) > LENNARD_SQUARED_CUTOFF)
	  break;
	calc_t sq_dist = squared_distance (set, current, other);
	if (sq_dist < LENNARD_SQUARED_CUTOFF) {
	  calc_t intensity = lennard_jones (sq_dist);
	  calc_t * /*restrict*/ posx = set->pos.x ;
	  force[0] += intensity * (posx[current] - posx[other]);
	  force[1] += intensity * (posx[set->offset + current] -
				   posx[set->offset + other]);
	  force[2] += intensity * (posx[set->offset * 2 + current] -
				   posx[set->offset * 2 + other]);
	}
      }
    set->speed.dx[current] += force[0];
    set->speed.dx[set->offset + current] += force[1];
    set->speed.dx[set->offset * 2 + current] += force[2];
    atom_state[current] = omp_get_thread_num();
  }
}

/* omp_force sans tri selon z, commenter aussi atom_set_sort dans omp_one_step_move */
/*
static void omp_force (sotl_device_t *dev)
{
  sotl_atom_set_t *set = &dev->atom_set;
#pragma omp parallel for     
  for (unsigned current = 0; current < set->natoms; current++) {
    calc_t force[3] = { 0.0, 0.0, 0.0 };

    for (unsigned other = 0; other < set->natoms; other++)
      if (current != other) {
	calc_t sq_dist = squared_distance (set, current, other);

	if (sq_dist < LENNARD_SQUARED_CUTOFF) {
	  calc_t intensity = lennard_jones (sq_dist);

	  force[0] += intensity * (set->pos.x[current] - set->pos.x[other]);
	  force[1] += intensity * (set->pos.x[set->offset + current] -
				   set->pos.x[set->offset + other]);
	  force[2] += intensity * (set->pos.x[set->offset * 2 + current] -
				   set->pos.x[set->offset * 2 + other]);
	}

      }

    set->speed.dx[current] += force[0];
    set->speed.dx[set->offset + current] += force[1];
    set->speed.dx[set->offset * 2 + current] += force[2];
  }
}
*/

// Main simulation function
//
void omp_one_step_move (sotl_device_t *dev)
{
  //  atom_set_sort(&dev->atom_set);
  // Apply gravity force
  //
  if (gravity_enabled)
    omp_gravity (dev);

  // Compute interactions between atoms
  //
  if (force_enabled)
    omp_force (dev);

  // Bounce on borders
  //
  if(borders_enabled)
    omp_bounce (dev);

  // Update positions
  //
  omp_move (dev);

#ifdef HAVE_LIBGL
  // Update OpenGL position
  //
  if (dev->display)
    omp_update_vbo (dev);
#endif
}

void omp_init (sotl_device_t *dev)
{
#ifdef _SPHERE_MODE_
  sotl_log(ERROR, "Sequential implementation does currently not support SPHERE_MODE\n");
  exit (1);
#endif

  borders_enabled = 1;
  
  dev->compute = SOTL_COMPUTE_OMP; // dummy op to avoid warning
}

void omp_alloc_buffers (sotl_device_t *dev)
{
  atom_state = calloc(dev->atom_set.natoms, sizeof(int));
  printf("natoms: %d\n", dev->atom_set.natoms);
}

void omp_finalize (sotl_device_t *dev)
{
  free(atom_state);

  dev->compute = SOTL_COMPUTE_OMP; // dummy op to avoid warning
}


