
__kernel void swap(__global float *vec,
			__global float *res)
{
  int index = get_global_id(0);

  res[SIZE - index - 1] = vec[index];
}
