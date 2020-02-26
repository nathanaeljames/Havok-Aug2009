#include <string>
//#include <ctime>
//#include <stdlib.h>//atoi
#include <iostream>
//#include <fstream>
//#include "signal.h"//Ctrl+C catch
#include "fast_md4.h"
#include "fast_md5.h"
#include <openssl/rc4.h>

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

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
	if(argc!=3)
		exit(1);

	uint8_t clear_data[64];
	uint8_t K[16], K1[16], K2[16], K3[16];
	uint32_t T = 1;
	RC4_KEY data_key;
	uint16_t uni_pwd[128]={0};
	uint8_t k_ipad[100];//65
	uint8_t k_opad[100];//65

	/*//buffer to store hash in:
	uint8_t k5hash[16];
	//convert hash to binary
	getHash(argv[1],k5hash);*/

	char schecksum[]="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	char sencdata[]="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	for(int i=0;i<32;i++)
		schecksum[i]=argv[1][i];
	for(int i=0;i<72;i++)
		sencdata[i]=argv[1][i+32];
	// checksum of timestamp
	uint8_t ts_checksum[16];
	// encrypted timestamp
	uint8_t enc_data[36];
	getHash(schecksum,ts_checksum);
	getHash(sencdata,enc_data);

	string candidate_s;
	//char candidate_a[9999];//nope, no passwords over 9999 chars. But really?

	while(getline(cin,candidate_s)){
		//K=MD4(Little_endian(UNICODE(pwd))
		for(unsigned int i=0;i<candidate_s.size();i++)
			uni_pwd[i]=candidate_s[i];
		fast_MD4((unsigned char*)uni_pwd,candidate_s.size()*2,K);
		//K1=MD5_HMAC(K,1)
		memset(k_ipad,0,65);
		memset(k_opad,0,65);
		memcpy(k_ipad,K,16);
		memcpy(k_opad,K,16);
		for(int i = 0;i < 64;i++) {
			k_ipad[i] ^= 0x36;
			k_opad[i] ^= 0x5c;
		}
		memcpy(k_ipad+64,(uint8_t*)&T,4);
		fast_MD5(k_ipad,68,K1);
		memcpy(k_opad+64,K1,16);
		fast_MD5(k_opad,80,K1);
		//K3=MD5_HMAC(K1,checksum)
		memset(k_ipad,0,65);
		memset(k_opad,0,65);
		memcpy(k_ipad,K1,16);
		memcpy(k_opad,K1,16);
		for(int i = 0;i < 64;i++) {
			k_ipad[i] ^= 0x36;
			k_opad[i] ^= 0x5c;
		}
		memcpy(k_ipad+64,ts_checksum,16);
		fast_MD5(k_ipad,80,K3);
		memcpy(k_opad+64,K3,16);
		fast_MD5(k_opad,80,K3);
		//clear_data = RC4(K3,encrypted_data)
		RC4_set_key(&data_key,16,K3);
		//decrypt data up to year of timestamp...
		RC4(&data_key,18,enc_data,clear_data);
		//check to ensure year of timestamp
		//is equal to the year packet was captured...
		if(!memcmp(clear_data+14,argv[2],4))
		{
			//reset key
			RC4_set_key(&data_key,16,K3);
			//decrypt entire timestamp
			RC4(&data_key,36,enc_data,clear_data);
			//calculate the checksum
			memset(k_ipad,0,65);
			memset(k_opad,0,65);
			memcpy(k_ipad,K1,16);
			memcpy(k_opad,K1,16);
			for(int i = 0;i < 64;i++) {
				k_ipad[i] ^= 0x36;
				k_opad[i] ^= 0x5c;
			}
			memcpy(k_ipad+64,clear_data,36);
			fast_MD5(k_ipad,100,K2);
			memcpy(k_opad+64,K2,16);
			fast_MD5(k_opad,80,K2);
			//check...
			if(!memcmp(K2,ts_checksum,16))
			{
				cout << "\nthe plaintext is " << candidate_s << "\n\n";
				exit(1);
			}
		}
	}

return 0;
}
