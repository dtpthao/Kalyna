#ifndef _M_COL_H
#define _M_COL_H

#include "errands.hpp"

#define POLYNOM 0x11D
#define M_POLY 8  //2^m
#define POW2m_POLY (1 << M_POLY)

uint8_t modPolynom(int w);

inline int coeff_mul(uint8_t uc, uint8_t coeff);
void MixColum(uint8_t *state, int len8);

inline int coeff_mul_inv(uint8_t uc, uint8_t coeff);
void MixColum_inv(uint8_t *state, int len8);

void TestMcol();

#endif // !_MIXCOLUM_H

