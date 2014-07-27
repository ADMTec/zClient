#include "stdafx.h"
#include "Other.h"
#include "Import.h"
#include "TMemory.h"
#include <direct.h>

Other gOther;

void Other::Load()
{
	this->CrackMain();
	this->ProtocolMain();
	this->ConnectMain();
	// ----
	SetOp((LPVOID)0x005EA5E1, this->MapObjReader, ASM::CALL);
	// ----
	SetOp((LPVOID)0x005CB1EC, this->MapMapReader, ASM::CALL);
	// ----
	SetOp((LPVOID)0x00550F0F, this->ModelDecode, ASM::CALL);
}
// ----
int Other::SearchEnd(BYTE *pArr)
{
	int iLen = 0;
	for (int i = 0; i < 100; i++)
	{
		if (pArr[i] == 0x00)
			return iLen;

		iLen++;
	}

	return -1;
}
// ----
char* Other::ParsePathToName(char *szPath, int iLen)
{
	int iPos = 0;
	for (int i = iLen; i > 0; i--)
	{
		if (szPath[i] == '\\' || szPath[i] == 0x5C)
		{
			iPos = i;
			break;
		}
	}

	char szOut[64];
	memcpy(szOut, &szPath[iPos+1], iLen - iPos+1);

	return szOut;
}
// ----
void Other::ModelDecode(LPVOID lpDest, LPVOID lpSource, int iSize)
{
	// ----
	_asm
	{
		mov gOther.movEbp, EBP
	}
	// ----

	LPBYTE pPath = (LPBYTE)(gOther.movEbp+0xE8);
	int iLen = gOther.SearchEnd(pPath);
	char szPath[64];
	memcpy(szPath, (char*)pPath, iLen+1);

	if (strstr(szPath, "Object94\\") != NULL)
	{
		char szName[64];
		strcpy_s(szName, 64, gOther.ParsePathToName(szPath, iLen + 1));
		printf("Name:%s\n", szName);

		_mkdir("Object94");
		char szOutputName[64];
		sprintf_s(szOutputName, "Object94\\%s", szName);

		LPBYTE pArr = (LPBYTE)lpDest;
		printf("Decode:%02X %02X %02X %02X %02X %s %d\n", pArr[0], pArr[1], pArr[2], pArr[3], pArr[4], szPath, gOther.SearchEnd(pPath));

		pModelDecode(lpDest, lpSource, iSize);

		printf("Decode:%02X %02X %02X %02X %02X\n", pArr[0], pArr[1], pArr[2], pArr[3], pArr[4]);

		FILE *fw;
		fopen_s(&fw, szOutputName, "wb");
		printf("Err:%d\n",GetLastError());

		BYTE btHeader[4] = {0x42,0x4D,0x44,0x04};

		if (fw != NULL)
		{
			fwrite(btHeader, 4, 1, fw);
			fwrite(pArr, iSize, 1, fw);
			fclose(fw);
		}
	}
	else
	{
		pModelDecode(lpDest, lpSource, iSize);
	}
}
// ----
int Other::MapMapReader(int flag, int MapBytes, int MapSize)
{
	LPBYTE pArr = (LPBYTE)MapBytes;

	BYTE szFileString[32];
	memcpy(szFileString, (BYTE*)pArr, 32);
	
	printf("MapMapReader:%02X %02X %02X %02X %02X\n", szFileString[0], szFileString[1], szFileString[2], szFileString[3], szFileString[4]);

	return pFileReader(flag, MapBytes, MapSize);
}
// ----
int Other::MapObjReader(int flag, int MapBytes, int MapSize)
{
	LPBYTE pArr = (LPBYTE)MapBytes;

	BYTE szFileString[32];
	memcpy(szFileString, (BYTE*)pArr, 32);

	printf("MapObjReader:%02X %02X %02X %02X %02X\n", szFileString[0], szFileString[1], szFileString[2], szFileString[3], szFileString[4]);

	return pFileReader(flag, MapBytes, MapSize);
}
// ----
void Other::ConnectMain()
{
	// ----
	SetRange((LPVOID)pAddress, 0x1B, 0);
	memcpy((LPVOID)pAddress, "87.98.134.80", sizeof("87.98.134.80"));
	// ----
	SetByte((LPVOID)(pVersion), '2');  //Change MainVersion
	SetByte((LPVOID)(pVersion + 1), '2');
	SetByte((LPVOID)(pVersion + 2), '7');
	SetByte((LPVOID)(pVersion + 3), '4');
	SetByte((LPVOID)(pVersion + 4), ':');
	// ----
}
// ----
void Other::ProtocolMain()
{
	// ----
	SetByte((LPVOID)0x0043937E, 0xEB); //Disable Protocol Xor
	SetByte((LPVOID)0x0043937F, 0x06);
	SetByte((LPVOID)0x00439380, 0x90);
	// ----
	SetByte((LPVOID)0x004393B2, 0xEB); //Disable Protocol Shift
	SetByte((LPVOID)0x004393B3, 0x04);
	// ----
	SetRange((LPVOID)0x0AB81136, 4, ASM::NOP); //Disable Protocol Restore
	SetRange((LPVOID)0x0A5E3ED1, 2, ASM::NOP);
	SetRange((LPVOID)0x09D6BBE5, 4, ASM::NOP);
	// ----
	SetByte((LPVOID)0x0AB825CD, 0x01); //C1 XX F3
	SetByte((LPVOID)0x0ADD80E4, 0x01); //C1 XX F3
	SetByte((LPVOID)0x00663CC5, 0x01); //C1 XX F3
	SetByte((LPVOID)0x0AC85877, 0x01); //C1 XX F3
	// ----
	SetByte((LPVOID)0x00639787, 0x01); //C1 XX 1C
	// ----
	SetByte((LPVOID)0x005B2485, 0x01); //C1 XX 24
	// ----
	SetByte((LPVOID)0x0A7099C8, 0x01); //C1 XX 16
	SetByte((LPVOID)0x0AB9E39D, 0x01); //C1 XX 16
	// ----
	SetByte((LPVOID)0x09EDCB69, 0x01); //C1 XX 30
	// ----
	SetByte((LPVOID)0x0A39529A, 0x01); //C1 XX 19
	// ----
}
// ----
void Other::CrackMain()
{
	// ----
	SetByte((LPVOID)0x0050E887, 0xEB); //CMStarterCore
	SetByte((LPVOID)0x0043E510, 0x50); //Login Enable
	SetByte((LPVOID)0x0043E519, 0x50); //Login Enable
	SetByte((LPVOID)0x0043E521, 0x18); //Login Enable
	SetByte((LPVOID)0x0043DFD9, 0x00); //Login Enable          
	// ----
	SetByte((LPVOID)0x004D9176, 0xEB); //Mu.exe
	// ----
	SetByte((LPVOID)0x004D9556, 0xE9); //GG
	SetByte((LPVOID)0x004D9557, 0x8B);
	SetByte((LPVOID)0x004D9558, 0x00);
	SetByte((LPVOID)0x004D9559, 0x00);
	SetByte((LPVOID)0x004D955A, 0x00);
	SetByte((LPVOID)0x004D955B, 0x90);
	// ----
	SetByte((LPVOID)0x004D9513, 0xEB); //Config.ini
	// ----
	SetByte((LPVOID)0x004DC3CA, 0xEB); //RG
	SetByte((LPVOID)0x0062D2DA, 0xEB); //RG
	SetByte((LPVOID)0x0062D3F6, 0xEB); //RG
	SetByte((LPVOID)0x0A78D5C1, 0xE9); //RG
	SetByte((LPVOID)0x0A78D5C2, 0x1C); //
	SetByte((LPVOID)0x0A78D5C3, 0x9C); //
	SetByte((LPVOID)0x0A78D5C4, 0xEA); //
	SetByte((LPVOID)0x0A78D5C5, 0xF5); //
	SetByte((LPVOID)0x0A78D5C6, 0x90); //
	// ----
	SetByte((LPVOID)0x009F1586, 0xC3); //MuError.log
	// ----
	SetRange((LPVOID)0x0A78A040, 7, ASM::NOP); //Disable Character Dissapear
	// ----
}