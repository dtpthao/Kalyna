#include "s_row.hpp"

//when l = 128, shiftrow == shiftrow_inv, others case will be added later
void ShiftRow(uint8_t *state, int len8) 
{
	uint8_t tmp;
	switch (len8) {
	case 16:	
		for (int i = 4; i < 8; i++) {
			tmp = state[i];
			state[i] = state[i + 8];
			state[i + 8] = tmp;
		}
		return;
	case 32:
		for (int i = 2; i < 8; i += 2) {
			for (int j = i; j < 8; j++) {
				tmp = state[24 + j];
				for (int k = 24 + j; k > 8; k -= 8) {
					state[k] = state[k - 8];
				}
				state[j] = tmp;
			}
		}
		return;
	case 64: return;	//others case will be added later
	}
}

void ShiftRow_inv(uint8_t *state, int len8)
{
	uint8_t tmp;
	switch (len8) {
	case 16:
		for (int i = 4; i < 8; i++) {
			tmp = state[i];
			state[i] = state[i + 8];
			state[i + 8] = tmp;
		}
		return;
	case 32:
		for (int i = 2; i < 8; i += 2) {
			for (int j = i; j < 8; j++) {
				tmp = state[24 + j];
				for (int k = 24 + j; k > 8; k -= 8) {
					state[k] = state[k - 8];
				}
				state[j] = tmp;
			}
		}
		return;
	case 64: return;
	}
}

void ShiftRow256(uint8_t *state) 
{
	uint8_t tmp;
	
}