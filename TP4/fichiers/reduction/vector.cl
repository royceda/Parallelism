__kernel void reduction(__global float *vec,
				int debut,
				int fin)
{

__local float tmp[TILE];

/*
const int index = fin + get_group_id(0);
const int index_th = get_local_id(get_group_id(0));

const int sum = vec[index_th];

vec[index] += sum;
 */

/* la IV
 uint global_id = get_global_id(0); //ou lire
 uint global_size = get_global_size(0); //utilisee poursavoir ou lire
 uint local_id = get_local_id(0); //ou lire et ecrire dans la memoire local
 uint group_size = get_local_size(0); //calcul initiale
 
 //transfert memoire global => memoire local
 //tmp[local_id] = vec[global_id] + vec[global_id + global_size];
 
 barrier(CLK_LOCAL_MEM_FENCE);

 //for(uint stride = debut; stride<fin; stride++){
 for(uint stride=group_size/2; stride>1; stride>>=1){ //>>=1 similaire à /=2
   //les premieres cases lisent de la seconde
   if(local_id < stride)
     tmp[local_id] += tmp[local_id + stride];
   //synchro
   barrier(CLK_LOCAL_MEM_FENCE);
 }
 //derniere iteration on ecrit le resultat a la n-eme position dans global vec
 
 if(local_id == 0)
   vec[fin+get_group_id(0)] = tmp[0] +tmp[1]; 
*/


// la II
tmp[get_local_id(0)] = vec[get_global_id(0)];
 barrier(CLK_LOCAL_MEM_FENCE);

 if(get_local_id(0) == 0){
   float group_sum = tmp[0];
   for(int i=1; i<get_local_size(0); i++)
     group_sum += tmp[i];
      
   vec[fin+get_group_id(0)] = group_sum;
 }
 
}
