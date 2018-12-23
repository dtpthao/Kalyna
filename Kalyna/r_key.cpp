#include "r_key.hpp"

//Function of addition modulo 2**64
//note: less significant bytes have smaller indexes
void AddrKey(uint8_t *dst, int len, uint8_t *src1, uint8_t *src2)
{
	int rem = 0, tmp;
	for (int i = 0; i < len; i += 8, rem = 0) {
		for (int j = i, k = i + 8; j < k; j++) {
			tmp = src1[j] + src2[j] + rem;
			dst[j] = tmp & 0xff;
			rem = tmp >> 8;
		}
	}
}

//Function of subtraction modulo 2**64
//note: less significant bytes have smaller indexes
void SubrKey(uint8_t *dst, int len, uint8_t *src1, uint8_t *src2)
{
	int rem = 0, tmp;
	for (int i = 0; i < len; i += 8, rem = 0) {
		for (int j = i, k = i + 8; j < k; j++) {
			tmp = src1[j] - src2[j] + rem;
			rem = tmp >> 31;		// if tmp < 0 ==> rem = -1
			if (rem) tmp += 0x100;
			dst[j] = tmp & 0xff;
		}
	}
}

inline void copymasuc(uint8_t *src, int begin, int end, uint8_t *dst)
{
	for (int i = begin, j = 0; i < end; i++) {
		dst[j++] = src[i];
	}
}

void GenInterKey(uint8_t *state, int len8, uint8_t *Lk, uint8_t *Rk)
{
	AddrKey(state, len8, Lk, state);
	//cout << "AddrKey:  "; printuc(state, len8);
	SubBytes(state, len8, s_box, state);
	//cout << "SubBytes: "; printuc(state, len8);
	ShiftRow(state, len8);
	//cout << "ShiftRow: "; printuc(state, len8);
	MixColum(state, len8);
	////cout << "MixColum: "; printuc(state, len8);
	XorKey(state, len8, Rk);
	//cout << "XorKey:   "; printuc(state, len8);
	SubBytes(state, len8, s_box, state);
	//cout << "SubBytes: "; printuc(state, len8);
	ShiftRow(state, len8);
	//cout << "ShiftRow: "; printuc(state, len8);
	MixColum(state, len8);
	//cout << "MixColum: "; printuc(state, len8);
	AddrKey(state, len8, Lk, state);
	//cout << "AddrKey:  "; printuc(state, len8);
	SubBytes(state, len8, s_box, state);
	//cout << "SubBytes: "; printuc(state, len8);
	ShiftRow(state, len8);
	//cout << "ShiftRow: "; printuc(state, len8);
	MixColum(state, len8);
	//cout << "MixColum: "; printuc(state, len8);
}

void rotateR8x(uint8_t *src, unsigned int len8, int val, uint8_t *dst)
{
	int sft = (val >> 3) & 0xF;
	if (!sft) {
		for (int i = 0; i < len8; i++)
			dst[i] = src[i];
		return;
	}
	uint8_t *tmp = new uint8_t[sft];
	for (int i = len8 - sft, j = 0; i < len8; i++)
		tmp[j++] = src[i];
	for (int i = len8 - 1; i >= sft; i--)
		dst[i] = src[i - sft];
	for (int i = 0; i < sft; i++)
		dst[i] = tmp[i];
}

void rotateL8x(uint8_t *src, unsigned int len8, int val, uint8_t *dst)
{
	int sft = (val >> 3) & 0xF;
	if (!sft) {
		for (int i = 0; i < len8; i++)
			dst[i] = src[i];
		return;
	}
	uint8_t *tmp = new uint8_t[sft];
	for (int i = 0; i < sft; i++)
		tmp[i] = src[i];
	for (int i = 0; i < len8 - sft; i++)
		dst[i] = src[i + sft];
	for (int i = len8 - sft, j = 0; i < len8; i++)
		dst[i] = tmp[j++];
}

void evenKeys(uint8_t *IK, int len8, uint8_t *tmv, uint8_t *rkey)
{
	uint8_t * fiIK = new uint8_t[len8];
	//cout << "v<<i/2:  "; printuc(tmv, len8);
	AddrKey(fiIK, len8, tmv, IK);		//fi(IntermediateKey) = AddroundKey IK with (v << i/2)
	//cout << "fiIK: "; printuc(fiIK, len8);

	AddrKey(rkey, len8, fiIK, rkey);
	//cout << "1. addid:   "; printuc(rkey, len8);
	SubBytes(rkey, len8, s_box, rkey);
	//cout << "2. s_box:   "; printuc(rkey, len8);
	ShiftRow(rkey, len8);
	//cout << "3. s_row:   "; printuc(rkey, len8);
	MixColum(rkey, len8);
	//cout << "4. m_col:   "; printuc(rkey, len8);
	XorKey(rkey, len8, fiIK);
	//cout << "5. xorkey:  "; printuc(rkey, len8);
	SubBytes(rkey, len8, s_box, rkey);
	//cout << "6. s_box:   "; printuc(rkey, len8);
	ShiftRow(rkey, len8);
	//cout << "7. s_row:   "; printuc(rkey, len8);
	MixColum(rkey, len8);
	//cout << "8. m_col:   "; printuc(rkey, len8);
	//cout << "fiIK:       "; printuc(fiIK, len8);
	AddrKey(rkey, len8, fiIK, rkey);
	//cout << "9. addfiIK: "; printuc(rkey, len8);
}

