#include "xor_rkey.hpp"


void XorKey(uint8_t *state, int len8, uint8_t *key) {

	for (int i = 0; i < 16; i++) {
		state[i] ^= key[i];
	}
}