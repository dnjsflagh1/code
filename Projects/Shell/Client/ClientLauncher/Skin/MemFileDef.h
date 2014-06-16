#ifndef _JCH_MEM_FILE_INTERFACE_H
#define _JCH_MEM_FILE_INTERFACE_H
#include <Windows.h>

enum baseopentype
{
	base_tool,
	base_client,
	base_server,
};

typedef BYTE* (*MemFileOpen)(const char* szFileName,int& nSize);
typedef void (*MemFileClose)(BYTE* pMemFile);

struct Memfile
{
	MemFileOpen		popenfunc;
	MemFileClose	pclosefunc;
};

#endif