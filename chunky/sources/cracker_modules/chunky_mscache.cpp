#include <string>
//#include <ctime>
//#include <stdlib.h>//atoi
#include <iostream>
//#include <fstream>
//#include "signal.h"//Ctrl+C catch
#include "fast_md4.h"

using namespace std;

typedef unsigned char uint8_t;
//typedef unsigned int uint32_t;

size_t getHash(char szHash[], unsigned char hash[])
{
       unsigned int number;
       size_t nHashLen;

       if(((nHashLen = strlen(szHash)) % 2) != 0)
            return(0);

       for(size_t i = 0;i < nHashLen;i++) {
           if(isxdigit(szHash[i]) == 0)
              return(0);
       }

       nHashLen /= 2;

       for(size_t i = 0;i < nHashLen;i++) {
           sscanf(&szHash[i*2],"%2x",&number);
           hash[i] = (unsigned char)number;
       }
       return(nHashLen);
}

void dump(uint8_t *digest)
{
		for(int i = 0;i < 16;i++)
			printf("%02X",digest[i]);
}

typedef unsigned short uint16_t;

int main(int argc, char *argv[])
{
	if(argc!=3)
		exit(1);

	string sUsername = argv[2];
	char u_username[40];
	memset(u_username, 0, 40);
	// Convert username to unicode and lowercase it
	for (unsigned int i = 0; i < sUsername.size() && i < 19; i++)
	{
		u_username[i*2] = tolower(sUsername[i]);
		u_username[i*2+1] = 0x00;
	}

	uint16_t uni_pwd[128]={0};

	//buffer to store hash in:
	uint8_t mscachehash[16];
	//convert hash to binary
	getHash(argv[1],mscachehash);

	uint8_t K[16];
	string candidate_s;
	//char candidate_a[9999];//nope, no passwords over 9999 chars. But really?

	while(getline(cin,candidate_s)){
		//convert the string to an array:
		for(unsigned int i=0;i<candidate_s.size();i++)
			uni_pwd[i]=candidate_s[i];
		//encrypt that array:
		fast_MD4((unsigned char*)uni_pwd,candidate_s.size()*2,K);
		memcpy(K+16, u_username, sUsername.size()*2);
		fast_MD4((unsigned char*)K,(sUsername.size()*2+16),(unsigned char*)K);
		//check it out to see if it works...
		if(!memcmp(mscachehash,K,16))
		{
			cout << "\nplaintext of ";
			dump(K);
			cout << " is " << candidate_s << "\n";
			exit(1);
		}
	}

return 0;
}
