#include "stdafx.h"
#include "GFXLoad.h"
#include "Import.h"
#include "TMemory.h"
#include "Other.h"

GFXLoad gGFXLoad;

Naked(SetFileSize)
{
	_asm
	{
		// ----
		MOV gGFXLoad.movEax, EAX
		MOV gGFXLoad.movEcx, ECX
		MOV gGFXLoad.movEdx, EDX
		MOV gGFXLoad.movEbx, EBX
		MOV gGFXLoad.movEsp, ESP
		MOV gGFXLoad.movEbp, EBP
		MOV gGFXLoad.movEsi, ESI
		MOV gGFXLoad.movEdi, EDI
		// ----
	}
	printf("SetFileSize:%02X\n",gGFXLoad.movEax);

	if (gGFXLoad.movEax == 0x16F4E)
		gGFXLoad.movEax = 0x16654;

	_asm
	{
		// ----
		MOV EAX, gGFXLoad.movEax
		MOV ECX, gGFXLoad.movEcx
		MOV EDX, gGFXLoad.movEdx
		MOV EBX, gGFXLoad.movEbx
		MOV ESP, gGFXLoad.movEsp
		MOV EBP, gGFXLoad.movEbp
		MOV ESI, gGFXLoad.movEsi
		MOV EDI, gGFXLoad.movEdi
		// ----

		MOV DWORD PTR SS : [EBP - 0x24], EAX
		PUSH DWORD PTR SS : [EBP - 0x24]
		JMP gGFXLoad.jmpSetFileSize
	}
}

void GFXLoad::Load()
{
	this->jmpSetFileSize = 0x009C46D3;
	// ----
	//009C470A   E8 7B3FF6FF      CALL main.0092868A - DDS file info
	//009C470A  |. E8 7B3FF6FF    CALL main.0092868A
	gTMemory.SetOp((LPVOID)0x009C470A, this->LoadFile, ASM::CALL);
	//gTMemory.SetOp((LPVOID)0x009C46E4, this->DecodeGFXDDS, ASM::CALL);
	//009C46CD   8945 DC          MOV DWORD PTR SS : [EBP - 0x24], EAX
	//009C46D0   FF75 DC          PUSH DWORD PTR SS : [EBP - 0x24]
	//009C46D3   E8 4F49F6FF      CALL main.00929027
	//gTMemory.SetOp((LPVOID)0x009C46CD, (LPVOID)SetFileSize, ASM::JMP);
	//009C466D   50               PUSH EAX
	//009C466E   E8 B449F6FF      CALL main.00929027
	//009C4673   8945 F0          MOV DWORD PTR SS:[EBP-0x10],EAX
	
	//009C4695   8945 E0          MOV DWORD PTR SS : [EBP - 0x20], EAX
	//009C4698   8D4D E4          LEA ECX, DWORD PTR SS : [EBP - 0x1C]
	//009C469B   E8 7B0F0000      CALL main.009C561B
}

void GFXLoad::LoadFile(LPBYTE FileBytes, int FileSize)
{
	//printf("LF:%02X %02X %02X\n",FileBytes,FileSize);
	// ----
	_asm
	{
		mov gGFXLoad.movEbp, EBP
	}
	// ----
	LPBYTE btAddr = *(LPBYTE*)(gGFXLoad.movEbp + 0xB8);
	int iLen = gOther.SearchEnd(btAddr);
	char szPath[64];
	memcpy(szPath, (char*)btAddr, iLen + 1);
	
	printf("LoadDDS: %02X %s %02X %02X\n",btAddr, szPath, FileSize, FileBytes);

	if (strstr(szPath, "effect_egg") != NULL)
	{
		LPBYTE pArr = (LPBYTE)FileBytes;

		FILE *fw;
		fopen_s(&fw, "effect_egg.dds", "wb");
		printf("Err:%d\n", GetLastError());

		if (fw != NULL)
		{
			fwrite(pArr, FileSize, 1, fw);
			fclose(fw);
		}
	}

	if (strstr(szPath, "event_egg") != NULL)
	{
		LPBYTE pArr = (LPBYTE)FileBytes;

	/*	FILE *fw;
		fopen_s(&fw, "event_egg.dds", "wb");
		printf("Err:%d\n", GetLastError());

		if (fw != NULL)
		{
			fwrite(pArr, FileSize, 1, fw);
			fclose(fw);
		}*/

		FILE *fr;
		fopen_s(&fr, "event_egg.dds", "rb");

		if (fr != NULL)
		{
			BYTE *btFile = new BYTE[FileSize];
			fread(btFile, FileSize, 1, fr);

			printf("BTFILE[%02X][%02X][%02X]\n", btFile[0], btFile[1], btFile[2]);

			memcpy(FileBytes, btFile, FileSize);

			printf("pArr[%02X][%02X][%02X] %02X\n", pArr[0], pArr[1], pArr[2], FileSize);
			fclose(fr);
		}
	}

	if (strstr(szPath, "Alarm.ozg") != NULL)
	{
		MessageBox(0, "", "", 0);
		printf("LoadDDS: %02X %s %02X %02X\n", btAddr, szPath, FileSize, FileBytes);

		LPBYTE pArr = (LPBYTE)FileBytes;

	/*	FILE *fw;
		fopen_s(&fw, "Alarm.swf", "wb");
		printf("Err:%d\n", GetLastError());

		if (fw != NULL)
		{
			fwrite(pArr, FileSize, 1, fw);
			fclose(fw);
		}*/
		printf("pArr[%02X][%02X][%02X]\n", pArr[0], pArr[1], pArr[2]);
		
		FILE *fr;
		fopen_s(&fr, "Alarm.swf", "rb");

		if (fr != NULL)
		{
			BYTE *btFile = new BYTE[FileSize];
			fread(btFile, FileSize, 1, fr);

			printf("BTFILE[%02X][%02X][%02X]\n", btFile[0], btFile[1], btFile[2]);

			memcpy(FileBytes, btFile, FileSize);

			printf("pArr[%02X][%02X][%02X] %02X\n", pArr[0], pArr[1], pArr[2], FileSize);
			fclose(fr);
		}
	}
		
	pLoadGFXDDS(FileBytes, FileSize);
}