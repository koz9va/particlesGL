#include "Particles.cuh"
#include "cuda_runtime.h"
#include <device_launch_parameters.h>


#define gravity 9.8
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

	int i;
	unsigned int id;
	point_t *p;
	bool collided;
	id = blockIdx.x * blockDim.x + threadIdx.x;
	if(id < pAm) {
		p = points_d + id;
		switch (p->type) {
			case sand:
				for (i = 1; i < (int)p->speed/2 + 1; ++i) {

					if ((cells_d[ p->x + (p->y + i) * w] != -1) || (p->y + i) >= h - 3) {
						collided = true;
						break;
					}
				}

				if(i > 1 || (i == 1 && !collided)) {
					--i;
					cells_d[p->x + p->y * w ] = -1;
					cells_d[p->x + (p->y + i) * w] = (int)id;
					p->y += i;
					if(!collided && p->speed + p->velocity <= gravity) {
						p->speed += p->velocity;
					} else if(collided)
						p->speed = 1;
					return;
				}


				collided = false;
				for (i = 1; i < (int)p->speed/2 + 1; ++i) {
					if ((cells_d[(p->x + i) + (p->y + i) * w] != -1) || (p->y + i) >= h - 3 || (p->x + i) > w - 3) {
						collided = true;
						break;
					}
				}

				if(i > 1 || (i == 1 && !collided)) {
					--i;
					cells_d[p->x + p->y * w] = -1;
					cells_d[(p->x + i) + (p->y + i) * w] = (int)id;
					p->y += i;
					p->x += i;
					if(!collided && p->speed / 2.0 >= 1.0) {
						p->speed /= 1.25;
					} else
						p->speed = 1;
					return;
				}

				collided = false;
				for (i = 1; i < (int) p->speed/2 + 1; ++i) {
					if ((cells_d[(p->x - i) + (p->y + i) * w] != -1) || (p->y + i) >= h - 3 || (p->x - i) < 3) {
						collided = true;
						break;
					}
				}

				if(i > 1 || (i == 1 && !collided)) {
					--i;
					cells_d[p->x + p->y * w] = -1;
					cells_d[(p->x + i) + (p->y + i) * w] = (int)id;
					p->y += i;
					p->x -= i;
					if(!collided && p->speed / 2.0 <= 1.0) {
						p->speed /= 1.25;
					} else
						p->speed = 1;
					return;
				}
				break;
			case rock:
				return;
			case water:
				return;
		}
	}
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