#include <string>
//#include <ctime>
//#include <stdlib.h>//atoi
#include <iostream>
#include <fstream>
//#include "signal.h"//Ctrl+C catch
#include "fast_md4.h"
#include "dense_hash_set"//for the hash table

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

//the following is for google dense_hash hash table:

inline uint32_t rotate( uint32_t x, uint32_t k )
{
 return ( x << k ) | ( x >> ( 32U - k ) ) ;
}

inline void prelim_mix( uint32_t& a, uint32_t& b, uint32_t& c )
{
 a -= c ; a ^= rotate( c, 4U ) ; c += b ;
 b -= a ; b ^= rotate( a, 6U ) ; a += c ;
 c -= b ; c ^= rotate( b, 8U ) ; b += a ;
 a -= c ; a ^= rotate( c, 16U ) ; c += b ;
 b -= a ; b ^= rotate( a, 19U ) ; a += c ;
 c -= b ; c ^= rotate( b, 4U ) ; b += a ;
}

inline void final_mix( uint32_t& a, uint32_t& b, uint32_t& c )
{
 c ^= b ; c -= rotate( b, 14U ) ;
 a ^= c ; a -= rotate( c, 11U ) ;
 b ^= a ; b -= rotate( a, 25U ) ;
 c ^= b ; c -= rotate( b, 16U ) ;
 a ^= c ; a -= rotate( c, 4U ) ;
 b ^= a ; b -= rotate( a, 14U ) ;
 c ^= b ; c -= rotate( b, 24U ) ;
}

enum { NBYTES = 16, NWORDS = NBYTES / sizeof(uint32_t) };

// put the 128 bit hash value in this structure
struct sixteen_byte_hash
{
  sixteen_byte_hash()
  { memset( bytes, 0, NBYTES ) ; }

  sixteen_byte_hash( const uint8_t* array )
  { memcpy( bytes, array, NBYTES ) ; }

  sixteen_byte_hash( const char* array )
  { memcpy( bytes, array, NBYTES ) ; }

  char bytes[NBYTES] ;
};

// hash a 128 bit digest to generate a 32 bit hash
struct hash_sixteen_byte_hash
{
 uint32_t operator() ( const sixteen_byte_hash& value ) const ;
};

// hash a 128 bit digest to generate a 32 bit hash
uint32_t hash_sixteen_byte_hash::operator() ( const sixteen_byte_hash& value ) const
{
 static uint32_t seed = 0U ;

 const uint32_t* words = reinterpret_cast< const uint32_t* > ( value.bytes ) ;

 uint32_t a,b,c ;
 a = b = c = 0xdeadbeef + ( NWORDS << 2U ) + seed ;

 a += words[0] ;
 b += words[1] ;
 c += words[2] ;
 prelim_mix( a, b, c) ;

 a += words[3] ;
 final_mix( a, b, c ) ;

 return c ;
}

// compare two 128 bit hash values to see if they are equal
struct equal_sixteen_byte_hash
{
 inline bool operator() ( const sixteen_byte_hash& first,
                          const sixteen_byte_hash& second ) const
 { return memcmp( first.bytes, second.bytes, NBYTES ) == 0 ; }
};

typedef google::dense_hash_set< sixteen_byte_hash, hash_sixteen_byte_hash,
                             equal_sixteen_byte_hash > hash_set ;

inline void insert_into_hash_set( hash_set& hs, const sixteen_byte_hash& value )
{ hs.insert( value ) ; }

inline bool look_up_in_hash_set( const hash_set& hs, const sixteen_byte_hash& value )
{ return hs.find( value ) != hs.end() ; }

size_t getHash( char szHash[], sixteen_byte_hash& hash )
{
   hash.bytes[0] = hash.bytes[NBYTES-1] = 0xff ;

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
       hash.bytes[i] = (unsigned char)number;
   }
   return(nHashLen);
}

//now we are done working with the google dense_hash hash table

void dump(uint8_t *digest)
{
		for(int i = 0;i < 16;i++)
			printf("%02X",digest[i]);
}

int main(int argc, char *argv[])
{
	if(argc!=2)
		exit(1);

	//initialize the hash_set with these two lines
	hash_set hs;
	hs.set_empty_key(sixteen_byte_hash());//set empty key to all nulls

	sixteen_byte_hash hashbuffer;//buffer to store binary of hashes in

	//open the hash list...
	ifstream hash_list(argv[1]);
	//check to ensure hash list opened correctly
	if(!hash_list.is_open())
	{
		cout<<"Error opening file \'"<<argv[1]<<"\'\n";
		exit(1);
	}

	char shash[33];//temporary array to store hash string in
	while(!hash_list.eof())
	{
		hash_list.getline(shash,33);//get each line of hash file
		getHash(shash,hashbuffer);//convery the string to binary
		insert_into_hash_set(hs,hashbuffer);//store binary hash in hash table
	}

	hash_list.close();//close hash list

	uint8_t K[16];
	string candidate_s;
	char candidate_a[9999];//nope, no passwords over 9999 chars. But really?
	cout << "\n";

	while(getline(cin,candidate_s)){
		//convert the string to an array:
		for(unsigned int i=0;i<candidate_s.size();i++)
			candidate_a[i]=candidate_s[i];
		//encrypt that array:
		fast_MD4((unsigned char*)candidate_a,candidate_s.size(),K);
		//check it out to see if it works...
		if(look_up_in_hash_set(hs,K))
		{
			cout << "plaintext of ";
			dump(K);
			cout << " is " << candidate_s << "\n";
			//exit(1);
		}
	}

return 0;
}
