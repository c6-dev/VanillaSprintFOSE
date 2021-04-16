#pragma once

#include "internal/utility.h"
#include "nvse/GameAPI.h"
#include "internal/md5/md5.h"
#include <time.h>

const UInt32 kGameHeapAllocAddr = 0x86B930, kGameHeapFreeAddr = 0x86BA60;

__declspec(naked) void* __stdcall GameHeapAlloc(UInt32 size)
{
	__asm
	{
		mov		ecx, 0x1090A78
		jmp		kGameHeapAllocAddr
	}
}

__declspec(naked) void __stdcall GameHeapFree(void *ptr)
{
	__asm
	{
		mov		ecx, 0x1090A78
		jmp		kGameHeapFreeAddr
	}
}

bool fCompare(float lval, float rval)
{
	return fabs(lval - rval) < FLT_EPSILON;
}

float invSqrt(float value)
{
	float hlfVal = 0.5F * value;
	int intVal = 0x5F375A86 - (*(int*)&value >> 1);
	value = *(float*)&intVal;
	for (char iter = 3; iter; iter--)
		value *= 1.5F - (hlfVal * value * value);
	return 1 / value;
}

double invSqrt(double value)
{
	double hlfVal = 0.5 * value;
	long long intVal = 0x5FE6EB50C7B537A9 - (*(long long*)&value >> 1);
	value = *(double*)&intVal;
	for (char iter = 3; iter; iter--)
		value *= 1.5 - (hlfVal * value * value);
	return 1 / value;
}

__declspec(naked) int __stdcall lfloor(float value)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		push	ecx
		fstcw	[ebp-4]
		mov		ax, [ebp-4]
		or		word ptr [ebp-4], 0x400
		fldcw	[ebp-4]
		fld		dword ptr [ebp+8]
		fistp	dword ptr [ebp+8]
		mov		[ebp-4], ax
		fldcw	[ebp-4]
		mov		eax, [ebp+8]
		mov		esp, ebp
		pop		ebp
		retn	4
	}
}

__declspec(naked) int __stdcall lceil(float value)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		push	ecx
		fstcw	[ebp-4]
		mov		ax, [ebp-4]
		or		word ptr [ebp-4], 0x800
		fldcw	[ebp-4]
		fld		dword ptr [ebp+8]
		fistp	dword ptr [ebp+8]
		mov		[ebp-4], ax
		fldcw	[ebp-4]
		mov		eax, [ebp+8]
		mov		esp, ebp
		pop		ebp
		retn	4
	}
}

__declspec(naked) int __fastcall ashr(UInt8 bits, int value)
{
	__asm
	{
		mov		eax, edx
		sar		eax, cl
		retn
	}
}

UInt32 __fastcall GetNextPrime(UInt32 num)
{
	if (num <= 2) return 2;
	else if (num == 3) return 3;
	UInt32 a = num / 6, b = num - (6 * a), c = (b < 2) ? 1 : 5, d;
	num = (6 * a) + c;
	a = (3 + c) / 2;
	do {
		b = 4;
		c = 5;
		do {
			d = num / c;
			if (c > d) return num;
			if (num == (c * d)) break;
			c += b ^= 6;
		} while (true);
		num += a ^= 6;
	} while (true);
	return num;
}

UInt32 __fastcall RGBHexToDec(UInt32 rgb)
{
	UInt8 *colors = (UInt8*)&rgb;
	return (colors[0] * 1000000) + (colors[1] * 1000) + colors[2];
}

UInt32 __fastcall RGBDecToHex(UInt32 rgb)
{
	return (rgb / 1000000) + (((rgb / 1000) % 1000) << 8) + ((rgb % 1000) << 16);
}

__declspec(naked) UInt32 __fastcall StrLen(const char *str)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
	iterHead:
		cmp		[eax], 0
		jz		done
		inc		eax
		jmp		iterHead
	done:
		sub		eax, ecx
		retn
	}
}

__declspec(naked) char* __fastcall StrEnd(const char *str)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
	iterHead:
		cmp		[eax], 0
		jz		done
		inc		eax
		jmp		iterHead
	done:
		retn
	}
}

