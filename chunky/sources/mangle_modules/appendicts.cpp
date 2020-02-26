/*
appendicts - appends dictionary words to dictionary words
by Nathanael Warren, 2009
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc<2)
        exit(1);

    vector<string> vec_wordlist_join;

    string word;
    
    //read in wordlist whose words will be concatenated to each word piped in...
	ifstream wordlistfilejoin(argv[1]);
	if(!wordlistfilejoin.is_open())
		exit(1);

	while(getline(wordlistfilejoin,word))
		vec_wordlist_join.push_back(word);

	wordlistfilejoin.close();

    while(getline(cin,word)){
        if(argc>2 && !strcmp(argv[2],"-a"))
                  cout << word << "\n";
        for(int c=0;c<vec_wordlist_join.size();c++)
            cout << word << vec_wordlist_join[c] << "\n";
    }

return 0;
}
