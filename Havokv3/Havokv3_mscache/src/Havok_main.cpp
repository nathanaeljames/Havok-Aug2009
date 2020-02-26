#include <string>
#include <ctime>
#include <stdlib.h>//atoi
#include <iostream>
#include <fstream>
#include "signal.h"//Ctrl+C catch
#include "BigIntegerLibrary.hh"//computing large numbers
//#include "dense_hash_set"//for the hash table
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
       cout << " Usage: <start word> <permutations> <crack mode> <mscache hash> <username>\n";
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
	cout << "\nHavokv3 mscache - a distributed mscache password cracker\n";
    cout << "                  - by Nathanael Warren, 2009\n\n";

	if(argc!=6)
		usage();

	// so we can show stats on ctrl+c
	signal(SIGINT, wrapUp);

	for(unsigned int i=0;i<strlen(argv[1]);i++)//store argv[1] in candidate array
		candidate[i]=argv[1][i];

	if(strlen(argv[4])!=32)
	{
		cout << "mscache hash is a 32-character hex string\n";
		exit(1);
	}

	string sUsername = argv[5];
	char u_username[40];
	memset(u_username, 0, 40);

	// Convert username to unicode and lowercase it
	for (unsigned int i = 0; i < sUsername.size() && i < 19; i++)
	{
		u_username[i*2] = tolower(sUsername[i]);
		u_username[i*2+1] = 0x00;
	}

	uint8_t mscachehash[16];
	getHash(argv[4],mscachehash);

	cout << " computing (this may take a while)...\n\n";

	unsigned int crackmode = atoi(argv[3]);
	unsigned int pass_len = strlen(argv[1]);

	switch(pass_len)
	{
	case 5:
		switch(crackmode)
		{
		case 1:
			hba_L5_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L5_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L5_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L5_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	case 6:
		switch(crackmode)
		{
		case 1:
			hba_L6_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L6_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L6_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L6_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	case 7:
		switch(crackmode)
		{
		case 1:
			hba_L7_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L7_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L7_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L7_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	case 8:
		switch(crackmode)
		{
		case 1:
			hba_L8_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L8_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L8_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L8_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	case 9:
		switch(crackmode)
		{
		case 1:
			hba_L9_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L9_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L9_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L9_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	case 10:
		switch(crackmode)
		{
		case 1:
			hba_L10_alnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 2:
			hba_L10_mixalnum(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 3:
			hba_L10_mixalnumsymb14(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		case 4:
			hba_L10_mixalnumsymb32(candidate,argv[2],mscachehash,u_username,sUsername.size());
			exit(0);
		default:
			usage();
		}
	default:
		usage();
	}
return 0;
}
