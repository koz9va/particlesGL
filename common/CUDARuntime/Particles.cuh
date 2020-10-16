
extern "C" {
	#include <cstdio>
	#include <cstdlib>
	#include <cmath>
	#include "../point.h"
};

namespace cu {
	extern "C" {
	void updateSand(point_t *points, int *cells, point_t *points_d, int *cells_d, int pAm, int w, int h);
	void AllocPointsAndCells(int w, int h, point_t **points_d, int **cells_d);
	void FreePointsAndCells(point_t *points_d, int *cells_d);
	}

}