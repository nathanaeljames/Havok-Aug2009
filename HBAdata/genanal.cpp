/*genanal - prints general analysis data and sorts wordlists for HBAdata.

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
	cout << "\t-g - prints some general analysis data\n";
	cout << "\t-c - prints programmed charsets\n";
	cout << "\t-s - sorts out words by charset and length\n";
	cout << "\t<sample password list file>\n";
	cout << "\t-h / -help - prints usage\n\n";
	exit(1);
}

bool incharset(char word[],char charset[])
{
     bool evaluation = 0;
     int truthcounter;//number of chars of word that are in charset
     truthcounter = 0;

     for(unsigned int i=0;i<strlen(word);i++)//for every char of word...
             for(unsigned int c=0;c<strlen(charset);c++)//for every char of charset...
                     if(word[i]==charset[c])//compare, and if the same...
                        truthcounter++;//than that char of word is in charset
     if(truthcounter==strlen(word))//if every char of word is in charset...
        evaluation = 1;//then the entire word is in charset
     return evaluation;
}

int main (int argc, char *argv[])
{
	cout << "\n genanal - prints general analysis data and sorts wordlists for HBAdata\n";
	cout << "\tby Nathanael Warren, 2009\n\n";

	bool generalanal, sortout, charsets;
	generalanal=sortout=charsets=0;

	int argvsample;//to find the argument containing the sample file
	argvsample=0;

	if(argc==1)
		usage();

	for(int i=1;i<argc;i++)
	{
		if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"-help"))
			usage();
		else if(!strcmp(argv[i],"-g"))
			generalanal=1;
		else if(!strcmp(argv[i],"-c"))
			charsets=1;
		else if(!strcmp(argv[i],"-s"))
			sortout=1;
		else if(argv[i][0]!='-')
			argvsample=i;
	}

	//initialize necessary data structures...

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
	//MiX_AlPhA_numeric_symbol14
    char charsetnine[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+= ";
	//MiX_AlPhA_numeric_symbol32
    char charsetten[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=~`[]{}|\\:;\"\'<>,.?/ ";

	if(charsets)
	{
		cout << "charset 0 is " << charsetzero << "\n";
		cout << "charset 1 is " << charsetone << "\n";
		cout << "charset 2 is " << charsettwo << "\n";
		cout << "charset 3 is " << charsetthree << "\n";
		cout << "charset 4 is " << charsetfour << "\n";
		cout << "charset 5 is " << charsetfive << "\n";
		cout << "charset 6 is " << charsetsix << "\n";
		cout << "charset 7 is " << charsetseven << "\n";
		cout << "charset 8 is " << charseteight << "\n";
		cout << "charset 9 is " << charsetnine << "\n";
		cout << "charset 10 is " << charsetten << "\n\n";
	}

	if(generalanal)
	{

		//BigInteger counters:
		BigInteger bnumberofwords(0), bnumberofwordsinnocharset(0);

		//vector which will eventually hold the number
		//of passwords that fall into each charset, respectively
		vector<BigInteger> vec_numwordsinrespcharset;
		for(int i=0;i<11;i++)
			vec_numwordsinrespcharset.push_back(0);//initialize all elements to zero

		//vector which will eventually hold the number of
		//passwords with lengths respective to element number
		vector<BigInteger> vec_numwordswithresplength;
		for(int i=0;i<15;i++)
			vec_numwordswithresplength.push_back(0);//initialize all elements to zero

		//open password list file - one password per line
		ifstream passwordfile(argv[argvsample]);
		//check to ensure passwordfile opened correctly
		if (!passwordfile.is_open())
		{
			cout<<"Error opening file \'" << (argv[argvsample]) << "\'\n";
			exit(1);
		}

		char password[1000];
		while(!passwordfile.eof())
		{
			passwordfile.getline(password,999);
			//count the word
			bnumberofwords++;
			//find charset(s) passwords fall in, and count number of passwords that fall in each charset...
			if(incharset(password,charsetzero))
				vec_numwordsinrespcharset[0]++;
			if(incharset(password,charsetone))
				vec_numwordsinrespcharset[1]++;
			if(incharset(password,charsettwo))
				vec_numwordsinrespcharset[2]++;
			if(incharset(password,charsetthree))
				vec_numwordsinrespcharset[3]++;
			if(incharset(password,charsetfour))
				vec_numwordsinrespcharset[4]++;
			if(incharset(password,charsetfive))
				vec_numwordsinrespcharset[5]++;
			if(incharset(password,charsetsix))
				vec_numwordsinrespcharset[6]++;
			if(incharset(password,charsetseven))
				vec_numwordsinrespcharset[7]++;
			if(incharset(password,charseteight))
				vec_numwordsinrespcharset[8]++;
			if(incharset(password,charsetnine))
				vec_numwordsinrespcharset[9]++;
			if(incharset(password,charsetten))
				vec_numwordsinrespcharset[10]++;
			if(!incharset(password,charsetten))
				bnumberofwordsinnocharset++;
			//find length of password and count number of passwords of each length...
			if(strlen(password)<=13)
				vec_numwordswithresplength[strlen(password)]++;
			if(strlen(password)>13)
				vec_numwordswithresplength[14]++;
		}

		cout << bnumberofwords << " words read from " << argv[argvsample] << ":\n\n";

		for(unsigned int i=0;i<vec_numwordswithresplength.size()-1;i++)
			cout<<vec_numwordswithresplength[i]<<" words are "<<i<<" characters long\n";
		cout<<vec_numwordswithresplength[14]<<" words are 14 or more characters long\n\n";

		for(unsigned int i=0;i<vec_numwordsinrespcharset.size();i++)
			cout<<vec_numwordsinrespcharset[i]<<" words fall in charset "<<i<<"\n";
		cout<<bnumberofwordsinnocharset<<" words fall in no defined charset\n\n";

		passwordfile.close();//close password file
	}

	if(sortout)
	{
		cout << "sorting passwords by length and charset:\n\n";
		//BigInteger counters:
		BigInteger bnumberofwords(0);

		//open output files:
		ofstream one_char_charset_zero("one_char_charset_zero.txt");
		ofstream one_char_charset_one("one_char_charset_one.txt");
		ofstream one_char_charset_two("one_char_charset_two.txt");
		ofstream one_char_charset_three("one_char_charset_three.txt");
		ofstream one_char_charset_four("one_char_charset_four.txt");
		ofstream one_char_charset_five("one_char_charset_five.txt");
		ofstream one_char_charset_six("one_char_charset_six.txt");
		ofstream one_char_charset_seven("one_char_charset_seven.txt");
		ofstream one_char_charset_eight("one_char_charset_eight.txt");
		ofstream one_char_charset_nine("one_char_charset_nine.txt");
		ofstream one_char_charset_ten("one_char_charset_ten.txt");

		ofstream two_char_charset_zero("two_char_charset_zero.txt");
		ofstream two_char_charset_one("two_char_charset_one.txt");
		ofstream two_char_charset_two("two_char_charset_two.txt");
		ofstream two_char_charset_three("two_char_charset_three.txt");
		ofstream two_char_charset_four("two_char_charset_four.txt");
		ofstream two_char_charset_five("two_char_charset_five.txt");
		ofstream two_char_charset_six("two_char_charset_six.txt");
		ofstream two_char_charset_seven("two_char_charset_seven.txt");
		ofstream two_char_charset_eight("two_char_charset_eight.txt");
		ofstream two_char_charset_nine("two_char_charset_nine.txt");
		ofstream two_char_charset_ten("two_char_charset_ten.txt");

		ofstream three_char_charset_zero("three_char_charset_zero.txt");
		ofstream three_char_charset_one("three_char_charset_one.txt");
		ofstream three_char_charset_two("three_char_charset_two.txt");
		ofstream three_char_charset_three("three_char_charset_three.txt");
		ofstream three_char_charset_four("three_char_charset_four.txt");
		ofstream three_char_charset_five("three_char_charset_five.txt");
		ofstream three_char_charset_six("three_char_charset_six.txt");
		ofstream three_char_charset_seven("three_char_charset_seven.txt");
		ofstream three_char_charset_eight("three_char_charset_eight.txt");
		ofstream three_char_charset_nine("three_char_charset_nine.txt");
		ofstream three_char_charset_ten("three_char_charset_ten.txt");

		ofstream four_char_charset_zero("four_char_charset_zero.txt");
		ofstream four_char_charset_one("four_char_charset_one.txt");
		ofstream four_char_charset_two("four_char_charset_two.txt");
		ofstream four_char_charset_three("four_char_charset_three.txt");
		ofstream four_char_charset_four("four_char_charset_four.txt");
		ofstream four_char_charset_five("four_char_charset_five.txt");
		ofstream four_char_charset_six("four_char_charset_six.txt");
		ofstream four_char_charset_seven("four_char_charset_seven.txt");
		ofstream four_char_charset_eight("four_char_charset_eight.txt");
		ofstream four_char_charset_nine("four_char_charset_nine.txt");
		ofstream four_char_charset_ten("four_char_charset_ten.txt");

		ofstream five_char_charset_zero("five_char_charset_zero.txt");
		ofstream five_char_charset_one("five_char_charset_one.txt");
		ofstream five_char_charset_two("five_char_charset_two.txt");
		ofstream five_char_charset_three("five_char_charset_three.txt");
		ofstream five_char_charset_four("five_char_charset_four.txt");
		ofstream five_char_charset_five("five_char_charset_five.txt");
		ofstream five_char_charset_six("five_char_charset_six.txt");
		ofstream five_char_charset_seven("five_char_charset_seven.txt");
		ofstream five_char_charset_eight("five_char_charset_eight.txt");
		ofstream five_char_charset_nine("five_char_charset_nine.txt");
		ofstream five_char_charset_ten("five_char_charset_ten.txt");

		ofstream six_char_charset_zero("six_char_charset_zero.txt");
		ofstream six_char_charset_one("six_char_charset_one.txt");
		ofstream six_char_charset_two("six_char_charset_two.txt");
		ofstream six_char_charset_three("six_char_charset_three.txt");
		ofstream six_char_charset_four("six_char_charset_four.txt");
		ofstream six_char_charset_five("six_char_charset_five.txt");
		ofstream six_char_charset_six("six_char_charset_six.txt");
		ofstream six_char_charset_seven("six_char_charset_seven.txt");
		ofstream six_char_charset_eight("six_char_charset_eight.txt");
		ofstream six_char_charset_nine("six_char_charset_nine.txt");
		ofstream six_char_charset_ten("six_char_charset_ten.txt");

		ofstream seven_char_charset_zero("seven_char_charset_zero.txt");
		ofstream seven_char_charset_one("seven_char_charset_one.txt");
		ofstream seven_char_charset_two("seven_char_charset_two.txt");
		ofstream seven_char_charset_three("seven_char_charset_three.txt");
		ofstream seven_char_charset_four("seven_char_charset_four.txt");
		ofstream seven_char_charset_five("seven_char_charset_five.txt");
		ofstream seven_char_charset_six("seven_char_charset_six.txt");
		ofstream seven_char_charset_seven("seven_char_charset_seven.txt");
		ofstream seven_char_charset_eight("seven_char_charset_eight.txt");
		ofstream seven_char_charset_nine("seven_char_charset_nine.txt");
		ofstream seven_char_charset_ten("seven_char_charset_ten.txt");

		ofstream eight_char_charset_zero("eight_char_charset_zero.txt");
		ofstream eight_char_charset_one("eight_char_charset_one.txt");
		ofstream eight_char_charset_two("eight_char_charset_two.txt");
		ofstream eight_char_charset_three("eight_char_charset_three.txt");
		ofstream eight_char_charset_four("eight_char_charset_four.txt");
		ofstream eight_char_charset_five("eight_char_charset_five.txt");
		ofstream eight_char_charset_six("eight_char_charset_six.txt");
		ofstream eight_char_charset_seven("eight_char_charset_seven.txt");
		ofstream eight_char_charset_eight("eight_char_charset_eight.txt");
		ofstream eight_char_charset_nine("eight_char_charset_nine.txt");
		ofstream eight_char_charset_ten("eight_char_charset_ten.txt");

		ofstream nine_char_charset_zero("nine_char_charset_zero.txt");
		ofstream nine_char_charset_one("nine_char_charset_one.txt");
		ofstream nine_char_charset_two("nine_char_charset_two.txt");
		ofstream nine_char_charset_three("nine_char_charset_three.txt");
		ofstream nine_char_charset_four("nine_char_charset_four.txt");
		ofstream nine_char_charset_five("nine_char_charset_five.txt");
		ofstream nine_char_charset_six("nine_char_charset_six.txt");
		ofstream nine_char_charset_seven("nine_char_charset_seven.txt");
		ofstream nine_char_charset_eight("nine_char_charset_eight.txt");
		ofstream nine_char_charset_nine("nine_char_charset_nine.txt");
		ofstream nine_char_charset_ten("nine_char_charset_ten.txt");

		ofstream ten_char_charset_zero("ten_char_charset_zero.txt");
		ofstream ten_char_charset_one("ten_char_charset_one.txt");
		ofstream ten_char_charset_two("ten_char_charset_two.txt");
		ofstream ten_char_charset_three("ten_char_charset_three.txt");
		ofstream ten_char_charset_four("ten_char_charset_four.txt");
		ofstream ten_char_charset_five("ten_char_charset_five.txt");
		ofstream ten_char_charset_six("ten_char_charset_six.txt");
		ofstream ten_char_charset_seven("ten_char_charset_seven.txt");
		ofstream ten_char_charset_eight("ten_char_charset_eight.txt");
		ofstream ten_char_charset_nine("ten_char_charset_nine.txt");
		ofstream ten_char_charset_ten("ten_char_charset_ten.txt");

		ofstream eleven_char_charset_zero("eleven_char_charset_zero.txt");
		ofstream eleven_char_charset_one("eleven_char_charset_one.txt");
		ofstream eleven_char_charset_two("eleven_char_charset_two.txt");
		ofstream eleven_char_charset_three("eleven_char_charset_three.txt");
		ofstream eleven_char_charset_four("eleven_char_charset_four.txt");
		ofstream eleven_char_charset_five("eleven_char_charset_five.txt");
		ofstream eleven_char_charset_six("eleven_char_charset_six.txt");
		ofstream eleven_char_charset_seven("eleven_char_charset_seven.txt");
		ofstream eleven_char_charset_eight("eleven_char_charset_eight.txt");
		ofstream eleven_char_charset_nine("eleven_char_charset_nine.txt");
		ofstream eleven_char_charset_ten("eleven_char_charset_ten.txt");

		ofstream twelve_char_charset_zero("twelve_char_charset_zero.txt");
		ofstream twelve_char_charset_one("twelve_char_charset_one.txt");
		ofstream twelve_char_charset_two("twelve_char_charset_two.txt");
		ofstream twelve_char_charset_three("twelve_char_charset_three.txt");
		ofstream twelve_char_charset_four("twelve_char_charset_four.txt");
		ofstream twelve_char_charset_five("twelve_char_charset_five.txt");
		ofstream twelve_char_charset_six("twelve_char_charset_six.txt");
		ofstream twelve_char_charset_seven("twelve_char_charset_seven.txt");
		ofstream twelve_char_charset_eight("twelve_char_charset_eight.txt");
		ofstream twelve_char_charset_nine("twelve_char_charset_nine.txt");
		ofstream twelve_char_charset_ten("twelve_char_charset_ten.txt");

		ofstream thirteen_char_charset_zero("thirteen_char_charset_zero.txt");
		ofstream thirteen_char_charset_one("thirteen_char_charset_one.txt");
		ofstream thirteen_char_charset_two("thirteen_char_charset_two.txt");
		ofstream thirteen_char_charset_three("thirteen_char_charset_three.txt");
		ofstream thirteen_char_charset_four("thirteen_char_charset_four.txt");
		ofstream thirteen_char_charset_five("thirteen_char_charset_five.txt");
		ofstream thirteen_char_charset_six("thirteen_char_charset_six.txt");
		ofstream thirteen_char_charset_seven("thirteen_char_charset_seven.txt");
		ofstream thirteen_char_charset_eight("thirteen_char_charset_eight.txt");
		ofstream thirteen_char_charset_nine("thirteen_char_charset_nine.txt");
		ofstream thirteen_char_charset_ten("thirteen_char_charset_ten.txt");

		//open password list file - one password per line
		ifstream passwordfile(argv[argvsample]);
		//check to ensure passwordfile opened correctly
		if (!passwordfile.is_open())
		{
			cout<<"Error opening file \'" << (argv[argvsample]) << "\'\n";
			exit(1);
		}

		char password[1000];
		while(!passwordfile.eof())
		{
			passwordfile.getline(password,999);
			//count the word
			bnumberofwords++;
			switch(strlen(password))
			{
			case 1:
				if(incharset(password,charsetzero))
					one_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					one_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					one_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					one_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					one_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					one_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					one_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					one_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					one_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					one_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					one_char_charset_ten << password << "\n";
				break;
			case 2:
				if(incharset(password,charsetzero))
					two_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					two_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					two_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					two_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					two_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					two_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					two_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					two_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					two_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					two_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					two_char_charset_ten << password << "\n";
				break;
			case 3:
				if(incharset(password,charsetzero))
					three_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					three_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					three_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					three_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					three_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					three_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					three_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					three_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					three_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					three_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					three_char_charset_ten << password << "\n";
				break;
			case 4:
				if(incharset(password,charsetzero))
					four_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					four_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					four_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					four_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					four_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					four_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					four_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					four_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					four_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					four_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					four_char_charset_ten << password << "\n";
				break;
			case 5:
				if(incharset(password,charsetzero))
					five_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					five_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					five_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					five_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					five_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					five_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					five_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					five_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					five_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					five_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					five_char_charset_ten << password << "\n";
				break;
			case 6:
				if(incharset(password,charsetzero))
					six_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					six_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					six_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					six_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					six_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					six_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					six_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					six_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					six_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					six_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					six_char_charset_ten << password << "\n";
				break;
			case 7:
				if(incharset(password,charsetzero))
					seven_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					seven_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					seven_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					seven_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					seven_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					seven_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					seven_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					seven_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					seven_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					seven_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					seven_char_charset_ten << password << "\n";
				break;
			case 8:
				if(incharset(password,charsetzero))
					eight_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					eight_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					eight_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					eight_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					eight_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					eight_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					eight_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					eight_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					eight_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					eight_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					eight_char_charset_ten << password << "\n";
				break;
			case 9:
				if(incharset(password,charsetzero))
					nine_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					nine_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					nine_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					nine_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					nine_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					nine_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					nine_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					nine_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					nine_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					nine_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					nine_char_charset_ten << password << "\n";
				break;
			case 10:
				if(incharset(password,charsetzero))
					ten_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					ten_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					ten_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					ten_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					ten_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					ten_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					ten_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					ten_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					ten_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					ten_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					ten_char_charset_ten << password << "\n";
				break;
			case 11:
				if(incharset(password,charsetzero))
					eleven_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					eleven_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					eleven_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					eleven_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					eleven_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					eleven_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					eleven_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					eleven_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					eleven_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					eleven_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					eleven_char_charset_ten << password << "\n";
				break;
			case 12:
				if(incharset(password,charsetzero))
					twelve_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					twelve_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					twelve_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					twelve_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					twelve_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					twelve_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					twelve_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					twelve_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					twelve_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					twelve_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					twelve_char_charset_ten << password << "\n";
				break;
			case 13:
				if(incharset(password,charsetzero))
					thirteen_char_charset_zero << password << "\n";
				if(incharset(password,charsetone))
					thirteen_char_charset_one << password << "\n";
				if(incharset(password,charsettwo))
					thirteen_char_charset_two << password << "\n";
				if(incharset(password,charsetthree))
					thirteen_char_charset_three << password << "\n";
				if(incharset(password,charsetfour))
					thirteen_char_charset_four << password << "\n";
				if(incharset(password,charsetfive))
					thirteen_char_charset_five << password << "\n";
				if(incharset(password,charsetsix))
					thirteen_char_charset_six << password << "\n";
				if(incharset(password,charsetseven))
					thirteen_char_charset_seven << password << "\n";
				if(incharset(password,charseteight))
					thirteen_char_charset_eight << password << "\n";
				if(incharset(password,charsetnine))
					thirteen_char_charset_nine << password << "\n";
				if(incharset(password,charsetten))
					thirteen_char_charset_ten << password << "\n";
				break;
			default:
				break;
			}
		}
		cout << bnumberofwords << " words read from " << argv[argvsample] << "\n\n";
		passwordfile.close();//close password file
	}

return 0;
}