__declspec(naked) void _MemCopy()
{
	__asm
	{
	copy16:
		cmp		ebx, 0x10
		jb		copy8
		movdqu	xmm0, qword ptr [edx]
		movdqu	qword ptr [eax], xmm0
		add		edx, 0x10
		add		eax, 0x10
		sub		ebx, 0x10
		jnz		copy16
		jmp		done
	copy8:
		cmp		bl, 8
		jb		copy4
		movq	xmm0, qword ptr [edx]
		movq	qword ptr [eax], xmm0
		add		edx, 8
		add		eax, 8
		sub		bl, 8
		jz		done
	copy4:
		test	bl, bl
		jz		done
		cmp		bl, 4
		jb		copy1
		mov		ecx, [edx]
		mov		[eax], ecx
		add		edx, 4
		add		eax, 4
		sub		bl, 4
		jz		done
	copy1:
		mov		cl, [edx]
		mov		[eax], cl
		inc		edx
		inc		eax
		dec		bl
		jnz		copy1
	done:
		retn
	}
}

__declspec(naked) void _MemRCopy()
{
	__asm
	{
	copy16:
		cmp		ebx, 0x10
		jb		copy8
		sub		ebx, 0x10
		movdqu	xmm0, qword ptr [edx+ebx]
		movdqu	qword ptr [eax+ebx], xmm0
		jnz		copy16
		jmp		done
	copy8:
		cmp		bl, 8
		jb		copy4
		sub		bl, 8
		movq	xmm0, qword ptr [edx+ebx]
		movq	qword ptr [eax+ebx], xmm0
		jz		done
	copy4:
		test	bl, bl
		jz		done
		cmp		bl, 4
		jb		copy1
		sub		bl, 4
		mov		ecx, dword ptr [edx+ebx]
		mov		dword ptr [eax+ebx], ecx
		jz		done
	copy1:
		dec		bl
		mov		cl, [edx+ebx]
		mov		[eax+ebx], cl
		jnz		copy1
	done:
		retn
	}
}

__declspec(naked) void __fastcall MemCopy(void *dest, const void *src, UInt32 bsize)
{
	__asm
	{
		push	ebx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		done
		mov		eax, ecx
		mov		ebx, [esp+8]
		cmp		eax, edx
		ja		revCopy
		call	_MemCopy
		jmp		done
	revCopy:
		call	_MemRCopy
	done:
		pop		ebx
		retn	4
	}
}

__declspec(naked) bool __fastcall MemCmp(const void *ptr1, const void *ptr2, UInt32 bsize)
{
	__asm
	{
		push	ebx
		mov		ebx, [esp+8]
	iterHead:
		mov		eax, [ecx]
		cmp		[edx], eax
		jnz		retnFalse
		add		ecx, 4
		add		edx, 4
		sub		ebx, 4
		jnz		iterHead
		mov		al, 1
		jmp		done
	retnFalse:
		xor		al, al
	done:
		pop		ebx
		retn	4
	}
}

__declspec(naked) void __fastcall MemZero(void *dest, UInt32 bsize)
{
	__asm
	{
		test	ecx, ecx
		jz		done
		pxor	xmm0, xmm0
	copy16:
		cmp		edx, 0x10
		jb		copy8
		movdqu	qword ptr [ecx], xmm0
		add		ecx, 0x10
		sub		edx, 0x10
		jnz		copy16
		jmp		done
	copy8:
		test	dl, dl
		jz		done
		cmp		dl, 8
		jb		copy4
		movq	qword ptr [ecx], xmm0
		add		ecx, 8
		sub		dl, 8
		jz		done
	copy4:
		mov		dword ptr [ecx], 0
	done:
		retn
	}
}

__declspec(naked) char* __fastcall StrCopy(char *dest, const char *src)
{
	__asm
	{
		push	ebx
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		done
		xor		ebx, ebx
	getSize:
		cmp		[edx+ebx], 0
		jz		doCopy
		inc		ebx
		jmp		getSize
	doCopy:
		call	_MemCopy
		mov		[eax], 0
	done:
		pop		ebx
		retn
	}
}

__declspec(naked) char* __fastcall StrCat(char *dest, const char *src)
{
	__asm
	{
		call	StrEnd
		mov		ecx, eax
		call	StrCopy
		retn
	}
}

