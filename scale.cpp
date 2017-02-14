#include <limits.h> /* CHAR_BIT */

/**
 * @brief Convert a fixed point number to the IEEE 754 double precision floating point one
 *
 * @param val binary representation of the signed fixed point number
 * @param lb total length in bits of the fixed point number, including the sign bit
 * @param is_signed 1 if the number is signed, 0 otherwise
 * @param wmsb weight of the most significant bit
 * @return double precision IEEE floating point representation of the given fixed point number
 */
static double fix2fl(unsigned long uval, int lb, double wmsb, int is_signed) {
	/* assert(lb >= 2); */
	/* assert(lb <= sizeof(uval)*CHAR_BIT) */
	int sign = 1;
	unsigned long mask;
	if (is_signed) {
		sign = uval & (1ULL << (lb-1)) ? - 1 : 1;
		lb--;
	}
	mask = (1UL << lb) - 1UL;
	uval &= mask;
	/* 
	 * x = x_{fix} w_{lsb},
	 * where w_{lsb} is the weight of the *least* significant bit
	 * (typically w_{lsb} = 2^{-f}, where f is the bit length of
	 * the fractional part). By definition the number w_{msb} has
	 * the following binary representation: 1000...00, that is,
	 * the leading bit is 1, and the rest (l_b - 1) are zeros.
	 * Thus w_{msb} = 2^{l_b-1} w_{lsb}, or w_{lsb} = w_{msb}/2^{l_b-1}
	 *
	 * x = x_{fix} w_{msb}/2^{l_b-1}
	 */
	return ((double)uval)*(wmsb/(double)(1UL << (lb-1)))*sign;
}

double FromScale(unsigned long dwValue, int iHighBit, int iBitCount, int iSigned, double dScale) {
	/* assert(iBitCount >= iSigned ? 2 : 1); */
	if (iBitCount < (iSigned ? 2 : 1)) {
		/* no data, return 0 on invalid input according to the 5.3 of the spec */
		return 0.0;
	}

	/* assert(iBitCount <= sizeof(dwValue)*CHAR_BIT); */
	if (iBitCount > sizeof(dwValue)*CHAR_BIT) {
		/* overflow, return 0 on invalid input according to the spec 5.3 */
		return 0.0;
	}

	/* assert(iHighBit < sizeof(dwValue)*CHAR_BIT); */
	if (iHighBit >= sizeof(dwValue)*CHAR_BIT) {
		/* overflow, return 0 on invalid input according to the spec 5.3 */
		return 0.0;
	}

	/* assert(iHighBit+1 >= iBitCount); */
	if (iHighBit+1 < iBitCount) {
		/* underflow, return 0 on invalid input according to the spec 5.3 */
		return 0.0;
	}

	if (dScale == 0.0) {
		/* silly, but spec 5.2 requires this */
		dScale = (double)(1ULL << (iBitCount - (iSigned ? 2 : 1)));
	}
	
	/* skip extra bits at the left */
	dwValue >>= (iHighBit - iBitCount + 1);
	return fix2fl(dwValue, iBitCount, dScale, iSigned); 
}

