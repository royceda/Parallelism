__kernel void reduction(__global float *vec,
				int debut,
				int fin)
{
	__local float tmp[TILE];

const int index = fin + get_group_id(0);

const int sum = vec[debut];

vec[index] += sum;

}