__declspec(naked) UInt32 __fastcall StrHash(const char *inKey)
{
	__asm
	{
		xor		eax, eax
		test	ecx, ecx
		jz		done
		xor		edx, edx
	iterHead:
		mov		dl, [ecx]
		cmp		dl, 'Z'
		jg		notCap
		test	dl, dl
		jz		done
		cmp		dl, 'A'
		jl		notCap
		or		dl, 0x20
	notCap:
		imul	eax, 0x65
		add		eax, edx
		inc		ecx
		jmp		iterHead
	done:
		retn
	}
}

__declspec(naked) bool __fastcall CmprLetters(const char *lstr, const char *rstr)
{
	__asm
	{
		mov		al, [ecx]
		cmp		[edx], al
		jz		retnTrue
		cmp		al, 'A'
		jl		retnFalse
		cmp		al, 'z'
		jg		retnFalse
		cmp		al, 'Z'
		jle		isCap
		cmp		al, 'a'
		jl		retnFalse
	isCap:
		xor		al, 0x20
		cmp		[edx], al
		jz		retnTrue
	retnFalse:
		xor		al, al
		retn
	retnTrue:
		mov		al, 1
		retn
	}
}

__declspec(naked) bool __fastcall StrEqualCS(const char *lstr, const char *rstr)
{
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retnFalse
		test	edx, edx
		jz		retnFalse
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jnz		retnFalse
		mov		edx, esi
	iterHead:
		mov		al, [ecx]
		test	al, al
		jz		retnTrue
		cmp		[edx], al
		jnz		retnFalse
		inc		ecx
		inc		edx
		jmp		iterHead
	retnTrue:
		mov		al, 1
		pop		edi
		pop		esi
		retn
	retnFalse:
		xor		al, al
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) bool __fastcall StrEqualCI(const char *lstr, const char *rstr)
{
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retnFalse
		test	edx, edx
		jz		retnFalse
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jnz		retnFalse
		mov		edx, esi
	iterHead:
		cmp		[ecx], 0
		jz		retnTrue
		call	CmprLetters
		test	al, al
		jz		retnFalse
		inc		ecx
		inc		edx
		jmp		iterHead
	retnTrue:
		mov		al, 1
		pop		edi
		pop		esi
		retn
	retnFalse:
		xor		al, al
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) char __fastcall StrCompare(const char *lstr, const char *rstr)
{
	__asm
	{
		push	ebx
		test	ecx, ecx
		jnz		proceed
		test	edx, edx
		jz		retnEQ
		jmp		retnLT
	proceed:
		test	edx, edx
		jz		retnGT
	iterHead:
		mov		al, [ecx]
		mov		bl, [edx]
		test	al, al
		jz		iterEnd
		cmp		al, bl
		jz		iterNext
		cmp		al, 'Z'
		jg		lNotCap
		cmp		al, 'A'
		jl		lNotCap
		or		al, 0x20
	lNotCap:
		cmp		bl, 'Z'
		jg		rNotCap
		cmp		bl, 'A'
		jl		rNotCap
		or		bl, 0x20
	rNotCap:
		cmp		al, bl
		jl		retnLT
		jg		retnGT
	iterNext:
		inc		ecx
		inc		edx
		jmp		iterHead
	iterEnd:
		test	bl, bl
		jz		retnEQ
	retnLT:
		mov		al, -1
		pop		ebx
		retn
	retnGT:
		mov		al, 1
		pop		ebx
		retn
	retnEQ:
		xor		al, al
		pop		ebx
		retn
	}
}

