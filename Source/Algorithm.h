// Algorithm.h
//

#ifndef HUSTMOON_ALGORITHM_H
#define HUSTMOON_ALGORITHM_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

int EncodeRuijie(char *dst, char *src);		//�����������
int DecodeRuijie(char *dst, char *src);		//��������û�������
BYTE Alog(BYTE base);
void Blog(BYTE *circleBase, int num, BYTE *checkSum);

#endif
