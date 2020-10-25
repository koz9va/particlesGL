#include "Particles.cuh"
#include "cuda_runtime.h"
#include <device_launch_parameters.h>


#define _SIZE_T_DEFINED
#ifndef __CUDACC__
#define __CUDACC__
#endif
#ifndef __cplusplus
#define __cplusplus
#endif
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}
__global__ void Sand_kernel(point_t *points_d, int *cells_d, int pAm, int w, int h) {

	int id;
	point_t *p;

	id = blockIdx.x * blockDim.x + threadIdx.x;

	if(id < pAm) {
		p = points_d + id;
		if(p->y + 2 > h)
			return;

		if(cells_d[w * p->x + (p->y + 1)] == -1) {
			cells_d[w * p->x + p->y] = -1;
			cells_d[w * p->x + (p->y + 1)] = id;
			++p->y;
			return;
		}
		if( (p->x < w && cells_d[w * (p->x + 1) + (p->y + 1)] == -1) ) {
			cells_d[w * p->x + p->y] = -1;
			cells_d[w * (p->x + 1) + (p->y + 1)] = id;
			++p->x;
			++p->y;
			return;
		}
		if(p->x > 0 && cells_d[w * (p->x - 1) + (p->y + 1)] == -1) {
			cells_d[w * p->x + p->y] = -1;
			cells_d[w * (p->x - 1) + (p->y + 1)] = id;
			--p->x;
			++p->y;
			return;
		}

	}
	//@todo implement sand velocity and call this shit from updateSand();
}

namespace cu {
	constexpr int blockSize = 256;
	extern "C"{
	void updateSand(point_t *points, int *cells, point_t *points_d, int *cells_d, int pAm, int w, int h, int updated)
		{
		int NumOfBlocks;
		if(updated == 1) {
			cudaMemcpy(points_d, points, sizeof(point_t) * pAm, cudaMemcpyHostToDevice);
			cudaMemcpy(cells_d, cells, sizeof(int) * w * h, cudaMemcpyHostToDevice);
		}
		NumOfBlocks = (int)((double)pAm/(double)blockSize) + 1;

		Sand_kernel<<<NumOfBlocks, blockSize>>>(points_d, cells_d, pAm, w, h);

		cudaMemcpy(points, points_d, sizeof(point_t) * pAm, cudaMemcpyDeviceToHost);
		cudaMemcpy(cells, cells_d, sizeof(int) * w * h, cudaMemcpyDeviceToHost);

		}
	void AllocPointsAndCells(int w, int h, point_t **points_d, int **cells_d, point_t *points, int *cells, int pAm) {
		cudaMalloc(points_d, sizeof(point_t) * w * h);
		cudaMalloc(cells_d, sizeof(int) * w * h);

	}
	void FreePointsAndCells(point_t *points_d, int *cells_d) {
		cudaFree(points_d);
		cudaFree(cells_d);
	}
	}
}