__declspec(naked) char __fastcall StrBeginsCS(const char *lstr, const char *rstr)
{
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retn0
		test	edx, edx
		jz		retn0
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jg		retn0
		mov		edx, esi
	iterHead:
		mov		al, [ecx]
		test	al, al
		jz		iterEnd
		cmp		[edx], al
		jnz		retn0
		inc		ecx
		inc		edx
		jmp		iterHead
	iterEnd:
		cmp		[edx], 0
		setz	al
		inc		al
		pop		edi
		pop		esi
		retn
	retn0:
		xor		al, al
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) char __fastcall StrBeginsCI(const char *lstr, const char *rstr)
{
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retn0
		test	edx, edx
		jz		retn0
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jg		retn0
		mov		edx, esi
	iterHead:
		cmp		[ecx], 0
		jz		iterEnd
		call	CmprLetters
		test	al, al
		jz		retn0
		inc		ecx
		inc		edx
		jmp		iterHead
	iterEnd:
		cmp		[edx], 0
		setz	al
		inc		al
		pop		edi
		pop		esi
		retn
	retn0:
		xor		al, al
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) void __fastcall FixPath(char *str)
{
	__asm
	{
		test	ecx, ecx
		jz		done
	iterHead:
		mov		al, [ecx]
		test	al, al
		jz		done
		cmp		al, 'Z'
		jg		checkSlash
		cmp		al, 'A'
		jl		iterNext
		or		byte ptr [ecx], 0x20
		jmp		iterNext
	checkSlash:
		cmp		al, '\\'
		jnz		iterNext
		mov		byte ptr [ecx], '/'
	iterNext:
		inc		ecx
		jmp		iterHead
	done:
		retn
	}
}

__declspec(naked) void __fastcall StrToLower(char *str)
{
	__asm
	{
		test	ecx, ecx
		jz		done
	iterHead:
		mov		al, [ecx]
		cmp		al, 'Z'
		jg		iterNext
		test	al, al
		jz		done
		cmp		al, 'A'
		jl		iterNext
		or		byte ptr [ecx], 0x20
	iterNext:
		inc		ecx
		jmp		iterHead
	done:
		retn
	}
}

__declspec(naked) void __fastcall ReplaceChr(char *str, char from, char to)
{
	__asm
	{
		test	ecx, ecx
		jz		done
		mov		al, [esp+4]
	iterHead:
		cmp		[ecx], 0
		jz		done
		cmp		[ecx], dl
		jnz		iterNext
		mov		[ecx], al
	iterNext:
		inc		ecx
		jmp		iterHead
	done:
		retn	4
	}
}

__declspec(naked) char* __fastcall FindChr(const char *str, char chr)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
	iterHead:
		cmp		[eax], 0
		jz		retnNULL
		cmp		[eax], dl
		jz		done
		inc		eax
		jmp		iterHead
	retnNULL:
		xor		eax, eax
	done:
		retn
	}
}

__declspec(naked) char* __fastcall FindChrR(const char *str, char chr)
{
	__asm
	{
		call	StrEnd
		test	eax, eax
		jz		done
	iterHead:
		cmp		eax, ecx
		jz		retnNULL
		dec		eax
		cmp		[eax], dl
		jz		done
		jmp		iterHead
	retnNULL:
		xor		eax, eax
	done:
		retn
	}
}

__declspec(naked) char* __fastcall SubStr(const char *srcStr, const char *subStr)
{
	__asm
	{
		push	ebx
		push	esi
		push	edi
		mov		esi, ecx
		mov		ecx, edx
		call	StrLen
		test	eax, eax
		jz		retnNULL
		mov		edi, edx
		mov		ebx, eax
		mov		ecx, esi
		call	StrLen
		sub		eax, ebx
		mov		ebx, eax
	mainHead:
		cmp		ebx, 0
		jl		retnNULL
	subHead:
		cmp		[edx], 0
		jnz		proceed
		mov		eax, esi
		jmp		done
	proceed:
		call	CmprLetters
		test	al, al
		jz		mainNext
		inc		ecx
		inc		edx
		jmp		subHead
	mainNext:
		dec		ebx
		inc		esi
		mov		ecx, esi
		mov		edx, edi
		jmp		mainHead
	retnNULL:
		xor		eax, eax
	done:
		pop		edi
		pop		esi
		pop		ebx
		retn
	}
}

__declspec(naked) char* __fastcall SlashPos(const char *str)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
	iterHead:
		mov		cl, [eax]
		test	cl, cl
		jz		retnNULL
		cmp		cl, '/'
		jz		done
		cmp		cl, '\\'
		jz		done
		inc		eax
		jmp		iterHead
	retnNULL:
		xor		eax, eax
	done:
		retn
	}
}

