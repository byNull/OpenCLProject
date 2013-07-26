__kernel void matrixVectorMultiply (__global const char *mat, __global const unsigned char *vec, __global int *r, __global int* matWidth)
{

	int x = get_global_id(0);
	int y = get_global_id(1);
	int size = *matWidth;
#if 1
	int index = 0;
	int sum   = 0;
	
	index = x * size;
	for(int i = 0; i < size; i ++){
		short tmp = vec[i] * mat[index];
		sum += tmp;
		index += 1;
	}
	r[x] = sum;
#endif
  //  r[x] = size;
    
}
