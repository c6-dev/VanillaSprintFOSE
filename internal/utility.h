#pragma once

#include "common/IFileStream.h"

const double kRadialConvertion = 1.74532925199433e-02;
#define M_PI	3.1415926535897932
#define M_PI_M2	6.2831853071795864
#define M_PI_D2	1.5707963267948966
#define M_PI_D4	0.7853981633974483

#define GameHeapAlloc(size) ThisCall<void*>(0x86B930, (void*)0x1090A78, size)
#define GameHeapFree(ptr) ThisCall<void*>(0x86BA60, (void*)0x1090A78, ptr)

bool fCompare(float lval, float rval);

int __stdcall lfloor(float value);

int __stdcall lceil(float value);

UInt32 __fastcall GetNextPrime(UInt32 num);

UInt32 __fastcall RGBHexToDec(UInt32 rgb);

UInt32 __fastcall RGBDecToHex(UInt32 rgb);

UInt32 __fastcall StrLen(const char *str);

char* __fastcall StrEnd(const char *str);

bool __fastcall MemCmp(const void *ptr1, const void *ptr2, UInt32 bsize);

void __fastcall MemZero(void *dest, UInt32 bsize);

char* __fastcall StrCopy(char *dest, const char *src);

char* __fastcall StrCat(char *dest, const char *src);

UInt32 __fastcall StrHash(const char *inKey);

bool __fastcall CmprLetters(const char *lstr, const char *rstr);

bool __fastcall StrEqualCS(const char *lstr, const char *rstr);

bool __fastcall StrEqualCI(const char *lstr, const char *rstr);

char __fastcall StrCompare(const char *lstr, const char *rstr);

char __fastcall StrBeginsCS(const char *lstr, const char *rstr);

char __fastcall StrBeginsCI(const char *lstr, const char *rstr);

void __fastcall FixPath(char *str);

void __fastcall StrToLower(char *str);

void __fastcall ReplaceChr(char *str, char from, char to);

char* __fastcall FindChr(const char *str, char chr);

char* __fastcall SubStr(const char *srcStr, const char *subStr);

char* __fastcall SlashPos(const char *str);

char* __fastcall SlashPosR(const char *str);

char* __fastcall GetNextToken(char *str, char delim);

char* __fastcall GetNextToken(char *str, const char *delims);

char* __fastcall CopyString(const char *key);

char* __fastcall IntToStr(int num, char *str);

char* __fastcall FltToStr(float num, char *str);

int __fastcall StrToInt(const char *str);

char* __fastcall UIntToHex(UInt32 num, char *str);

UInt32 __fastcall HexToUInt(const char *str);

bool __fastcall FileExists(const char *path);

void ClearFolder(char *pathEndPtr);

void __fastcall GetTimeStamp(char *buffer);

UInt32 __fastcall ByteSwap(UInt32 dword);

void MakeAllDirs(char* path);