__declspec(naked) char* __fastcall SlashPosR(const char *str)
{
	__asm
	{
		call	StrEnd
		test	eax, eax
		jz		done
	iterHead:
		cmp		eax, ecx
		jz		retnNULL
		dec		eax
		cmp		[eax], '/'
		jz		done
		cmp		[eax], '\\'
		jz		done
		jmp		iterHead
	retnNULL:
		xor		eax, eax
	done:
		retn
	}
}

__declspec(naked) char* __fastcall GetNextToken(char *str, char delim)
{
	__asm
	{
		push	ebx
		mov		eax, ecx
		xor		bl, bl
	iterHead:
		mov		cl, [eax]
		test	cl, cl
		jz		done
		cmp		cl, dl
		jz		chrEQ
		test	bl, bl
		jnz		done
		jmp		iterNext
	chrEQ:
		test	bl, bl
		jnz		iterNext
		mov		bl, 1
		mov		[eax], 0
	iterNext:
		inc		eax
		jmp		iterHead
	done:
		pop		ebx
		retn
	}
}

__declspec(naked) char* __fastcall GetNextToken(char *str, const char *delims)
{
	__asm
	{
		push	ebx
		push	esi
		mov		eax, ecx
		mov		esi, edx
		xor		bl, bl
	mainHead:
		mov		cl, [eax]
		test	cl, cl
		jz		done
	subHead:
		cmp		[edx], 0
		jz		wasFound
		cmp		cl, [edx]
		jz		chrEQ
		inc		edx
		jmp		subHead
	chrEQ:
		test	bl, bl
		jnz		mainNext
		mov		bl, 1
		mov		[eax], 0
	mainNext:
		inc		eax
		mov		edx, esi
		jmp		mainHead
	wasFound:
		test	bl, bl
		jz		mainNext
	done:
		pop		esi
		pop		ebx
		retn
	}
}

char* __fastcall CopyString(const char *key)
{
	char *newKey = (char*)malloc(StrLen(key) + 1);
	StrCopy(newKey, key);
	return newKey;
}

char* __fastcall IntToStr(int num, char *str)
{
	if (num < 0)
	{
		num = -num;
		*str++ = '-';
	}
	int temp = num, digits = 1;
	while (temp /= 10) digits++;
	temp = digits;
	str += digits;
	*str = 0;
	do
	{
		*--str = '0' + (num % 10);
		num /= 10;
	}
	while (--digits);
	return str + temp;
}

char* __fastcall FltToStr(float num, char *str)
{
	if (num != 0)
	{
		if (num < 0)
		{
			*str++ = '-';
			num = fabs(num);
		}
		int intNum = (int)num;
		if (intNum)
		{
			str = IntToStr(intNum, str);
			if (intNum == num)
				return str;
		}
		else *str++ = '0';
		*str++ = '.';
		intNum = (int)((num - intNum) * 100000);
		int divis = intNum % 10;
		if (divis == 9) intNum++;
		else if (divis == 1) intNum--;
		divis = 10000;
		do
		{
			*str++ = '0' + (intNum / divis);
			intNum %= divis;
			divis /= 10;
		}
		while (intNum);
	}
	else *str++ = '0';
	*str = 0;
	return str;
}

int __fastcall StrToInt(const char *str)
{
	if (!str || !*str) return 0;
	int result = 0;
	bool neg = (*str == '-');
	if (neg) str++;
	char chr;
	while (chr = *str)
	{
		if ((chr < '0') || (chr > '9')) break;
		result *= 10;
		result += chr - '0';
		str++;
	}
	return neg ? -result : result;
}

char* __fastcall UIntToHex(UInt32 num, char *str)
{
	char res[8];
	UInt8 size = 0, temp;
	do
	{
		temp = num % 0x10;
		res[size++] = temp + ((temp < 10) ? '0' : '7');
	}
	while (num >>= 4);
	do
	{
		*str++ = res[--size];
	}
	while (size);
	*str = 0;
	return str;
}

