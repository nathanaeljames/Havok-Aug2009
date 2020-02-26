#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>//(for atoi to work)

using namespace std;

void usage()
{
	cout << "Usage: <input1> <input2> <output>\n";
	cout << "\n see README for more details.\n";
	exit(1);
}

int main(int argc, char *argv[])
{
	cout << "\nshmoosh - concatenates and uniques wordlists into one\n";
	cout << "\tby Nathanael Warren, 2009\n\n";

	if(argc!=4)
		usage();

	vector<string> vec_wordlist_compilation;

///////////////////////////input1//////////////////////////////

	ifstream wordlistfile(argv[1]);
	if(!wordlistfile.is_open())
	{
		cout<<"\nError opening file \'"<<argv[1]<<"\'\n";
		exit(1);
	}
	int x=0;
	string word;
	while(getline(wordlistfile,word)){
		vec_wordlist_compilation.push_back(word);
		x++;
	}
	cout << x << " words loaded from file \'"<<argv[1]<<"\'\n";

	wordlistfile.close();

	///////////////////////////input2//////////////////////////////

	ifstream wordlistfiletwo(argv[2]);
	if(!wordlistfiletwo.is_open())
	{
		cout<<"\nError opening file \'"<<argv[2]<<"\'\n";
		exit(1);
	}
	int v=0;
	while(getline(wordlistfiletwo,word)){
		vec_wordlist_compilation.push_back(word);
		v++;
	}
	cout << v << " words loaded from file \'"<<argv[2]<<"\'\n";

	wordlistfiletwo.close();

////////////////////////////sort//////////////////////////////
	cout << "\nsorting " << v+x << " words, removing duplicates...\n";

	//sort vector (least to greatest)...
	sort(vec_wordlist_compilation.begin(),vec_wordlist_compilation.end());
	//remove duplicates...
	vec_wordlist_compilation.resize((unique(vec_wordlist_compilation.begin(),vec_wordlist_compilation.end()))-vec_wordlist_compilation.begin());

	/*for(unsigned int c=0;c<vec_wordlist_compilation.size();c++)
		cout << vec_wordlist_compilation[c] << "\n";*/
	cout << vec_wordlist_compilation.size() << " unique words remain.\n";

////////////////////////////output//////////////////////////////

	ofstream output(argv[3]);
	for(unsigned int c=0;c<vec_wordlist_compilation.size();c++)
		output << vec_wordlist_compilation[c] << "\n";

return 0;
}