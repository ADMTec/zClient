#include "stdafx.h"
#include "GFXLoad.h"
#include "Import.h"
#include "TMemory.h"
#include "Other.h"

GFXLoad gGFXLoad;

Naked(GFXLoaderASM)
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
		MOV ECX, DWORD PTR SS : [EBP + 0x0C] //-FILE INFO
		MOV gGFXLoad.dwFilePtr, ECX
		MOV ECX, DWORD PTR SS : [EBP + 0x10] //-FILE SIZE		
		MOV gGFXLoad.dwFileSize, ECX
		MOV ECX, DWORD PTR SS : [EBP + 0x08] //-FILE NAME
		MOV gGFXLoad.dwFileName, ECX
	}
	// ----
	gGFXLoad.GetName(gGFXLoad.dwFileName,gGFXLoad.szPath); //Get File Name
	// ----
	if (strstr(gGFXLoad.szPath, "Alarm.ozg") != NULL)
	{
		gGFXLoad.LoadGFXFile("Data\\Custom\\GFX\\Alarm.swf", gGFXLoad.dwFileSize, gGFXLoad.dwFilePtr); //Load our edited file
	}
	if (strstr(gGFXLoad.szPath, "characterFrame.ozg") != NULL)
	{
		gGFXLoad.LoadGFXFile("Data\\Custom\\GFX\\characterFrame.swf", gGFXLoad.dwFileSize, gGFXLoad.dwFilePtr); //Load our edited file
	}
	if (strstr(gGFXLoad.szPath, "inventoryFrame.ozg") != NULL)
	{
		gGFXLoad.LoadGFXFile("Data\\Custom\\GFX\\inventoryFrame.swf", gGFXLoad.dwFileSize, gGFXLoad.dwFilePtr); //Load our edited file
		/*FILE *fw;
		fopen_s(&fw, "inventoryFrame.swf", "wb");

		if (fw != NULL)
		{
			LPBYTE pFile = (LPBYTE)gGFXLoad.dwFilePtr;
			// ----
			pFile[0] = 0x46;
			pFile[1] = 0x57;
			pFile[2] = 0x53;
			// ----
			fwrite(pFile, gGFXLoad.dwFileSize, 1, fw);
			fclose(fw);
			// ----
			pFile[0] = 0x47;
			pFile[1] = 0x46;
			pFile[2] = 0x58;
			// ----
		}*/
	}
	if (strstr(gGFXLoad.szPath, "MainFrame.ozg") != NULL)
	{
		FILE *fw;
		fopen_s(&fw, "MainFrame.swf", "wb");

		if (fw != NULL)
		{
			LPBYTE pFile = (LPBYTE)gGFXLoad.dwFilePtr;
			// ----
			pFile[0] = 0x46;
			pFile[1] = 0x57;
			pFile[2] = 0x53;
			// ----
			fwrite(pFile, gGFXLoad.dwFileSize, 1, fw);
			fclose(fw);
			// ----
			pFile[0] = 0x47;
			pFile[1] = 0x46;
			pFile[2] = 0x58;
			// ----
		}
	}
	// ----
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
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		MOV ECX, DWORD PTR SS : [EBP + 0x0C]
		MOV DWORD PTR DS : [EAX + 0x0C], ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		MOV ECX, DWORD PTR SS : [EBP + 0x10]

		JMP gGFXLoad.jmpGFXLoader
	}
}

void GFXLoad::Load()
{
	this->jmpGFXLoader = 0x009C5300;
	// ----
	gTMemory.SetRange((LPVOID)0x009C52F1, 6, ASM::NOP);
	gTMemory.SetOp((LPVOID)0x009C52F1, GFXLoaderASM, ASM::JMP);
	// ----
}

int GFXLoad::GetName(DWORD dwFileName,char* szOut)
{
	int iLen = gOther.SearchEnd((LPBYTE)dwFileName);
	memcpy(szOut, (char*)dwFileName, iLen + 1);
	// ----
	return iLen;
}

void GFXLoad::LoadGFXFile(char *filename, DWORD dwFileSize, DWORD dwFile)
{
	FILE *fpOpen2;
	fopen_s(&fpOpen2, filename, "rb");

	if (fpOpen2 != NULL)
	{
		fseek(fpOpen2, 0, SEEK_END);
		int lSize = ftell(fpOpen2);
		rewind(fpOpen2);

		char *buffer = (char*)malloc(sizeof(char)*lSize);
		fread(buffer, 1, lSize, fpOpen2);
		fclose(fpOpen2);

		buffer[0] = 0x47;
		buffer[1] = 0x46;
		buffer[2] = 0x58;

		memcpy(&*(BYTE*)dwFilePtr, buffer, lSize);
	}
}