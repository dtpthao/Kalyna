#include "OFBmode.hpp"

void OFB128128(uint8_t *src, unsigned int lenSrc, uint8_t *&dst)
{
	const int LEN8 = 16;
	dst = new uint8_t[lenSrc];
	uint8_t IV[LEN8] = { 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F },
		Key[LEN8] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F };

	uint8_t **rkey = new uint8_t*[11];
	for (int i = 0; i < 11; i++) rkey[i] = new uint8_t[16];
	GenRoundKeys128128(rkey, Key);

	int i, j, k,
		remBlock = lenSrc % LEN8,
		divBlock = lenSrc - remBlock;
	for (i = 0; i < divBlock; i += LEN8) {
		BlockEncrypt128128(IV, rkey);
		//printf("IV   %4d: ", i); printuc(IV, 16);
		//printf("block%4d: ", i);
		for (j = LEN8 - 1, k = i; j >= 0; j--, k++) {
			dst[k] = IV[j] ^ src[k];
			//printf("%02x", dst[k]);
		}
		//cout << endl;
	}
	BlockEncrypt128128(IV, rkey);
	//printf("IV   %4d: ", i); printuc(IV, 16);
	//printf("block%4d: ", i);
	for (j = remBlock - 1, k = i; j >= 0; j--, k++) {
		dst[k] = IV[j] ^ src[k];
		//printf("%02x", dst[k]);
	}
	//cout << endl;
}