#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g) {
	double imp0 = 377.0;
	int mm, nn;

	Type = tmZGrid;
	SizeX = 101;				// x size of domain	
	SizeY = 81;					// y size of domain
	MaxTime = 300;				// duration of simulation
	Cdtds = 1.0 / sqrt(2.0);	// Courant number

	g->hx = (double *)calloc((SizeX) * (SizeY - 1), sizeof(double));
	g->chxh = (double *)calloc((SizeX) * (SizeY - 1), sizeof(double));
	g->chxe = (double *)calloc((SizeX) * (SizeY - 1), sizeof(double));
	g->hy = (double *)calloc((SizeX - 1) * (SizeY), sizeof(double));
	g->chyh = (double *)calloc((SizeX - 1) * (SizeY), sizeof(double));
	g->chye = (double *)calloc((SizeX - 1) * (SizeY), sizeof(double));
	g->ez = (double *)calloc((SizeX) * (SizeY), sizeof(double));
	g->ceze = (double *)calloc((SizeX) * (SizeY), sizeof(double));
	g->cezh = (double *)calloc((SizeX) * (SizeY), sizeof(double));

	/* set electric-field update coefficients */
	for (mm = 0; mm < SizeX; mm++)
		for (nn = 0; nn < SizeY; nn++) {
			Ceze(mm, nn) = 1.0;
			Cezh(mm, nn) = Cdtds * imp0;
		}

	/* set magnetic-field update coefficients */
	for (mm = 0; mm < SizeX; mm++)
		for (nn = 0; nn < SizeY - 1; nn++) {
			Chxh(mm, nn) = 1.0;
			Chxe(mm, nn) = Cdtds / imp0;
		}

	for (mm = 0; mm < SizeX - 1; mm++)
		for (nn = 0; nn < SizeY; nn++) {
			Chyh(mm, nn) = 1.0;
			Chye(mm, nn) = Cdtds / imp0;
		}

	return;
}
