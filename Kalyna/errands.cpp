#include "errands.hpp"

void printuc(uchar *Src, int len) {
	for (int i = 0; i < len; i++) {
		cout << hex << setw(2) << setfill('0') << uppercase << (int)Src[i];
	}
	cout << endl;
}

void hex2char(char *src, int len, uchar *dst) {

	//int len = strlen(src) / 2;
	//uchar *dst = new uchar[len + 1];
	for (int i = 0, j = 0; j < len; i += 2, j++) {
		dst[j] = (src[i] % 32 + 9) % 25 * 16 + (src[i + 1] % 32 + 9) % 25;
	}
	//dst[len] = '\0';
	//return dst;
}

int readFile(uchar *&plaintext, const char* filename)
{
	FILE *fin;
	fopen_s(&fin, filename, "rb");
	if (!fin) return 0;
	fseek(fin, 0, SEEK_END);
	int len = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	plaintext = new uchar[len];
	char *str = new char[len];
	fread(plaintext, 1, len, fin);
	fclose(fin);
	return len;
}

int write2File(uchar *text, int len, const char* filename)
{
	FILE *fout;
	fopen_s(&fout, filename, "wb");
	if (!fout) return 0;
	fwrite(text, 1, len, fout);
	fclose(fout);
	return len;
}