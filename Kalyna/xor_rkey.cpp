#include "xor_rkey.hpp"


void XorKey(uchar *state, int len8, uchar *key) {

	for (int i = 0; i < 16; i++) {
		state[i] ^= key[i];
	}
}