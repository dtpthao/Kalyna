#ifndef _BLOCKCIPHER_H
#define _BLOCKCIPHER_H

#include "errands.hpp"
#include "s_box.hpp"
#include "s_row.hpp"
#include "xor_rkey.hpp"
#include "r_key.hpp"

void BlockEncrypt128128(uint8_t *state, uint8_t **rkey);

void BlockDecrypt128128(uint8_t *state, uint8_t **rkey);

#endif // !_BLOCKCIPHER_H
