/* TMz simulation with a TFSF boundary and a second-order ABC. */

#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h"
#include "fdtd-proto2.h"

int main()
{
	Grid *g;

	g = (Grid *)calloc(1, sizeof(Grid));
	gridInit(g);	// initialize 2D grid

	abcInit(g);	// initialize ABC
	tfsfInit(g);	// initialize TFSF boundary
	snapshotInit2d(g);	// initialize snapshots

	/* do time stepping */
	for (Time = 0; Time < MaxTime; Time++) {
		updateH2d(g);	// update magnetic fields
		tfsfUpdate(g);	// apply TFSF boundary
		updateE2d(g);	// update electric fields
		abc(g);	// apply ABC
		snapshot2d(g);	// take a snapshot (if appropriate)
	} // end of time-stepping

	return 0;
}
