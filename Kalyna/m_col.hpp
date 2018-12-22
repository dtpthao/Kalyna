#ifndef _M_COL_H
#define _M_COL_H

#include "errands.hpp"

#define POLYNOM 0x11D
#define M_POLY 8  //2^m
#define POW2m_POLY (1 << M_POLY)

uchar modPolynom(int w);

inline int coeff_mul(uchar uc, uchar coeff);
void MixColum(uchar *state, int len8);

inline int coeff_mul_inv(uchar uc, uchar coeff);
void MixColum_inv(uchar *state, int len8);

void TestMcol();

#endif // !_MIXCOLUM_H

