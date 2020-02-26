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

int main(int argc, char *argv[])
{
	if(argc!=2)
		exit(1);

	//buffer to store hash in:
	uint8_t md4hash[16];
	//convert hash to binary
	getHash(argv[1],md4hash);

	uint8_t K[16];
	string candidate_s;
	char candidate_a[9999];//nope, no passwords over 9999 chars. But really?

	while(getline(cin,candidate_s)){
		//convert the string to an array:
		for(unsigned int i=0;i<candidate_s.size();i++)
			candidate_a[i]=candidate_s[i];
		//encrypt that array:
		fast_MD4((unsigned char*)candidate_a,candidate_s.size(),K);
		//check it out to see if it works...
		if(!memcmp(md4hash,K,16))
		{
			cout << "\nplaintext of ";
			dump(K);
			cout << " is " << candidate_s << "\n";
			exit(1);
		}
	}

return 0;
}