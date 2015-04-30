
__kernel void vecmul(__global float *vec,
		     __global float *res,
		     float k)
{
int index = get_global_id(0);

int nb_thread = get_num_groups(1) * get_num_groups(0);
int a = (get_global_id(0)+16) % nb_thread;
res[a] = vec[a] * k;

}
