/*
 * Fast implementation of the MD4 message-digest algorithm as per
 * RFC 1320 (see http://tools.ietf.org/html/rfc1320)
 *
 * Author: Joao Inacio <jcinacio at gmail.com>
 * License: Use and share as you wish at your own risk, please keep this header ;)
 *
 * Optimizations:
 *  - For lengths < 16, transformation steps are "unrolled" using macros/defines
 *  - Constants used whenever possible, it's the compiler's job to sort them out
 *  - Padding is done on 4-byte words, and memory copied as last resort.
 */


typedef unsigned int UINT4;


/* MD4 Defines as per RFC reference implementation */

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

#define ROTATE_LEFT(x, n) \
	(((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s) {		\
    (a) += F ((b), (c), (d));		\
	(a) += (x);						\
    (a) = ROTATE_LEFT ((a), (s));	\
}
#define GG(a, b, c, d, x, s) {		\
    (a) += G ((b), (c), (d));		\
	(a) += 0x5a827999 + (x);		\
    (a) = ROTATE_LEFT ((a), (s));	\
}
#define HH(a, b, c, d, x, s) {		\
    (a) += H ((b), (c), (d));		\
	(a) += 0x6ed9eba1 + (x);		\
    (a) = ROTATE_LEFT ((a), (s));	\
}

#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

#define Ca 0x67452301
#define Cb 0xefcdab89
#define Cc 0x98badcfe
#define Cd 0x10325476

/* End MD4 RFC */



/* MD4 optimization macros */

// fast initializer array
static const UINT4 CC[4] = {Ca, Cb, Cc, Cd};

// MD4 transformation steps for all data lengths
#define MD4_steps(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15) { \
	\
	FF (a, b, c, d,  w0, S11);\
	FF (d, a, b, c,  w1, S12);\
	FF (c, d, a, b,  w2, S13);\
	FF (b, c, d, a,  w3, S14);\
	FF (a, b, c, d,  w4, S11);\
	FF (d, a, b, c,  w5, S12);\
	FF (c, d, a, b,  w6, S13);\
	FF (b, c, d, a,  w7, S14);\
	FF (a, b, c, d,  w8, S11);\
	FF (d, a, b, c,  w9, S12);\
	FF (c, d, a, b, w10, S13);\
	FF (b, c, d, a, w11, S14);\
	FF (a, b, c, d, w12, S11);\
	FF (d, a, b, c, w13, S12);\
	FF (c, d, a, b, w14, S13);\
	FF (b, c, d, a, w15, S14);\
	\
	GG (a, b, c, d,  w0, S21);\
	GG (d, a, b, c,  w4, S22);\
	GG (c, d, a, b,  w8, S23);\
	GG (b, c, d, a, w12, S24);\
	GG (a, b, c, d,  w1, S21);\
	GG (d, a, b, c,  w5, S22);\
	GG (c, d, a, b,  w9, S23);\
	GG (b, c, d, a, w13, S24);\
	GG (a, b, c, d,  w2, S21);\
	GG (d, a, b, c,  w6, S22);\
	GG (c, d, a, b, w10, S23);\
	GG (b, c, d, a, w14, S24);\
	GG (a, b, c, d,  w3, S21);\
	GG (d, a, b, c,  w7, S22);\
	GG (c, d, a, b, w11, S23);\
	GG (b, c, d, a, w15, S24);\
	\
	HH (a, b, c, d,  w0, S31);\
	HH (d, a, b, c,  w8, S32);\
	HH (c, d, a, b,  w4, S33);\
	HH (b, c, d, a, w12, S34);\
	HH (a, b, c, d,  w2, S31);\
	HH (d, a, b, c, w10, S32);\
	HH (c, d, a, b,  w6, S33);\
	HH (b, c, d, a, w14, S34);\
	HH (a, b, c, d,  w1, S31);\
	HH (d, a, b, c,  w9, S32);\
	HH (c, d, a, b,  w5, S33);\
	HH (b, c, d, a, w13, S34);\
	HH (a, b, c, d,  w3, S31);\
	HH (d, a, b, c, w11, S32);\
	HH (c, d, a, b,  w7, S33);\
	HH (b, c, d, a, w15, S34);\
}


// len >= 56
#define MD4_transform_add(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15) { \
	\
	a = wOut[0]; b = wOut[1]; c = wOut[2]; d = wOut[3];\
	\
	MD4_steps(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15);\
	\
	wOut[0] += a; wOut[1] += b; wOut[2] += c; wOut[3] += d;\
}

// len < 56
#define MD4_transform_single(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15) { \
	\
	a = CC[0]; b=CC[1]; c=CC[2]; d=CC[3];\
	\
	MD4_steps(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15);\
	\
	wOut[0] = a+Ca; wOut[1] = b+Cb; wOut[2] = c+Cc; wOut[3] = d+Cd;\
}

