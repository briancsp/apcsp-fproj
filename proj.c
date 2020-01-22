#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//function takes string input, returns string with only lowercase letters
char* edit(char str[]) {
  char str2[256]="";
  int count = 0;

  for(int i=0;i<strlen(str);i++) {
    if(str[i]>=65 && str[i]<=90) {
      str[i]=str[i]+32;
    }
    if(str[i]>=97 && str[i]<=122) {
      str2[count]=str[i];
      count++;
    }
  }

  strcpy(str,str2);
  return str;
}

char* makePad(char pad[],int len) {
  srand(time(NULL));
  for(int i=0;i<len;i++) {
    pad[i]=rand()%26+97;
  }
  return pad;
}

int main(int argc, char *argv[]) {
	char alph[] = "abcdefghijklmnopqrstuvwxyz";
	char polyalph[26][27] = {};
	int inc = 0;

  //build polyalphabetic grid
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

	char key[256] = "";
	char plaintext[256] = "";
	char ciphertext[256] = "";
  	char func[256]="";
  	char sample[] = "thisissampleplaintext";
	int pad = 0;

      if(argc==4) {
	sscanf(argv[1],"%s",plaintext);
	sscanf(argv[2],"%s",key);
	sscanf(argv[3],"%s",func);
      }
      else if(argc==2) {
	if(strcmp(argv[1],"decrypt")==0) {
	  sscanf(argv[1],"%s",func);
        }
      }

  if(strcmp(func,"")==0) {
    char thing[] = "encrypt";
    for(int i=0;i<7;i++) {
      func[i]=thing[i];
    }
  }

  if(strcmp(func,"encrypt")==0 && strcmp(key,"1TP")==0) {
    *key=*makePad(key,strlen(plaintext));
    pad=1;
  }

  if(strcmp(func,"encrypt")==0) {
    printf("We are going to %s... \nplaintext: %s, key: %s (YOUR INPUT)\n",func,plaintext,key);
  }
  else if (strcmp(func,"decrypt")==0) {
    printf("We are going to %s... \nciphertext: %s, key: %s (YOUR INPUT)\n",func,plaintext,key);
  }

  *plaintext=*edit(plaintext);
  *key=*edit(key);

  if(strcmp(func,"encrypt")==0) {
    if(strcmp(plaintext,"")==0 && strcmp(key,"")==0) {
      for(int i=0;i<strlen(sample);i++) {
        plaintext[i]=sample[i];
      }
      *key=*makePad(key,strlen(plaintext));
      printf("\nInvalid inputs. Using Sample Plaintext and One-Time Pad. Copy the one-time pad if you want to decrypt.\n");
    }
      printf("\nplaintext: %s, key: %s (EDITED INPUT)\n",plaintext,key);
      if(pad==1) {
	printf("Using One-Time Pad. Copy the one-time pad if you want to decrypt.\n");
      }
  }
  else if (strcmp(func,"decrypt")==0) {
    printf("ciphertext: %s, key: %s (EDITED INPUT)\n",plaintext,key);
  }

  printf("\n%sing...\n",func);

  int keyL = strlen(key);
  int plainL = strlen(plaintext);

  //ENCRYPT - get character from ind1 - key character, ind2 - plaintext character
  if(strcmp(func,"encrypt")==0) {
    for (int i = 0; i < plainL; i++) {
      int imod = (int) fmod(i,keyL);
      int keyindex = key[imod] - 97;
      int alphindex = plaintext[i] - 97;
      char ch = polyalph[keyindex][alphindex];
      ciphertext[i] = ch;
    }
    printf("\nResults:\nPlaintext:  %s\nCiphertext: %s\n", plaintext, ciphertext);
  }

  //DECRYPT - get character from alphindex of regular alphabet. Alphindex is index of ciphertext character in row of polyalph given by key character
  else if(strcmp(func,"decrypt")==0) {
    if(strcmp(key,"")==0) {
      printf("\nNo valid keyword entered. Enter keyword and try again.\n");
      if(strcmp(plaintext,"")==0) {
        printf("\nNo valid ciphertext entered. Enter ciphertext and try again.\n");
      }
    }
    else if(strcmp(plaintext,"")==0) {
      printf("\nNo valid ciphertext entered. Enter ciphertext and try again.\n");
    }
    else {
      for (int i = 0; i < plainL; i++) {
        int imod = (int) fmod(i,keyL);
        int keyindex = key[imod] - 97;
        int alphindex = fmod(26 + plaintext[i] - 97 - keyindex,26);
        char ch = alph[alphindex];
        ciphertext[i] = ch;
      }
      printf("\nResults:\nPlaintext:  %s\nCiphertext: %s\n", plaintext, ciphertext);
    }
  }
	
	return 0;
}