UInt32 __fastcall HexToUInt(const char *str)
{
	if (!str || !*str) return 0;
	char size = 0, chr;
	UInt32 result = 0, mul = 1;
	do
	{
		str++;
		size++;
	}
	while (*str && (size < 8));
	do
	{
		chr = *--str;
		if (chr < '0') continue;
		else if (chr <= '9') chr -= '0';
		else if (chr < 'A') continue;
		else if (chr <= 'F') chr -= '7';
		else if (chr < 'a') continue;
		else if (chr <= 'f') chr -= 'W';
		else continue;
		result += chr * mul;
		mul <<= 4;
	}
	while (--size);
	return result;
}

bool __fastcall FileExists(const char *path)
{
	DWORD attr = GetFileAttributes(path);
	return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool FileToBufferRaw(const char *filePath, char *buffer)
{
	IFileStream srcFile;
	if (!srcFile.Open(filePath)) return false;
	UInt32 length = srcFile.GetLength();
	if (!length || (length >= kMaxMessageLength)) return false;
	srcFile.ReadBuf(buffer, length);
	buffer[length] = 0;
	return true;
}

UInt32 FileToBuffer(const char *filePath, char *buffer)
{
	IFileStream sourceFile;
	if (!sourceFile.Open(filePath)) return 0;
	UInt32 length = 0, sections = 1;
	UInt8 data;
	bool split = false;
	while (!sourceFile.HitEOF())
	{
		data = sourceFile.Read8();
		if (!data) break;
		if ((data == '\n') || (data == '\r'))
		{
			split = true;
			continue;
		}
		if (split)
		{
			split = false;
			if (length)
			{
				*buffer++ = 0;
				sections++;
			}
		}
		*buffer++ = data;
		length++;
	}
	*buffer = 0;
	return length ? sections : 0;
}

extern char *s_strArgBuffer;

void ClearFolder(char *pathEndPtr)
{
	DirectoryIterator dirIter(s_strArgBuffer);
	while (!dirIter.End())
	{
		if (dirIter.IsFolder())
			ClearFolder(StrCopy(StrCopy(pathEndPtr - 1, dirIter.Get()), "\\*"));
		else
		{
			StrCopy(pathEndPtr - 1, dirIter.Get());
			remove(s_strArgBuffer);
		}
		dirIter.Next();
	}
	dirIter.Close();
	*(pathEndPtr - 1) = 0;
	RemoveDirectory(s_strArgBuffer);
}

void __fastcall GetTimeStamp(char *buffer)
{
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%Y%m%d%H%M%S", &timeinfo);
}

UInt32 __fastcall ByteSwap(UInt32 dword)
{
	UInt8 *ptr = (UInt8*)&dword, byte = *ptr;
	*ptr = ptr[3];
	ptr[3] = byte;
	byte = ptr[1];
	ptr[1] = ptr[2];
	ptr[2] = byte;
	return *(UInt32*)ptr;
}

void DumpMemImg(void *data, UInt32 size, UInt8 extra)
{
	UInt32 *ptr = (UInt32*)data;
	Console_Print("Output");
	_MESSAGE("\nDumping  %08X\n", ptr);
	for (UInt32 iter = 0; iter < size; iter += 4, ptr++)
	{
		if (!extra) _MESSAGE("%03X\t\t%08X\t", iter, *ptr);
		else if (extra == 1) _MESSAGE("%03X\t\t%08X\t[%08X]\t", iter, *ptr, ByteSwap(*ptr));
		else _MESSAGE("%03X\t\t%08X\t%f", iter, *ptr, *(float*)ptr);
	}
}

void GetMD5File(const char *filePath, char *outHash)
{
	IFileStream sourceFile;
	if (!sourceFile.Open(filePath)) return;

	MD5 md5;

	HANDLE handle = sourceFile.GetHandle();

	SInt64 offset = 0;
	UInt8 buffer[0x400], digest[0x10];
	UInt32 length;

	while (!sourceFile.HitEOF())
	{
		ReadFile(handle, buffer, 0x400, &length, NULL);
		offset += length;
		sourceFile.SetOffset(offset);
		md5.MD5Update(buffer, length);
	}
	md5.MD5Final(digest);

	for (UInt8 idx = 0; idx < 0x10; idx++, outHash += 2)
		sprintf_s(outHash, 3, "%02X", digest[idx]);
}