// len < 16
#define MD4_transform_16(w0, w1, w2, w3, w14) \
	 MD4_transform_single(w0, w1, w2, w3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, w14, 0);


// pad word and append 0x80 at appropriate location
#define MD4_pad_w0()		(0x00000080)
#define MD4_pad_w1(data)	(((data) & 0x000000FF) | 0x00008000)
#define MD4_pad_w2(data)	(((data) & 0x0000FFFF) | 0x00800000)
#define MD4_pad_w3(data)	(((data) & 0x00FFFFFF) | 0x80000000)


#ifndef MD4_pad_w1
static inline UINT4 MD4_pad_w1(UINT4 data)
{
	__asm__ (
		"movb 	%%al, 	%%cl	\n\t"
		"xorl 	%1,		%1		\n\t"
		"orb	$128, 	%%ah	\n\t"
		"movb	%%cl, 	%%al	\n\t"
		"movl 	%1, 	%0		\n\t"
		: "=r" (data)
		: "a" (data)
		: "cl"
	);
	return data;
}
#endif

#ifndef MD4_pad_w3
static inline UINT4 MD4_pad_w3(UINT4 data)
{
	__asm__ (
		"roll 	$8,		%1		\n\t"
		"movb	$128, 	%%al	\n\t"
		"rorl 	$8,		%1		\n\t"
		"movl 	%1, 	%0		\n\t"
		: "=r" (data)
		: "a" (data)
	);
	return data;
}
#endif


static inline void
MD4_copy_pad_block(UINT4 *dData, UINT4 *wIn, int blocklen, int len)
{
	register int cl;

	// copy full words
	for (cl = 0; cl < blocklen; cl++)
		dData[cl] = wIn[cl];

	// copy with padding
	switch (len & 0x03) {
		case 0:
			dData[cl] = MD4_pad_w0();
			break;
		case 1:
			dData[cl] = MD4_pad_w1(wIn[cl]);
			break;
		case 2:
			dData[cl] = MD4_pad_w2(wIn[cl]);
			break;
		case 3:
			dData[cl] = MD4_pad_w3(wIn[cl]);
			break;
	}
	// append 0's
	for (cl++; cl < 14; cl++)
		dData[cl] = 0;
	// append len
	dData[cl++] = (len << 3);
	dData[cl] = (len >> 29);
}



/*
 * fast_MD5()
 *
 */
