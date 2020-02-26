/* HBAdemo - demonstrates the advantages of human behavior analysis
   in cryptography.
   
   Author: Nathanael Warren - http://www.cerberusgate.com
*/

#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <stdlib.h>//for atoi
#include <iostream>
#include "BigIntegerLibrary.hh"
#include <fstream>
using namespace std;

void usage()
{
	cout << " Usage:\n";
	cout << " <password list>\n";
}

bool incharset(char word[],char charset[])
{
     bool evaluation = 0;
     int truthcounter;//number of chars of word that are in charset
     truthcounter = 0;

     for(unsigned int i=0;i<strlen(word);i++)//for every char of word...
     {
             for(unsigned int c=0;c<strlen(charset);c++)//for every char of charset...
             {
                     if(word[i]==charset[c])//compare, and if the same...
                     {
                        truthcounter++;//than that char of word is in charset
                     }
             }
     }
     if(truthcounter==strlen(word))//if every char of word is in charset...
     {
        evaluation = 1;//then the entire word is in charset
     }
     return evaluation;
}

BigInteger bigpow(BigInteger bbase, int pow)
{
	BigInteger bpowresult(1);
	for(int i=1;i<=pow;i++)
	{
		bpowresult *= bbase;
	}
	return bpowresult;
}

int main (int argc, char *argv[])
{
	cout << "\nHBAdemo - demonstrates the cryptanalytic advantages of human behavior analysis\n";
	cout << "\tby Nathanael Warren, 2009\n\n";

	if(argc!=2)
	{
		usage();
		return 1;
	}

	ifstream charsets("charsets.txt");//open charsets file

	if(!charsets.is_open())//check to ensure charsets file opened correctly
    {
        cout<<"Error opening file \'charsets.txt\'\n";
		cout<<"see README for more information\n";
        exit(1);
    }

	//store the contents of 'charset.txt' file in a vector 'vec_charsets'. As each
	//word is read into the vector, make sure they are all of the same length and charset
	vector<string> vec_charsets;
	char charset[100];//temporary array
	char mastercharset[100];//to ensure all charsets are same
	unsigned int charsetlen=0;
	for(int i=0;!charsets.eof();i++)
	{
		charsets.getline(charset,99);//read charsets file line by line
		if(i==0)
		{
			strcpy(mastercharset,charset);//to test and ensure all charsets are same
		}
		if(strlen(charset)!=charsetlen && i!=0)
		{
			cout << "not all charset strings are the same length!\n";
			cout << "see README for more information\n";
			exit(1);
		}
		if(!incharset(charset,mastercharset))
		{
			cout << "not all charsets specified in \'charsets.txt\' match!\n";
			cout << "see README for more information\n";
			exit(1);
		}
		charsetlen=strlen(charset);
		vec_charsets.push_back(charset);//store in vector 'vec_charsets'
	}

	BigInteger bcharsetlen(charsetlen);

	//close file
	charsets.close();

	ifstream passwordfile(argv[1]);//open password list file

	if(!passwordfile.is_open())//check to ensure password list file opened correctly
    {
        cout<<"Error opening file " << (argv[1]) << "\n";
        exit(1);
    }

    //store the passwords file in a vector 'vec_passwords'. Check each password to make sure
	//they are the same length and fall into ALL of the charsets specified in the 'charsets.txt'
	//file
    char password[1000];//temporary array
    vector<string> vec_passwords;//array to store passwords in
	unsigned int passwordlen=0;//test for length comparison
    
    for(int i=0;!passwordfile.eof();i++)
	{
        passwordfile.getline(password,999); //read sample file line by line
		if(strlen(password)!=passwordlen && i!=0)
		{
			cout << "not all passwords in password file are same length!\n";
			cout << "please sort out different length words\n";
			cout << "see README for more information.\n";
			exit(1);
		}
		if(!incharset(password,mastercharset))
		{
			cout << "not all passwords fall in the charsets specified in \'charsets.txt\' file!\n";
			cout << "see README for more information\n";
			exit(1);
		}
		passwordlen=strlen(password);
        vec_passwords.push_back(password);//store in vector 'vec_passwords'
    }
	cout << "\n" << vec_passwords.size() << " passwords read in\n";
	cout << "passwords are of length " << passwordlen << "\n\n";

	//close file
	passwordfile.close();

	//make sure there is a charset defined for each position of password...
	if(vec_charsets.size()<passwordlen)
	{
		cout << "password length is " << passwordlen << " but there are";
		cout << " only " << vec_charsets.size() << " charsets defined in \'charsets.txt\'\n";
		cout << "see README for more information\n";
		exit(1);
	}

	BigInteger bpermutationstofind(0);

	for(unsigned int i=0;i<vec_passwords.size();i++)//scan through passwords, one by one
	{
		for(unsigned int c=0;c<passwordlen;c++)//scan through each char of password
		{
			for(unsigned int x=0;x<charsetlen;x++)//scan through respective charset string
			{
				if(vec_passwords[i][c]==vec_charsets[c][x])
				{
					bpermutationstofind=bpermutationstofind+(bigpow(bcharsetlen,c)*x);
				}
			}
		}
	}

	BigInteger btotalpasswords(vec_passwords.size());

	BigInteger baveragepermutations=bpermutationstofind/btotalpasswords;

	cout << "using this character set configuration, the average number of tries neccessary\n";
	cout << "to recover a password is " << baveragepermutations << " tries.\n\n";

	cout << "the total number of tries neccessary to recover all passwords in list was\n";
	cout << bpermutationstofind << " tries\n";

return 0;
}
