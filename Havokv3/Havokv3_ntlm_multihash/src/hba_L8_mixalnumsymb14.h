inline void reset_mixalnumsymb14_L8(char candidate[], unsigned int position[])
{
	char charset0[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset1[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset2[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset3[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset4[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset5[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset6[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset7[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";

	//set the charset position for first character of candidate
	for(int i=0;position[0]==666;i++)
		if(candidate[0]==charset0[i])
			position[0]=i;	
	//set the charset position for second character of candidate
	for(int i=0;position[1]==666;i++)
		if(candidate[1]==charset1[i])
			position[1]=i;
	//set the charset position for third character of candidate
	for(int i=0;position[2]==666;i++)
		if(candidate[2]==charset2[i])
			position[2]=i;
	//set the charset position for fourth character of candidate
	for(int i=0;position[3]==666;i++)
		if(candidate[3]==charset3[i])
			position[3]=i;
	//set the charset position for fifth character of candidate
	for(int i=0;position[4]==666;i++)
		if(candidate[4]==charset4[i])
			position[4]=i;
	//set the charset position for sixth character of candidate
	for(int i=0;position[5]==666;i++)
		if(candidate[5]==charset5[i])
			position[5]=i;
	//set the charset position for seventh character of candidate
	for(int i=0;position[6]==666;i++)
		if(candidate[6]==charset6[i])
			position[6]=i;
	//set the charset position for eigth character of candidate
	for(int i=0;position[7]==666;i++)
		if(candidate[7]==charset7[i])
			position[7]=i;
}

void hba_L8_mixalnumsymb14(char candidate[], char permutations[], hash_set& hs)
{
	//frequency analysis - etaoinshrdlucmfwypvbgkqjxz
	char charset0[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset1[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset2[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset3[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset4[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset5[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset6[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	char charset7[] = "e1nsra326yt0d954o78lkgmihbpcxuwfzjvq!ESANRDYBTO*LHMGKCX@PI$#U-ZWFJ_Q+^V)%=&(";
	unsigned short int charcount=76;
	unsigned short int maxpos=charcount-1;
	unsigned int permutated=0;
	unsigned int position[]={666,666,666,666,666,666,666,666};
	
	//algorithm-specific initiations...
	uint8_t K[16];
	uint16_t uni_pwd[128]={0};
	//MD4_CTX ctx;

	/*the following code block deals with the BigInteger library (v2008.07.20)
	BigInteger library arithmetic is not used in the actual cracker loop,
	do to its slow operation*/

	//permutations must be less than 4 609 609 000 000 000 000
	//convert array "permutations" to BigInteger "permutations"...
	BigInteger bpermutations = stringToBigInteger(permutations);
	//make a BigInt representing the largest value that C++ int
	//can hold..
	BigInteger cpphandle(2147000000);
	//find out how many primary cracker loops using C++ int are
	//needed to cover the range of permutations...
	BigInteger bcpplnum = bpermutations / cpphandle;
	//find the remainder to be fed into the second cracker loop...
	BigInteger bremainder = bpermutations % cpphandle;
	//store BigInteger bcpplnum to unsigned long int cpplnum
	unsigned int cpplnum = bcpplnum.toInt();
	//store BigInteger bremainder to unsigned long int remainder
	unsigned int remainder = bremainder.toInt();

	position[0]=position[1]=position[2]=position[3]=position[4]=position[5]=position[6]=position[7]=666;//set positions to garbage
	reset_mixalnumsymb14_L8(candidate,position);//reset positions from password

	//start timer...
	clock_t begin = clock();

//this is the outermost cracker loop 1. This code is only called ~ every 2 billion permutations,
//speed is still essential, however, attempt to optimize...
for(unsigned int i=1;i<=cpplnum;i++)
{
    //this is the innermost cracker loop 1. Code inside of here must be optimized for max efficiency...
	for(;permutated<=2147000000 && position[7]<charcount;position[7]++)
	{
		candidate[7]=charset7[position[7]];
		for(;permutated<=2147000000 && position[6]<charcount;position[6]++)
		{
			candidate[6]=charset6[position[6]];
			for(;permutated<=2147000000 && position[5]<charcount;position[5]++)
			{
				candidate[5]=charset5[position[5]];
				for(;permutated<=2147000000 && position[4]<charcount;position[4]++)
				{
					candidate[4]=charset4[position[4]];
					for(;permutated<=2147000000 && position[3]<charcount;position[3]++)
					{
						candidate[3]=charset3[position[3]];
						for(;permutated<=2147000000 && position[2]<charcount;position[2]++)
						{
							candidate[2]=charset2[position[2]];
							for(;permutated<=2147000000 && position[1]<charcount;position[1]++)
							{
								candidate[1]=charset1[position[1]];
								for(;permutated<=2147000000 && position[0]<charcount;position[0]++)
								{
									candidate[0]=charset0[position[0]];
									//this is the actual password test function...
									permutated++;
									//cout << candidate << "\n";
									for(unsigned int i = 0;i < 8;i++)
										uni_pwd[i] = candidate[i];
									//MD4_Init(&ctx);
									//MD4_Update(&ctx,uni_pwd,16);
									//MD4_Final(K,&ctx);
									fast_MD4((unsigned char*)uni_pwd,16,K);
									//dump(K);
									if(look_up_in_hash_set(hs,K))
									{
										cout << "plaintext of ";
										dump(K);
										cout << " is " << candidate << "\n";
									}
									//end of test function...
								}
								position[0]=0;
							}
							position[1]=0;
						}
						position[2]=0;
					}
					position[3]=0;
				}
				position[4]=0;
			}
			position[5]=0;
		}
		position[6]=0;
	}//end of innermost cracker loop 1.
	
	position[0]=position[1]=position[2]=position[3]=position[4]=position[5]=position[6]=position[7]=666;//set positions to garbage
	reset_mixalnumsymb14_L8(candidate,position);//reset positions from password

	//reset permutated counter to zero...
	permutated = 0;
	//this code helps prevent current candidate from being tested again on next loop...
	if(position[0]<maxpos){
		position[0]++;
		candidate[0]=charset0[position[0]];
	}
}//end of outermost cracker loop 1.

//this is cracker loop 2. Its purpose is to process the remaining number of permutations
	position[0]=position[1]=position[2]=position[3]=position[4]=position[5]=position[6]=position[7]=666;//set positions to garbage
	reset_mixalnumsymb14_L8(candidate,position);//reset positions from password

	for(;permutated<=remainder && position[7]<charcount;position[7]++)
	{
		candidate[7]=charset7[position[7]];
		for(;permutated<=remainder && position[6]<charcount;position[6]++)
		{
			candidate[6]=charset6[position[6]];
			for(;permutated<=remainder && position[5]<charcount;position[5]++)
			{
				candidate[5]=charset5[position[5]];
				for(;permutated<=remainder && position[4]<charcount;position[4]++)
				{
					candidate[4]=charset4[position[4]];
					for(;permutated<=remainder && position[3]<charcount;position[3]++)
					{
						candidate[3]=charset3[position[3]];
						for(;permutated<=remainder && position[2]<charcount;position[2]++)
						{
							candidate[2]=charset2[position[2]];
							for(;permutated<=remainder && position[1]<charcount;position[1]++)
							{
								candidate[1]=charset1[position[1]];
								for(;permutated<=remainder && position[0]<charcount;position[0]++)
								{
									candidate[0]=charset0[position[0]];
									//this is the actual password test function...
									permutated++;
									//cout << candidate << "\n";
									for(unsigned int i = 0;i < 8;i++)
										uni_pwd[i] = candidate[i];
									//MD4_Init(&ctx);
									//MD4_Update(&ctx,uni_pwd,16);
									//MD4_Final(K,&ctx);
									fast_MD4((unsigned char*)uni_pwd,16,K);
									//dump(K);
									if(look_up_in_hash_set(hs,K))
									{
										cout << "plaintext of ";
										dump(K);
										cout << " is " << candidate << "\n";
									}
									//end of test function...
								}
								position[0]=0;
							}
							position[1]=0;
						}
						position[2]=0;
					}
					position[3]=0;
				}
				position[4]=0;
			}
			position[5]=0;
		}
		position[6]=0;
	}
//end of cracker loop 2
	clock_t end = clock() ;//stop timer
	cout << "\nended on " << candidate << "\n";
	cout << bpermutations << " words in " << double(end-begin) / CLOCKS_PER_SEC << " seconds\n" ;
}