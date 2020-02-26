/* divvy - Finds the commands to distribute Havok to a specified
   number of processing cores. By Nathanael Warren, 2009.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>//(for atoi to work)
#include "BigIntegerLibrary.hh"
using namespace std;

void usage()
{
	 cout << " Usage: <threads to spawn> <password length> <charset file>\n";
     cout << "\n see README for more details.\n";
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
    cout << "\ndivvy - finds commands for Havok distribution\n";
    cout << "\tby Nathanael Warren, 2009\n\n";

    if(argc!=4)
    {
       usage();
       return 1;
    }

	//process command line options...
	int threads = atoi(argv[1]);
	BigInteger bthreads = threads;
	int passlen = atoi(argv[2]);
    
    //open charsets file...
    ifstream charsetsfile(argv[3]);
    //ensure charsets is open...
    if (!charsetsfile.is_open())
    {
        cout<<"\nError opening file \'"<<argv[3]<<"\'\n";
        exit(1);
    }

    //store the charsets in a vector 'vec_charsets'
    char charset[100];//temporary array
    vector<string> vec_charsets;//array to store charsets in
	int charsetlen=0;//test for length comparison
    
    for(int i=0;i<passlen && !charsetsfile.eof();i++)
	{
        charsetsfile.getline(charset,99); //read sample file line by line
		if(strlen(charset)!=charsetlen && i!=0)
		{
			cout << "inconsistent charset lengths for range ";
			cout << passlen << " in file \'"<<argv[3]<<"\'!\n";
			exit(1);
		}
		charsetlen=strlen(charset);
        vec_charsets.push_back(charset);//store in vector 'vec_charsets'
    }

	//close charsets file
    charsetsfile.close();

	BigInteger bcharsetlen = charsetlen;
	//find total keyspace...
	BigInteger bkeyspace = bigpow(bcharsetlen,passlen);
	//find sub keyspace (keyspace per process)...
	BigInteger bsubrange = bkeyspace / bthreads;
	//find remainder of division...
	BigInteger bremainder = bkeyspace % bthreads;

	//store the subranges in a vector called 'vec_subranges'
	vector<BigInteger> vec_subranges;
	BigInteger bsubtostore(bsubrange);//for remainder compensation

	for(int i=0;i<threads;i++)
	{
		bsubtostore=bsubrange;
		if(bremainder!=0)//compensate for remainders
		{
			bsubtostore++;
			bremainder--;
		}
		vec_subranges.push_back(bsubtostore);
	}

	vector<char> vec_startword;
	//set the initial start word...
	for(size_t i=0;i<vec_charsets.size();++i)
	{
		vec_startword.push_back(vec_charsets[i][0]);
	}

	//print initial command...
	//cout << "Havokv" << argv[2] << " ";
	for(size_t i=0;i<vec_startword.size();++i)
	{
		cout << vec_startword[i];
	}
	cout << " " << vec_subranges[0] << "\n";

	//set initial positions to zero...
	vector<int> vec_position;
	for(int i=0;i<passlen;i++)
	{
		vec_position.push_back(0);
	}

for(int c=0;c<threads-1;c++)//for each command...
{
	vector<int> vec_permute;
	BigInteger blefttocover= vec_subranges[c];
	//find the neccessary permutations to each position and store them
	//(backwards) in vector 'vec_permute'...
	int permute;
	for(int i=passlen;i>=1;i--)
	{
		permute=(blefttocover/(bigpow(bcharsetlen,i-1))).toInt();
		vec_permute.push_back(permute);
		blefttocover=blefttocover%(bigpow(bcharsetlen,i-1));
	}

	//immeadiately permutate accordingly...

	//generate the startword...
	for(int i=vec_permute.size()-1,ppos=0;i!=-1;--i,ppos++)//iterate through vector backward (forward)
	{
		for(int perm=0;perm<vec_permute[i];perm++)//for the number of permutations...
		{
			//increment position ppos vec_permute[i] times...
			for(int x=0;;x++)
			{
				if(vec_position[ppos+x]!=charsetlen-1)
				{
					vec_position[ppos+x]++;
					vec_startword[ppos+x]=vec_charsets[ppos+x][vec_position[ppos+x]];
					break;
				}
				if(vec_position[ppos+x]==charsetlen-1)
				{
					vec_position[ppos+x]=0;
					vec_startword[ppos+x]=vec_charsets[ppos+x][0];
				}		
			}
		}
	}

	//print command...
	//cout << "Havokv" << argv[2] << " ";
	for(size_t i=0;i<vec_startword.size();++i)
	{
		cout << vec_startword[i];
	}
	cout << " " << vec_subranges[c+1] << "\n";
}

return 0;
}
