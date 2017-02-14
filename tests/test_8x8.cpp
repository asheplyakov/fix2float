#include "scale.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	double wmsb = 128;
	unsigned long fixed = 0xffffUL; /* as 8.8 unsigned fixed point */
	/* 2^7 + 2^6 + ... + 2 + 1 + 2^{-1} + ... + 2^{-8} = 255 + (255/256) = 256 - 1/256 */
	double expected = 256.0 - 1.0/256;
	double actual = FromScale(fixed, 15, 16, 0, wmsb);
	if (expected != actual) {
		printf("Error: %lu = %f != %f\n", fixed, actual, expected);
		return 1;
	}
	return 0;
}

