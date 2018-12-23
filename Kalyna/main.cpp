#include "OFBmode.hpp"

void testBlockEncrypt128128()
{
	char sIV[33] = "101112131415161718191A1B1C1D1E1F";
	char sKey[33] = "000102030405060708090A0B0C0D0E0F";
	char sPt[33] = "11111111111111111111111111111111";
	uint8_t IV[16], IV2[16], Key[16], C[16], P1[16], Plaintext[16];
	hex2char(sIV, 16, IV);
	//hex2char(sIV, 16, IV2);
	hex2char(sKey, 16, Key);
	//hex2char(sPt, 16, Plaintext);

	uint8_t **rkey = new uint8_t*[11];
	for (int i = 0; i < 11; i++) rkey[i] = new uint8_t[16];
	GenRoundKeys128128(rkey, Key);

	cout << "Encrypt: " << endl;
	cout << "IV : "; printuc(IV, 16);
	cout << "Key: "; printuc(Key, 16);
	//cout << "P  : "; printuc(Plaintext, 16);
	BlockEncrypt128128(IV, rkey);
	cout << "IV1: "; printuc(IV, 16);
	//for (int i = 0; i < 16; i++) {
	//	C[i] = IV[i] ^ Plaintext[i];
	//}
	//cout << "C  : "; printuc(C, 16);
	cout << endl << endl;

	cout << "Decrypt: " << endl;
	cout << "IV1: "; printuc(IV, 16);
	cout << "Key: "; printuc(Key, 16);
	//cout << "C  : "; printuc(C, 16);
	BlockDecrypt128128(IV, rkey); //BlockDecrypt128128(IV2, rkey);
	cout << "IV2: "; printuc(IV, 16);
	//for (int i = 0; i < 16; i++) {
	//	P1[i] = IV[i] ^ C[i];
	//}
	//cout << "P1 : "; printuc(P1, 16);
	//cout << "P  : "; printuc(Plaintext, 16);
	cout << "IV : " << sIV << endl;
}

void testOFB()
{
	uint8_t *M = new uint8_t[1];
	uint8_t *C = new uint8_t[1];
	uint8_t *M1 = new uint8_t[1];
	uint8_t *C1 = new uint8_t[1];

	cout << "Encrypt: " << endl;
	int lenM = readFile(M, "Plaintext.txt");
	cout << "lenM: " << lenM << endl;
	cout << "M : "; 
	cout << M << endl << endl;
	OFB128128(M, lenM, C);
	cout << "==>C : "; printuc(C, lenM);
	write2File(C, lenM, "Ciphertext.txt");
	cout << endl << endl;

	cout << "Decrypt: " << endl;
	int lenC = readFile(C1, "Ciphertext.txt");
	cout << "lenC: " << dec << lenC << endl;
	cout << "C1: "; printuc(C1, lenC); cout << endl;
	OFB128128(C1, lenC, M1);
	cout << "==>M1: ";
	cout << M1 << endl << endl;
}

int main() 
{
	//cout << (int)modPolynom(512) << endl;
	//TestMcol();
	//testAddSubrKey();

	//testGenInterKey2();
	//testGenInterKey();
	//cout << endl << endl;
	//testGenRoundKeys();
	//cout << endl << endl;
	//testGenRoundKeys2();

	//testBlockEncrypt128128();

	testOFB();

	system("pause");
	return 0;
}
