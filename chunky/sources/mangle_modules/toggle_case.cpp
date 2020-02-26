/*
toggle_case - toggles the case of the first characters of wordlist
by Nathanael Warren, 2009
*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string wordin;
	string wordout;

    while(getline(cin,wordin)){
        wordout=wordin;
        if(argc>1 && !strcmp(argv[1],"-a"))
           cout << wordin << "\n";
		if(wordin[0]=='a')
            wordout[0]='A';
        if(wordin[0]=='A')
            wordout[0]='a';
        if(wordin[0]=='b')
            wordout[0]='B';
        if(wordin[0]=='B')
            wordout[0]='b';
        if(wordin[0]=='c')
            wordout[0]='C';
        if(wordin[0]=='C')
            wordout[0]='c';
        if(wordin[0]=='d')
            wordout[0]='D';
        if(wordin[0]=='D')
            wordout[0]='d';
        if(wordin[0]=='e')
            wordout[0]='E';
        if(wordin[0]=='E')
            wordout[0]='e';
        if(wordin[0]=='f')
            wordout[0]='F';
        if(wordin[0]=='F')
            wordout[0]='f';
        if(wordin[0]=='g')
            wordout[0]='G';
        if(wordin[0]=='G')
            wordout[0]='g';
        if(wordin[0]=='h')
            wordout[0]='H';
        if(wordin[0]=='H')
            wordout[0]='h';
        if(wordin[0]=='i')
            wordout[0]='I';
        if(wordin[0]=='I')
            wordout[0]='i';
        if(wordin[0]=='j')
            wordout[0]='J';
        if(wordin[0]=='J')
            wordout[0]='j';
        if(wordin[0]=='k')
            wordout[0]='K';
        if(wordin[0]=='K')
            wordout[0]='k';
        if(wordin[0]=='l')
            wordout[0]='L';
        if(wordin[0]=='L')
            wordout[0]='l';
        if(wordin[0]=='m')
            wordout[0]='M';
        if(wordin[0]=='M')
            wordout[0]='m';
        if(wordin[0]=='n')
            wordout[0]='N';
        if(wordin[0]=='N')
            wordout[0]='n';
        if(wordin[0]=='o')
            wordout[0]='O';
        if(wordin[0]=='O')
            wordout[0]='o';
        if(wordin[0]=='p')
            wordout[0]='P';
        if(wordin[0]=='P')
            wordout[0]='p';
        if(wordin[0]=='q')
            wordout[0]='Q';
        if(wordin[0]=='Q')
            wordout[0]='q';
        if(wordin[0]=='r')
            wordout[0]='R';
        if(wordin[0]=='R')
            wordout[0]='r';
        if(wordin[0]=='s')
            wordout[0]='S';
        if(wordin[0]=='S')
            wordout[0]='s';
        if(wordin[0]=='t')
            wordout[0]='T';
        if(wordin[0]=='T')
            wordout[0]='t';
        if(wordin[0]=='u')
            wordout[0]='U';
        if(wordin[0]=='U')
            wordout[0]='u';
        if(wordin[0]=='v')
            wordout[0]='V';
        if(wordin[0]=='V')
            wordout[0]='v';
        if(wordin[0]=='w')
            wordout[0]='W';
        if(wordin[0]=='W')
            wordout[0]='w';
        if(wordin[0]=='x')
            wordout[0]='X';
        if(wordin[0]=='X')
            wordout[0]='x';
        if(wordin[0]=='y')
            wordout[0]='Y';
        if(wordin[0]=='Y')
            wordout[0]='y';
        if(wordin[0]=='z')
            wordout[0]='Z';
        if(wordin[0]=='Z')
            wordout[0]='z';
		cout << wordout << "\n";
	}
	
return 0;
}
