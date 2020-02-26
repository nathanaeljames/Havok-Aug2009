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


#ifndef FAST_MD4_H
#define FAST_MD4_H


void
fast_MD4(unsigned char *pData, int len, unsigned char *pDigest);


#endif // FAST_MD4_H
