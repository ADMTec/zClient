#include "stdafx.h"
#include "TMemory.h"
#include <io.h>
#include <fcntl.h>
#include <tlhelp32.h>
#include <process.h> 
//---------------------------------------------------------------------------
TMemory gTMemory;

void TMemory::InitConsole()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;
}
//---------------------------------------------------------------------------

DWORD TMemory::WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode = 0;
	DWORD dwOldProtect = 0;
	// ----
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	// ----
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	memcpy(lpAddress, lpBuf, uSize);
	// ----
	DWORD dwBytes = 0;
	// ----
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);
	// ----
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	return 0x00;
}
//---------------------------------------------------------------------------

DWORD TMemory::ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode = 0;
	DWORD dwOldProtect = 0;
	// ----
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	// ----
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	memcpy(lpBuf, lpAddress, uSize);
	// ----
	DWORD dwBytes = 0;
	// ----
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);
	// ----
	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	return 0x00;
}
//---------------------------------------------------------------------------

DWORD TMemory::SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return this->WriteMemory(dwOffset, (LPVOID)& btValue, sizeof(BYTE));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetByte(const LPVOID dwOffset, BYTE & btValue)
{
	return this->ReadMemory(dwOffset, (LPVOID)btValue, sizeof(BYTE));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetWord(const LPVOID dwOffset, const WORD wValue)
{
	return this->WriteMemory(dwOffset, (LPVOID)& wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetWord(const LPVOID dwOffset, WORD & wValue)
{
	return this->ReadMemory(dwOffset, (LPVOID)wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetDword(const LPVOID dwOffset, const DWORD dwValue)
{
	return this->WriteMemory(dwOffset, (LPVOID)& dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetDword(const LPVOID dwOffset, DWORD & dwValue)
{
	return this->ReadMemory(dwOffset, (LPVOID)dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetFloat(const LPVOID dwOffset, float fValue)
{
	return this->WriteMemory(dwOffset, &fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetFloat(const LPVOID dwOffset, float & fValue)
{
	return ReadMemory(dwOffset, &fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetDouble(const LPVOID dwOffset, double dValue)
{
	return this->WriteMemory(dwOffset, &dValue, sizeof(double));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0] = 0xE9;
	memcpy((LPVOID)& btBuf[1], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return this->WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0] = 0x0F;
	btBuf[1] = 0x8F;
	memcpy((LPVOID)& btBuf[2], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return this->WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0] = 0x0F;
	btBuf[1] = 0x87;
	memcpy((LPVOID)& btBuf[2], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return this->WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0] = cmd;
	memcpy((LPVOID)& btBuf[1], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return this->WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf = new BYTE[wCount];
	// ----
	memset(lpBuf, btValue, wCount);
	// ----
	return this->WriteMemory(dwAddress, (LPVOID)lpBuf, wCount);
}
//---------------------------------------------------------------------------

DWORD TMemory::SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	DWORD dwShift = (ULONG_PTR)dwMyFuncOffset - ((ULONG_PTR)dwJmpOffset + 5);
	// ----
	btBuf[0] = cmd;
	// ----
	memcpy((LPVOID)& btBuf[1], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return this->WriteMemory(dwJmpOffset, (LPVOID)btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

void TMemory::HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset - (dwJmpOffset + 5);
}
//---------------------------------------------------------------------------