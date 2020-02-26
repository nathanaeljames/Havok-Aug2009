#include <string>
#include <ctime>
#include <stdlib.h>//atoi
#include <iostream>
#include <fstream>
#include "signal.h"//Ctrl+C catch
#include "BigIntegerLibrary.hh"//computing large numbers

using namespace std;

//#include <openssl/md5.h>
//#include <openssl/md4.h>
//#include <openssl/rc4.h>
#include "fast_md4.h"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

void dump(uint8_t *digest)
{
		for(int i = 0;i < 16;i++)
			printf("%02X",digest[i]);
}

char candidate[11];

void wrapUp(int sig)
{
	cout << "\naborting...\n";
	cout << "ended on " << candidate << "\n";
	exit(0);
}

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

#include "hba_L5_alnum.h"
#include "hba_L6_alnum.h"
#include "hba_L7_alnum.h"
#include "hba_L8_alnum.h"
#include "hba_L9_alnum.h"
#include "hba_L10_alnum.h"

#include "hba_L5_mixalnum.h"
#include "hba_L6_mixalnum.h"
#include "hba_L7_mixalnum.h"
#include "hba_L8_mixalnum.h"
#include "hba_L9_mixalnum.h"
#include "hba_L10_mixalnum.h"

#include "hba_L5_mixalnumsymb14.h"
#include "hba_L6_mixalnumsymb14.h"
#include "hba_L7_mixalnumsymb14.h"
#include "hba_L8_mixalnumsymb14.h"
#include "hba_L9_mixalnumsymb14.h"
#include "hba_L10_mixalnumsymb14.h"

#include "hba_L5_mixalnumsymb32.h"
#include "hba_L6_mixalnumsymb32.h"
#include "hba_L7_mixalnumsymb32.h"
#include "hba_L8_mixalnumsymb32.h"
#include "hba_L9_mixalnumsymb32.h"
#include "hba_L10_mixalnumsymb32.h"

void usage()
{
       cout << " Usage: <start word> <permutations> <crack mode> <hash file> <username file>\n";
	   cout << "\n         crack modes:\n";
       cout << "         1 = brute force attack with (a-z, 0-9)\n";
       cout << "         2 = brute force attack with (a-z, A-Z, 0-9)\n";
       cout << "         3 = brute force attack with (a-z, A-Z, 0-9, 14 special chars)\n";
       cout << "         4 = brute force attack with (a-z, A-Z, 0-9, 32 special chars)\n";
       cout << "\n See README.txt for more details\n\n";
	   exit(1);
}

int main (int argc, char *argv[])
{
	cout << "\nHavokv3 mscache multihash - a distributed mscache password cracker\n";
	cout << "multiple hashes support - support for up to 25 simultaneous hashes\n";
    cout << "                  - by Nathanael Warren, 2009\n\n";

	if(argc!=6)
		usage();

	// so we can show stats on ctrl+c
	signal(SIGINT, wrapUp);

	for(unsigned int i=0;i<strlen(argv[1]);i++)//store argv[1] in candidate array
		candidate[i]=argv[1][i];

	unsigned int crackmode = atoi(argv[3]);
	unsigned int pass_len = strlen(argv[1]);

	uint8_t mscache_hash_array[25][16]={{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
		{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F },
	{ 0xA6, 0x04, 0x67, 0x77, 0xA8, 0xE0, 0x5F, 0x53, 0x7F, 0x4C, 0xA1, 0x47, 0x9C, 0x26, 0x73, 0x3F }};

	int sUsernameSize[]={666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666,666};

	char u_username_array[25][40];

	//open the hash list...
	ifstream hash_list(argv[4]);

	//check to ensure hash list opened correctly
	if(!hash_list.is_open())
	{
		cout<<"Error opening file \'"<<argv[4]<<"\'\n";
		exit(1);
	}

	char shash[33];//temporary array to store hash strings in
	int numhashes=0;
	while(!hash_list.eof())
	{
		//mscache hash buffer
		uint8_t mscache_hash[16];
		hash_list.getline(shash,33);//get each line of hash file
		if(numhashes==25)//make sure that no more than 25 hashes are loaded
		{
			cout << "more than 25 hashes not supported as of this release!\n";
			exit(1);
		}
		if(strlen(shash)!=32)
		{
			cout << "mscache hash is a 32-character hex string\n";
			exit(1);
		}
		//convert strings to binary...
		getHash(shash,mscache_hash);
		//and store them in their arrays
		for(int i=0;i<16;i++)
			mscache_hash_array[numhashes][i]=mscache_hash[i];
		numhashes++;//count loops
	}

	hash_list.close();

	//open username list...
	ifstream username_list(argv[5]);

	//check to ensure username list opened correctly
	if(!username_list.is_open())
	{
		cout<<"Error opening file \'"<<argv[5]<<"\'\n";
		exit(1);
	}

	string sUsername;//temporary array to store username strings in
	int numusers=0;
	while(getline(username_list,sUsername)){
		sUsernameSize[numusers]=sUsername.size();
		memset(u_username_array[numusers], 0, 40);
		// Convert username to unicode and lowercase it
		for (unsigned int i = 0; i < sUsername.size(); i++)
		{
			u_username_array[numusers][i*2] = tolower(sUsername[i]);
			u_username_array[numusers][i*2+1] = 0x00;
		}
		numusers++;
	}

	username_list.close();

	if(numusers!=numhashes)
	{
		cout << "number of usernames does not equal number of hashes!\n";
		cout << "usernames and hashes should be respective to one another.\n";
		exit(1);
	}

	cout << numhashes << " hashes loaded\n";

	cout << " computing (this may take a while)...\n\n";

	switch(pass_len)
	{
	case 5:
		switch(crackmode)
		{
		case 1:
			hba_L5_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L5_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L5_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L5_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	case 6:
		switch(crackmode)
		{
		case 1:
			hba_L6_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L6_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L6_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L6_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	case 7:
		switch(crackmode)
		{
		case 1:
			hba_L7_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L7_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L7_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L7_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	case 8:
		switch(crackmode)
		{
		case 1:
			hba_L8_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L8_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L8_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L8_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	case 9:
		switch(crackmode)
		{
		case 1:
			hba_L9_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L9_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L9_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L9_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	case 10:
		switch(crackmode)
		{
		case 1:
			hba_L10_alnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 2:
			hba_L10_mixalnum(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 3:
			hba_L10_mixalnumsymb14(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		case 4:
			hba_L10_mixalnumsymb32(candidate,argv[2],mscache_hash_array,u_username_array,sUsernameSize,numhashes);
			exit(0);
		default:
			usage();
		}
	default:
		usage();
	}
return 0;
}
