#pragma once
#include <windows.h>

class Protocol
{
public:
	// ----
	void	Load();
	static  void DataRecv(DWORD Case, LPBYTE DATA, int Len, int aIndex);
	// ----
}; extern Protocol gProtocol;