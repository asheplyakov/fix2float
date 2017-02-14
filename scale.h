#ifndef SCALE_H
#define SCALE_H

/* @brief Convert a fixed point number to IEEE 754 double precision floating point one
 *
 * @param dwValue contains the binary representation of the fixed point number
 * @param iHighBit the binary representation starts at this bit
 * @param iBitCount the binary representation is this many bits long
 * @param dScale the weight of the most significant bit
 */
extern double FromScale(unsigned long dwValue, int iHighBit, int iBitCount, int iSigned, double dScale);

#endif /* SCALE_H */