void
fast_MD4(unsigned char *pData, int len, unsigned char *pDigest)
{
	#define wIn		((UINT4 *)pData)
	#define wOut	((UINT4 *)pDigest)

	register UINT4 a;
	register UINT4 b;
	register UINT4 c;
	register UINT4 d;

	switch (len) {
		case 0:
			MD4_transform_16(MD4_pad_w0(), 0, 0, 0, 8*0);
			return;
		case 1:
			MD4_transform_16(MD4_pad_w1(wIn[0]), 0, 0, 0, 8*1);
			return;
		case 2:
			MD4_transform_16(MD4_pad_w2(wIn[0]), 0, 0, 0, 8*2);
			return;
		case 3:
			MD4_transform_16(MD4_pad_w3(wIn[0]), 0, 0, 0, 8*3);
			return;
		case 4:
			MD4_transform_16(wIn[0], MD4_pad_w0(), 0, 0, 8*4);
			return;
		case 5:
			MD4_transform_16(wIn[0], MD4_pad_w1(wIn[1]), 0, 0, 8*5);
			return;
		case 6:
			MD4_transform_16(wIn[0], MD4_pad_w2(wIn[1]), 0, 0, 8*6);
			return;
		case 7:
			MD4_transform_16(wIn[0], MD4_pad_w3(wIn[1]), 0, 0, 8*7);
			return;
		case 8:
			MD4_transform_16(wIn[0], wIn[1], MD4_pad_w0(), 0, 8*8);
			return;
		case 9:
			MD4_transform_16(wIn[0], wIn[1], MD4_pad_w1(wIn[2]), 0, 8*9);
			return;
		case 10:
			MD4_transform_16(wIn[0], wIn[1], MD4_pad_w2(wIn[2]), 0, 8*10);
			return;
		case 11:
			MD4_transform_16(wIn[0], wIn[1], MD4_pad_w3(wIn[2]), 0, 8*11);
			return;
		case 12:
			MD4_transform_16(wIn[0], wIn[1], wIn[2], MD4_pad_w0(), 8*12);
			return;
		case 13:
			MD4_transform_16(wIn[0], wIn[1], wIn[2], MD4_pad_w1(wIn[3]), 8*13);
			return;
		case 14:
			MD4_transform_16(wIn[0], wIn[1], wIn[2], MD4_pad_w2(wIn[3]), 8*14)
			return;
		case 15:
			MD4_transform_16(wIn[0], wIn[1], wIn[2], MD4_pad_w3(wIn[3]), 8*15)
			return;
	}

	// data block used for padding
	UINT4 dData[16];

	if (len < 56) {
		// 16 < length < 56

		MD4_copy_pad_block(dData, wIn, (len >> 2), len);

		// redefine data input, point to padded data
		#undef	wIn
		#define wIn		dData

		MD4_transform_single(
			wIn[ 0], wIn[ 1], wIn[ 2], wIn[ 3], wIn[ 4], wIn[ 5], wIn[ 6], wIn[ 7],
			wIn[ 8], wIn[ 9], wIn[10], wIn[11], wIn[12], wIn[13], wIn[14], wIn[15]
		);

		#undef	wIn
		#define wIn		((UINT4 *)pData)

		return;
	} else {
		// len >= 56

		// original len
		int tlen = len;

		// init digest for long lens
		wOut[0] = Ca; wOut[1] = Cb; wOut[2] = Cc; wOut[3] = Cd;

		while (tlen >= 64) {
			// Process 64-byte chunks
			MD4_transform_add(
				wIn[ 0], wIn[ 1], wIn[ 2], wIn[ 3], wIn[ 4], wIn[ 5], wIn[ 6], wIn[ 7],
				wIn[ 8], wIn[ 9], wIn[10], wIn[11], wIn[12], wIn[13], wIn[14], wIn[15]
			);

			tlen -= 64;
			pData += 64;
		}

		if (tlen >= 56) {
			// Process > 56-byte chunk

			int cl = (tlen >> 2);
			// perform padding on last 2 byte
			if (cl > 14) {
				dData[14] = wIn[14];
			} else {
				dData[15] = 0;
			}
			// copy 1 word with padding byte
			switch (len & 0x03) {
				case 0:
					dData[cl] = MD4_pad_w0();
					break;
				case 1:
					dData[cl] = MD4_pad_w1(wIn[cl]);
					break;
				case 2:
					dData[cl] = MD4_pad_w2(wIn[cl]);
					break;
				case 3:
					dData[cl] = MD4_pad_w3(wIn[cl]);
					break;
			}

			// transform
			MD4_transform_add(
				wIn[ 0], wIn[ 1], wIn[ 2], wIn[ 3], wIn[ 4], wIn[ 5], wIn[ 6], wIn[ 7],
				wIn[ 8], wIn[ 9], wIn[10], wIn[11], wIn[12], wIn[13], dData[14], dData[15]
			);
			// final transform
			#define w14		(len << 3)
			#define w15		(len >> 29)
			MD4_transform_add(
					0,	    0,		0,		0,		0, 		0,		0,		0,
					0, 		0,		0,		0,		0,		0,    w14,	  w15
			);
			#undef	w14
			#undef	w15
		} else {
			// (len mod 64) < 56

			MD4_copy_pad_block(dData, wIn, (tlen >> 2), len);

			#undef	wIn
			#define wIn		dData

			// transform
			MD4_transform_add(
				wIn[ 0], wIn[ 1], wIn[ 2], wIn[ 3], wIn[ 4], wIn[ 5], wIn[ 6], wIn[ 7],
				wIn[ 8], wIn[ 9], wIn[10], wIn[11], wIn[12], wIn[13], wIn[14], wIn[15]
			);

			#undef 	wIn
		}
	}

	/* end of fast_MD4() */
}




/*	compile with "-DMAKE_TEST -lssl" to enable testing of hash validity */

#ifdef MAKE_TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md4.h>


int main(int argc, char* argv[])
{
	unsigned char plain[122] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=~`[]{}|\\:;\"'<>,.?/ abcdefghijklmnopqrstuvwxyz";

	#define MAXTESTLEN	122

	unsigned char *pHash  = (unsigned char *)malloc(16);
	unsigned char *pHashOssl  = (unsigned char *)malloc(16);


	int len, i, result = 0;
	for (len = 0; len < MAXTESTLEN; len++)
	{
		fast_MD4(plain, len, pHash);

		MD4(plain, len, pHashOssl);

		printf("Length %d: ", len);

		if ( memcmp(pHash, pHashOssl, 16)  == 0) {
			printf("PASS");
		} else {
			printf("FAIL \n");
			for (i = 0;  i < 16; i++) printf("%02x", pHash[i]);
			printf(" != ");
			for (i = 0;  i < 16; i++) printf("%02x", pHashOssl[i]);

			result = 1;
		}

		printf("\n");
	}

	free(pHash);
	free(pHashOssl);

	return 0;
}

#endif
