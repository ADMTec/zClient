#include "stdafx.h"
#include "TMemory.h"
#include "Import.h"
#include "Resolution.h"
#include "Other.h"
#include "Graphics.h"
#include "Glow.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			gTMemory.InitConsole();
			// ----
			gResolution.Load();
			gGraphics.Load();
			gOther.Load();
			// ----
			gGlow.isEnabled = GetPrivateProfileInt("GLOW", "Enabled", 0, "./Option.ini"); // I just put it here
			// ----
			//009C470A   E8 7B3FF6FF      CALL main.0092868A - DDS file info
			MessageBox(0, "Loaded", "Caption", 0); //Test purposes, so I know if dll is loaded!
		}
		break;
		// ----
		case DLL_PROCESS_DETACH:
		{
			// --
		}
		break;
	}

	return true;
}