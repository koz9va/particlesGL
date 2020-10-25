
extern "C" {
	#include <cstdio>
	#include <cstdlib>
	#include <cmath>
	#include "../point.h"
};

namespace cu {
	extern "C" {
	void updateSand(point_t *points, int *cells, point_t *points_d, int *cells_d, int pAm, int w, int h, int updated);
	void AllocPointsAndCells(int w, int h, point_t **points_d, int **cells_d, point_t *points, int *cells, int pAm);
	void FreePointsAndCells(point_t *points_d, int *cells_d);
	}

}