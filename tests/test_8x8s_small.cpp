#include "scale.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	double wmsb = 64.0;
	unsigned long fixed = 0x8001; /* as 7.8  signed fixed point */
	/* (-1) * 2^{-8} */
	double expected = - 1.0/256;
	double actual = FromScale(fixed, 15, 16, 1, wmsb);
	if (expected != actual) {
		printf("%lu = %f != %f\n", fixed, actual, expected);
		return 1;
	}
	return 0;
}
