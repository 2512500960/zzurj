#pragma once
#ifndef MD5_FROM_MINIEAP_H
#define MD5_FROM_MINIEAP_H
#include "types_minieap.h"

/* MD5 context. */
typedef struct
{
	UINT4 state[4];								   /* state (ABCD) */
	UINT4 count[2];		/* number of bits, modulo 2^64 (lsb first) */
	UCHAR buffer[64];						 /* input buffer */
} MD5_CTX;

void MD5Init1(MD5_CTX * context);
void MD5Update1(MD5_CTX *context, UCHAR *input, UINT4 inputLen);
void MD5Final1(UCHAR digest[16], MD5_CTX *context);

UCHAR* ComputeHash1(UCHAR *src, UINT4 len);

#endif /* MD5_FROM_MINIEAP_H */
