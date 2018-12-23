#include "BlockCipher.hpp"

void BlockEncrypt128128(uint8_t *state, uint8_t **rkey)
{
	const int len8 = 16;
	AddrKey(state, len8, state, rkey[0]);
	//cout << "addrKey: "; printuc(state, len8);
	for (int i = 1; i < 10; i++) {
		SubBytes(state, len8, s_box, state);
		//cout << "s_box  : "; printuc(state, len8);
		ShiftRow(state, len8);
		//cout << "s_row  : "; printuc(state, len8);
		MixColum(state, len8);
		//cout << "m_col  : "; printuc(state, len8);
		XorKey(state, len8, rkey[i]);
		//cout << "xorKey : "; printuc(state, len8);
	}
	SubBytes(state, len8, s_box, state);
	//cout << "s_box  : "; printuc(state, len8);
	ShiftRow(state, len8);
	//cout << "s_row  : "; printuc(state, len8);
	MixColum(state, len8);
	//cout << "m_col  : "; printuc(state, len8);
	AddrKey(state, len8, state, rkey[10]);
	//cout << "addrKey: "; printuc(state, len8);
}

void BlockDecrypt128128(uint8_t *state, uint8_t **rkey)
{
	//uint8_t rkey[11][16];
	int len8 = 16;
	SubrKey(state, len8, state, rkey[10]);
	//cout << "sudrKey : "; printuc(state, len8);
	MixColum_inv(state, len8);
	//cout << "invm_col: "; printuc(state, len8);
	ShiftRow(state, len8);
	//cout << "invs_row: "; printuc(state, len8);
	SubBytes(state, len8, s_box_inv, state);
	//cout << "invs_box: "; printuc(state, len8);
	for (int i = 9; i > 0; i--) {
		XorKey(state, len8, rkey[i]);
		//cout << "xorKey  : "; printuc(state, len8);
		MixColum_inv(state, len8);
		//cout << "invm_col: "; printuc(state, len8);
		ShiftRow(state, len8);
		//cout << "invs_row: "; printuc(state, len8);
		SubBytes(state, len8, s_box_inv, state);
		//cout << "invs_box: "; printuc(state, len8);
	}
	SubrKey(state, len8, state, rkey[0]);
	//cout << "sudrKey : "; printuc(state, len8);
}



