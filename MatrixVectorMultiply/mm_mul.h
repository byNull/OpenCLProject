#ifndef __MM_MUL_H__
#define __MM_MUL_H__

#pragma once

#ifdef __cplusplus
extern "C"{
#endif
void SpMV_NONE(char matrix[2048][2048], unsigned char vector[2048], int result[2048]);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"{
#endif
	void SpMV_SSE(char matrix[2048][2048], unsigned char vector[2048], int result[2048]);
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"{
#endif
	void SpMV_AVX(char matrix[2048][2048], unsigned char vector[2048], int result[2048]);
#ifdef __cplusplus
}
#endif


#endif