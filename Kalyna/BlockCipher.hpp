#ifndef _BLOCKCIPHER_H
#define _BLOCKCIPHER_H

#include "errands.hpp"
#include "s_box.hpp"
#include "s_row.hpp"
#include "xor_rkey.hpp"
#include "r_key.hpp"

void BlockEncrypt128128(uchar *state, uchar **rkey);

void BlockDecrypt128128(uchar *state, uchar **rkey);

#endif // !_BLOCKCIPHER_H
