#pragma once
#include <windows.h>

class Other
{
public:
	// ----
	void	Load();
	void	CrackMain();
	void	ProtocolMain();
	void	ConnectMain();
	static  int MapObjReader(int flag, int MapBytes, int MapSize);
	static	int MapMapReader(int flag, int MapBytes, int MapSize);
	static	void ModelDecode(LPVOID lpDest,LPVOID lpSource,int iSize);
	char*	ParsePathToName(char *szPath, int iLen);
	int		SearchEnd(BYTE *pArr);
	// ----
	DWORD	movEbp;
}; extern Other gOther;