void oddKeys(uint8_t *erkey, int len8, uint8_t *orkey) {
	//copymasuc(erkey, 0, l >> 3, orkey);
	rotateL8x(erkey, len8, (len8 << 1) + 24, orkey);
}


//src and dst can be the same
void lsft(uint8_t *src, int val, uint8_t *dst)
{
	int tmp, rem = 0;
	for (int i = 15; i >= 0; i--) {
		tmp = src[i] << val;
		dst[i] = tmp & 0xFF + rem;
		rem = tmp >> 8;
	}
}

void lsft(uint8_t *src, uint8_t *dst)
{
	int tmp, rem = 0;
	for (int i = 15; i >= 0; i--) {
		tmp = src[i] << 1;
		dst[i] = tmp & 0xFF + rem;
		rem = tmp >> 8;
	}
}

void GenRoundKeys128128(uint8_t **roundKey, uint8_t * Key)
{
#ifndef BSIZE
#define BSIZE 128
#define KSIZE 128
#define BSIZE8 16
#define KSIZE8 16
#define ODDSFT (BSIZE8 << 1) + 24
	uint8_t IK[BSIZE8] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	GenInterKey(IK, BSIZE8, Key, Key);

	uint8_t v[BSIZE8] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	//cout << "v :  "; printuc(v, BSIZE8);
	
	copymasuc(Key, 0, BSIZE8, roundKey[0]);
	//cout << "rkey:    "; printuc(roundKey[0], BSIZE8);
	//cout << "rotate:  "; printuc(roundKey[0], BSIZE8);
	evenKeys(IK, BSIZE8, v, roundKey[0]);
	//cout << endl << endl;
	for (int i = 1; i < 10; i++) {
		////oddKeys(roundKey[i - 1], BSIZE8, roundKey[i]);
		rotateL8x(roundKey[i - 1], BSIZE8, ODDSFT, roundKey[i]); //odd keys
		//cout << i + 1 << ". " << endl;
		lsft(v, v);
		//copymasuc(Key, 0, BSIZE8, roundKey[++i]);		//rKey0 = Key
		//cout << i << ". " << endl << "rkey:    "; printuc(roundKey[i], 16);
		rotateR8x(Key, BSIZE8, i << 5, roundKey[++i]);	//cSftKey = Key >>> 32*i
		//cout << "rotate:  "; printuc(roundKey[i], BSIZE8);
		evenKeys(IK, BSIZE8, v, roundKey[i]);
		//cout << endl << endl;
	}
#endif // !l
}

