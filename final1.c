#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	char alph[26] = "abcdefghijklmnopqrstuvwxyz";
	char polyalph[26][27] = {};
	int inc = 0;

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if ((j + inc) <= 25) {
				polyalph[i][j] = alph[j + inc];
			} else {
				polyalph[i][j] = alph[j + inc - 26];
			}
		}
		polyalph[i][26] = '\0';
		inc++;
	}

	/*for(int i=0;i<26;i++) {
	  printf("%s\n",polyalph[i]);
	}*/

	char key[256] = "yess";
	char plaintext[256] = "hihowami";
	char ciphertext[256] = "";

	int keyL = strspn(key, alph);
	int plainL = strspn(plaintext, alph);

	sscanf(argv[1],"%s",plaintext);
	sscanf(argv[2],"%s",key);

	for(int i=0;plaintext[i];i++) {
	  plaintext[i]=tolower(plaintext[i]);
	}

	for(int i=0;key[i];i++) {
	  key[i]=tolower(key[i]);
	}
	printf("plaintext: %s, key: %s\n",plaintext,key);

	for (int i = 0; i < plainL; i++) {
	  int imod = (int) fmod(i,keyL);
		int index = key[imod] - 97;
		int index2 = plaintext[i] - 97;
		char ch = polyalph[index][index2];
		//printf("index: %d, index2: %d, char: %c\n",index,index2,ch);
		ciphertext[i] = ch;
	}

	printf("Plaintext: %s\nCiphertext: %s\n", plaintext, ciphertext);

	return 0;
}
