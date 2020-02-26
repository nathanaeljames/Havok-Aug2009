/*HBAdata - analyzes human behavior in password creation.

   Author: Nathanael Warren - http://www.cerberusgate.com
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>//for atoi
#include <vector>
#include <algorithm>
#include "BigIntegerLibrary.hh"
using namespace std;

void usage()
{
	cout << "\tArguments (may be any combination):\n";
	cout << "\t-a - does an arbitrary frequency analysis\n";
	cout << "\t-f - does a full position-respective frequency analysis\n";
	cout << "\t-v - verbose\n";
	cout << "\t<sample password list file>\n";
	cout << "\t-h / -help - prints usage\n\n";
	exit(1);
}

int main (int argc, char *argv[])
{
	cout << "\n HBAdata - analyzes human behavior in password creation\n";
	cout << "\tby Nathanael Warren, 2009\n\n";

	bool arbanal,fullanal,verbose;
	arbanal=fullanal=verbose=0;

	int argvsample;//to find the argument containing the sample file
	argvsample=0;

	if(argc<3)
		usage();

	for(int i=1;i<argc;i++)
	{
		if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"-help"))
			usage();
		else if(!strcmp(argv[i],"-a"))
			arbanal=1;
		else if(!strcmp(argv[i],"-f"))
			fullanal=1;
		else if(!strcmp(argv[i],"-v"))
			verbose=1;
		else if(argv[i][0]!='-')
			argvsample=i;
	}

	//initialize arrays:

	//numeric
    char charsetzero[] = "0123456789";
	//lower_alpha
    char charsetone[] = "abcdefghijklmnopqrstuvwxyz";
	//UPPER_ALPHA
    char charsettwo[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//lower_alpha_numeric
    char charsetthree[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	//UPPER_ALPHA_numeric
    char charsetfour[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//lower_alpha_numeric_symbol14
    char charsetfive[] = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_+=";
	//UPPER_ALPHA_numeric_symbol14
    char charsetsix[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=";
	//MiX_AlPhA
    char charsetseven[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//MiX_AlPhA_numeric
    char charseteight[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//MiX_AlPhA_numeric_symbol14_space
    char charsetnine[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+= ";
	//MiX_AlPhA_numeric_symbol32_space
    char charsetten[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=~`[]{}|\\:;\"\'<>,.?/ ";

	//BigInteger counters:
	BigInteger bnumberofchars(0), bnumberofwords(0), bnumberofwordsinnocharset(0);
	
	//vector which holds the chars of charset(MiX_AlPhA_numeric_symbol32)
	vector<char> vec_charsetchars;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetchars.push_back(charsetten[i]);//store charsetten in vector

	//vector which holds char counts respective to chars in 'vec_charsetchars'
	vector<BigInteger> vec_charsetcharscounts_poszero;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_poszero.push_back(0);//initialize all elements to zero
	//position one...
	vector<BigInteger> vec_charsetcharscounts_posone;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posone.push_back(0);//initialize all elements to zero
	//position two...
	vector<BigInteger> vec_charsetcharscounts_postwo;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_postwo.push_back(0);//initialize all elements to zero
	//position three...
	vector<BigInteger> vec_charsetcharscounts_posthree;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posthree.push_back(0);//initialize all elements to zero
	//position four...
	vector<BigInteger> vec_charsetcharscounts_posfour;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posfour.push_back(0);//initialize all elements to zero
	//position five...
	vector<BigInteger> vec_charsetcharscounts_posfive;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posfive.push_back(0);//initialize all elements to zero
	//position six...
	vector<BigInteger> vec_charsetcharscounts_possix;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_possix.push_back(0);//initialize all elements to zero
	//position seven...
	vector<BigInteger> vec_charsetcharscounts_posseven;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posseven.push_back(0);//initialize all elements to zero
	//position eight...
	vector<BigInteger> vec_charsetcharscounts_poseight;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_poseight.push_back(0);//initialize all elements to zero
	//position nine...
	vector<BigInteger> vec_charsetcharscounts_posnine;
	for(unsigned int i=0;i<strlen(charsetten);i++)
		vec_charsetcharscounts_posnine.push_back(0);//initialize all elements to zero

	//open password list file - one password per line
	ifstream passwordfile(argv[argvsample]);
	//check to ensure passwordfile opened correctly
	if (!passwordfile.is_open())
    {
        cout<<"Error opening file \'" << (argv[argvsample]) << "\'\n";
        exit(1);
    }

	char password[1000];
	unsigned int passwordlen=0;//test for length comparison
	for(int x=0;!passwordfile.eof();x++)
	{
		passwordfile.getline(password,999);//word by word
		bnumberofwords++;//count the word

		//check to ensure all passwords are of same length...
		if(strlen(password)!=passwordlen && x!=0)
		{
			cout << "not all passwords in password file are same length!\n";
			cout << "please sort out different length words\n";
			cout << "see README for more information.\n";
			exit(1);
		}
		passwordlen=strlen(password);
		if(passwordlen>10)
		{
			cout << "passwords of more than 10 chars not supported!\n";
			cout << "see README for more information.\n";
			exit(1);
		}

		for(unsigned int i=0;i<strlen(password);i++)//char by char
		{
			bnumberofchars++;//count the chars
			for(unsigned int c=0;c<vec_charsetchars.size();c++)//compare each char of password to all 'vec_charsetchars' chars
			{
				if(i==0 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_poszero[c]++;//count number of each char
				if(i==1 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posone[c]++;
				if(i==2 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_postwo[c]++;
				if(i==3 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posthree[c]++;
				if(i==4 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posfour[c]++;
				if(i==5 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posfive[c]++;
				if(i==6 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_possix[c]++;
				if(i==7 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posseven[c]++;
				if(i==8 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_poseight[c]++;
				if(i==9 && password[i]==vec_charsetchars[c])
					vec_charsetcharscounts_posnine[c]++;
			}
		}
	}
	passwordfile.close();//close password file

	cout << bnumberofwords << " total words in file\n";
	cout << "passwords are of length " << passwordlen << "\n";
	cout << bnumberofchars << " total characters in file\n\n";

//////////////////////////////////////////////////////////////////////////////////////////////////////
	if(arbanal)
	{
		cout << "//////////////////////////////////////////\n";
		cout << "//arbitrary position frequency analysis://\n";
		cout << "//////////////////////////////////////////\n\n";
		//a vector to hold the total char counts for each char, respectively
		vector<BigInteger> vec_totalcounts;
		for(unsigned int i=0;i<strlen(charsetten);i++)
			vec_totalcounts.push_back(0);//initialize all elements to zero
		for(unsigned int i=0;i<vec_totalcounts.size();i++)//add counts from each position...
			vec_totalcounts[i]=vec_totalcounts[i]+vec_charsetcharscounts_poszero[i]+vec_charsetcharscounts_posone[i]+vec_charsetcharscounts_postwo[i]+vec_charsetcharscounts_posthree[i]+vec_charsetcharscounts_posfour[i]+vec_charsetcharscounts_posfive[i]+vec_charsetcharscounts_possix[i]+vec_charsetcharscounts_posseven[i]+vec_charsetcharscounts_poseight[i]+vec_charsetcharscounts_posnine[i];
		if(verbose)
		{
			cout << "char\tarbitrary position\n\n";
			for(unsigned int i=0;i<vec_totalcounts.size();i++)//print
				cout <<vec_charsetchars[i]<<"\t"<<vec_totalcounts[i]<<"\n";
			cout << "\n";
		}
		cout << "arbitrary position frequency analysis:\n";
		cout << "--------------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, unique, and output as string
		for(unsigned int i=0;i<vec_totalcounts.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_totalcounts[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_totalcounts.size();c++)//scan through each charcount in original vector
				if(vec_totalcounts[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////
	if(fullanal)
	{
		cout << "////////////////////////////////////////////////\n";
		cout << "//full position-respective frequency analysis://\n";
		cout << "////////////////////////////////////////////////\n\n";
		if(verbose)
		{
			cout << "char\tposo\tpos1\tpos2\tpos3\tpos4\n\n";
			for(unsigned int c=0;c<vec_charsetchars.size();c++)
			{
				cout<<vec_charsetchars[c]<<"\t"<<vec_charsetcharscounts_poszero[c]<<"\t";
				cout<<vec_charsetcharscounts_posone[c]<<"\t"<<vec_charsetcharscounts_postwo[c]<<"\t";
				cout<<vec_charsetcharscounts_posthree[c]<<"\t"<<vec_charsetcharscounts_posfour[c]<<"\n";
			}
			cout << "\nchar\tpos5\tpos6\tpos7\tpos8\tpos9\n\n";
			for(unsigned int c=0;c<vec_charsetchars.size();c++)
			{
				cout<<vec_charsetchars[c]<<"\t"<<vec_charsetcharscounts_posfive[c]<<"\t";
				cout<<vec_charsetcharscounts_possix[c]<<"\t"<<vec_charsetcharscounts_posseven[c]<<"\t";
				cout<<vec_charsetcharscounts_poseight[c]<<"\t"<<vec_charsetcharscounts_posnine[c]<<"\n";
			}
			cout << "\n";
		}
/////////////////////////////////////
		//for position zero:
		{
		cout << "position 0 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_poszero.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_poszero[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_poszero.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_poszero[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position one:
		{
		cout << "position 1 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posone.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posone[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posone.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posone[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position two:
		{
		cout << "position 2 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_postwo.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_postwo[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_postwo.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_postwo[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position three:
		{
		cout << "position 3 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posthree.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posthree[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posthree.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posthree[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position four:
		{
		cout << "position 4 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posfour.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posfour[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posfour.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posfour[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position five:
		{
		cout << "position 5 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posfive.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posfive[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posfive.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posfive[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position six:
		{
		cout << "position 6 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_possix.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_possix[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_possix.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_possix[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position seven:
		{
		cout << "position 7 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posseven.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posseven[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posseven.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posseven[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position eight:
		{
		cout << "position 8 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_poseight.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_poseight[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_poseight.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_poseight[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
/////////////////////////////////////
		//for position nine:
		{
		cout << "position 9 frequency analysis:\n";
		cout << "------------------------------\n";
		//a vector to copy a vector into
		vector<BigInteger> vec_charsetcharscountstocopy;
		//now copy to a temporary vector, sort, and output as string
		for(unsigned int i=0;i<vec_charsetcharscounts_posnine.size();i++)
			vec_charsetcharscountstocopy.push_back(vec_charsetcharscounts_posnine[i]);//copy vector
		//sort vector (least to greatest)...
		sort(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end());
		//remove duplicates...
		vec_charsetcharscountstocopy.resize((unique(vec_charsetcharscountstocopy.begin(),vec_charsetcharscountstocopy.end()))-vec_charsetcharscountstocopy.begin());
		//go through sorted copy vector backwards (greatest to least)...
		for(unsigned int i=vec_charsetcharscountstocopy.size()-1;i!=(-1);i--)
			for(unsigned int c=0;c<vec_charsetcharscounts_posnine.size();c++)//scan through each charcount in original vector
				if(vec_charsetcharscounts_posnine[c]==vec_charsetcharscountstocopy[i])//if the same...
					cout<<vec_charsetchars[c];//print results
		cout << "\n\n";
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////

return 0;
}