void GenRoundKeys128256(uint8_t roundKey[15][16], uint8_t *Key)
{
#ifdef BSIZE
#define BSIZE 128
#define KSIZE 256
#define BSIZE8 16
#define KSIZE8 32
	uint8_t IK[BSIZE8] = { 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t Rk[BSIZE8], Lk[BSIZE8], Key2[KSIZE8], Ktmp[KSIZE8];
	copymasuc(Key, 0, KSIZE8, Key2);
	copymasuc(Key, 0, BSIZE8, Lk);
	copymasuc(Key, BSIZE8, KSIZE8, Rk);
	cout << "IK: "; printuc(IK, BSIZE8);
	cout << "Lk: "; printuc(Lk, BSIZE8);
	cout << "Rk: "; printuc(Rk, BSIZE8);
	cout << endl << endl;
	GenInterKey(IK, BSIZE8, Lk, Rk);

	uint8_t v[BSIZE8] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	cout << "v :  "; printuc(v, BSIZE8);
	
	copymasuc(Lk, 0, BSIZE8, roundKey[0]);
	evenKeys(IK, BSIZE8, v, roundKey[0]);
	oddKeys(roundKey[0], BSIZE8, roundKey[1]);
	lsft(v, v);
	copymasuc(Rk, 0, BSIZE8, roundKey[2]);
	evenKeys(IK, BSIZE8, v, roundKey[2]);

	for (int i = 3, j = 1; i < 15; i++, j++) {
		oddKeys(roundKey[i - 1], BSIZE8, roundKey[i]);

		cout << ++i << ". " << endl;
		lsft(v, v);
		rotateR8x(Key2, KSIZE8, i << 4, Ktmp);	//rotate = Lk(Key >>> 16*i)
		cout << "rotate:  "; printuc(Ktmp, KSIZE8);
		copymasuc(Ktmp, 0, BSIZE8, roundKey[i]);
		cout << "Lk    :  "; printuc(roundKey[i], BSIZE8);
		evenKeys(IK, BSIZE8, v, roundKey[i]);
		cout << endl;

		i++;
		oddKeys(roundKey[i - 1], BSIZE8, roundKey[i]);

		cout << ++i << ". " << endl;
		lsft(v, v);
		rotateR8x(Key, KSIZE8, (i/4) << 6, Ktmp);	//rotate = Rk(Key >>> 32*[i/4])
		cout << "rotate:  "; printuc(Ktmp, KSIZE8);
		copymasuc(Ktmp, BSIZE8, KSIZE8, roundKey[i]);
		cout << "Rk    :  "; printuc(roundKey[i], BSIZE8);
		evenKeys(IK, BSIZE8, v, roundKey[i]);
		
		cout << endl << endl;
	}
#endif // !l
}

void testAddSubrKey()
{
	char sM[4][33] = { "101112131415161718191A1B1C1D1E1F",
						"2A996BD4E2BFE707EBBDF763CBFA64A5",
						"202122232425262728292A2B2C2D2E2F",
						"95CD566091D32765B72653E17180F381"};
	char sRk[4][33] = { "16505E6B9B3AB1E6865B77DCE082A0F4",
						"B8AA879A2086A66DD80A9872E25CD2B0",
						"57C816EB3F7E12DEED2C6B56E6B5BE1A",
						"2BBFF92FF9794546B343FADB28A0D1D4" };
	char sC[4][33] = { "2661707EAF4FC7FD9E7491F7FC9FBE13",
						"81BF1C7D779BAC20E1C9EA39B4D2AD06",
						"77E9380E64A338051556958112E3EC49",
						"58EC3E091000158A1148F7166F334F14" };
	uint8_t M[4][16], rK[4][16], C[4][16] , M1[4][16];
	
	for (int i = 0; i < 4; i++) {
		hex2char(sM[i], 16, M[i]);
		cout << "M : "; printuc(M[i], 16);
		hex2char(sRk[i], 16, rK[i]);
		cout << "rK: "; printuc(rK[i], 16);
		AddrKey(C[i], 16, M[i], rK[i]);
		cout << "C : "; printuc(C[i], 16);
		cout << "C : " << sC[i] << endl;
		SubrKey(M1[i], 16, C[i], rK[i]);
		cout << "M1: "; printuc(M1[i], 16);
		cout << "M : "; printuc(M[i], 16);
		cout << endl;
	}
}

//when block size = key size
void testGenInterKey()
{
	uint8_t state[16] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t Key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
						0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
	cout << "state: "; printuc(state, 16);
	cout << "Key  : "; printuc(Key, 16);
	cout << endl;
	GenInterKey(state, 16, Key, Key);
	cout << endl;
	cout << "Intermediate Key: "; printuc(state, 16);
}

//when block size = 1/2 key size
void testGenInterKey2()
{
	char sstate[33] = "07000000000000000000000000000000";
	char skey[65] = "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F";
	uint8_t state[16];
	uint8_t Key[32];
	hex2char(sstate, 16, state);
	hex2char(skey, 32, Key);
	cout << "State: "; printuc(state, 16);
	cout << "Key  : "; printuc(Key, 32);
	uint8_t Rk[16], Lk[16];
	copymasuc(Key, 0, 16, Lk);
	copymasuc(Key, 16, 32, Rk);
	/*for (int i = 16, j = 0; i < 32;)
		Rk[j++] = Key[i++];*/
	//cout << endl << endl;
	cout << "Lk: "; printuc(Lk, 16);
	cout << "Rk: "; printuc(Rk, 16);
	GenInterKey(state, 16, Lk, Rk);
}

void testGenRoundKeys()
{
	uint8_t **rkey = new uint8_t*[11];
	for (int i = 0; i < 11; i++) rkey[i] = new uint8_t[16];
	uint8_t Key[16];
	char sKey[33] = "000102030405060708090A0B0C0D0E0F";
	hex2char(sKey, 16, Key);
	cout << "Key: "; printuc(Key, 16);
	GenRoundKeys128128(rkey, Key);
	for (int i = 0; i < 11; i++) {
		cout << "k" << i << ": "; printuc(rkey[i], 16);
	}
}

void testGenRoundKeys2()
{
	uint8_t roundKey[15][16] = { 0 };
	uint8_t Key[32];
	char sKey[65] = "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F";
	hex2char(sKey, 32, Key);
	GenRoundKeys128256(roundKey, Key);
	for (int i = 0; i < 15; i++) {
		cout << "k" << i << ": "; printuc(roundKey[i], 16);
	}
}

