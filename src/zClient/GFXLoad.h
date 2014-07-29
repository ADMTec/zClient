#pragma once
#include <windows.h>

class GFXLoad
{
public:
	// ----
	void	Load();
	static void LoadFile(LPBYTE FileBytes, int FileSize);
	static void DecodeGFXDDS(LPVOID lpDest, LPVOID lpSource, int iSize);
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
	DWORD jmpSetFileSize;
}; extern GFXLoad gGFXLoad;