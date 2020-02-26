/*
feednode - feeds in a wordlist and outputs it. Defaults to screen,
but is intended to be piped to a mangeling program via command line.

Ex. feednode file.txt | mangeler file2.txt > results.txt

by Nathanael Warren, 2009
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=2)
        exit(1);
    
    string word;
    
    ifstream feedin(argv[1]);
    while(getline(feedin,word))
        cout << word << "\n";
        
    feedin.close();

return 0;
}
