#ifndef CHECKV4_H
#define CHECKV4_H

extern "C" { __declspec(dllexport) unsigned char *computeV4(const unsigned char *src, int len); }
__declspec(dllexport) char *computePwd(const unsigned char *md5, const char* username, const char* password);
#endif
