#pragma once
#include <windows.h>

class GFXLoad
{
public:
	// ----
	void	Load();
	static void LoadFile(LPBYTE FileBytes, int FileSize);
	static void DecodeGFXDDS(LPVOID lpDest, LPVOID lpSource, int iSize);
	void	LoadGFXFile(char *filename, DWORD dwFileSize, DWORD dwFile);
	int   GetName(DWORD dwFileName, char* szOut);
	// ----
public:
	DWORD movEax;
	DWORD movEcx;
	DWORD movEdx;
	DWORD movEbx;
	DWORD movEsp;
	DWORD movEbp;
	DWORD movEsi;
	DWORD movEdi;
	// ----
	DWORD jmpGFXLoader;
	DWORD dwFilePtr;
	DWORD dwFileSize;
	DWORD dwFileName;
	char  szPath[64];
}; extern GFXLoad gGFXLoad;