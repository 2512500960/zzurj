// Algorithm.h
//

#ifndef HUSTMOON_ALGORITHM_H
#define HUSTMOON_ALGORITHM_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

int EncodeRuijie(char *dst, char *src);		//加密锐捷密码
int DecodeRuijie(char *dst, char *src);		//解密锐捷用户名密码
BYTE Alog(BYTE base);
void Blog(BYTE *circleBase, int num, BYTE *checkSum);

#endif
