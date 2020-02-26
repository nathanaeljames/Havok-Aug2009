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

void hba_L8_mixalnumsymb14(char candidate[], char permutations[], uint8_t *ts_checksum, uint8_t *enc_data, char year[])
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
	uint8_t clear_data[64];
	uint8_t K[16], K1[16], K2[16], K3[16];
	uint32_t T = 1;
	RC4_KEY data_key;
	uint16_t uni_pwd[128]={0};
	uint8_t k_ipad[100];//65
	uint8_t k_opad[100];//65

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
									//K=MD4(Little_endian(UNICODE(pwd))
									for(int i = 0;i < 8;i++)
										uni_pwd[i] = candidate[i];
									fast_MD4((unsigned char*)uni_pwd,16,K);
									//K1=MD5_HMAC(K,1)
									memset(k_ipad,0,65);
									memset(k_opad,0,65);
									memcpy(k_ipad,K,16);
									memcpy(k_opad,K,16);
									for(int i = 0;i < 64;i++) {
										k_ipad[i] ^= 0x36;
										k_opad[i] ^= 0x5c;
									}
									memcpy(k_ipad+64,(uint8_t*)&T,4);
									fast_MD5(k_ipad,68,K1);
									memcpy(k_opad+64,K1,16);
									fast_MD5(k_opad,80,K1);
									//K3=MD5_HMAC(K1,checksum)
									memset(k_ipad,0,65);
									memset(k_opad,0,65);
									memcpy(k_ipad,K1,16);
									memcpy(k_opad,K1,16);
									for(int i = 0;i < 64;i++) {
										k_ipad[i] ^= 0x36;
										k_opad[i] ^= 0x5c;
									}
									memcpy(k_ipad+64,ts_checksum,16);
									fast_MD5(k_ipad,80,K3);
									memcpy(k_opad+64,K3,16);
									fast_MD5(k_opad,80,K3);
									//clear_data = RC4(K3,encrypted_data)
									RC4_set_key(&data_key,16,K3);
									//decrypt data up to year of timestamp...
									RC4(&data_key,18,enc_data,clear_data);
									//check to ensure year of timestamp
									//is equal to the year packet was captured...
									if(!memcmp(clear_data+14,year,4))
									{
										//reset key
										RC4_set_key(&data_key,16,K3);
										//decrypt entire timestamp
										RC4(&data_key,36,enc_data,clear_data);
										//calculate the checksum
										memset(k_ipad,0,65);
										memset(k_opad,0,65);
										memcpy(k_ipad,K1,16);
										memcpy(k_opad,K1,16);
										for(int i = 0;i < 64;i++) {
											k_ipad[i] ^= 0x36;
											k_opad[i] ^= 0x5c;
										}
										memcpy(k_ipad+64,clear_data,36);
										fast_MD5(k_ipad,100,K2);
										memcpy(k_opad+64,K2,16);
										fast_MD5(k_opad,80,K2);
										//check...
										if(!memcmp(K2,ts_checksum,16))
										{
											cout << "the plaintext is " << candidate << "\n\n";
											wrapUp(SIGINT);
										}
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
									//K=MD4(Little_endian(UNICODE(pwd))
									for(int i = 0;i < 8;i++)
										uni_pwd[i] = candidate[i];
									fast_MD4((unsigned char*)uni_pwd,16,K);
									//K1=MD5_HMAC(K,1)
									memset(k_ipad,0,65);
									memset(k_opad,0,65);
									memcpy(k_ipad,K,16);
									memcpy(k_opad,K,16);
									for(int i = 0;i < 64;i++) {
										k_ipad[i] ^= 0x36;
										k_opad[i] ^= 0x5c;
									}
									memcpy(k_ipad+64,(uint8_t*)&T,4);
									fast_MD5(k_ipad,68,K1);
									memcpy(k_opad+64,K1,16);
									fast_MD5(k_opad,80,K1);
									//K3=MD5_HMAC(K1,checksum)
									memset(k_ipad,0,65);
									memset(k_opad,0,65);
									memcpy(k_ipad,K1,16);
									memcpy(k_opad,K1,16);
									for(int i = 0;i < 64;i++) {
										k_ipad[i] ^= 0x36;
										k_opad[i] ^= 0x5c;
									}
									memcpy(k_ipad+64,ts_checksum,16);
									fast_MD5(k_ipad,80,K3);
									memcpy(k_opad+64,K3,16);
									fast_MD5(k_opad,80,K3);
									//clear_data = RC4(K3,encrypted_data)
									RC4_set_key(&data_key,16,K3);
									//decrypt data up to year of timestamp...
									RC4(&data_key,18,enc_data,clear_data);
									//check to ensure year of timestamp
									//is equal to the year packet was captured...
									if(!memcmp(clear_data+14,year,4))
									{
										//reset key
										RC4_set_key(&data_key,16,K3);
										//decrypt entire timestamp
										RC4(&data_key,36,enc_data,clear_data);
										//calculate the checksum
										memset(k_ipad,0,65);
										memset(k_opad,0,65);
										memcpy(k_ipad,K1,16);
										memcpy(k_opad,K1,16);
										for(int i = 0;i < 64;i++) {
											k_ipad[i] ^= 0x36;
											k_opad[i] ^= 0x5c;
										}
										memcpy(k_ipad+64,clear_data,36);
										fast_MD5(k_ipad,100,K2);
										memcpy(k_opad+64,K2,16);
										fast_MD5(k_opad,80,K2);
										//check...
										if(!memcmp(K2,ts_checksum,16))
										{
											cout << "the plaintext is " << candidate << "\n\n";
											wrapUp(SIGINT);
										}
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