#include "stdafx.h"
#include "TMemory.h"
#include "Import.h"
#include "Resolution.h"
#include "Other.h"
#include "Graphics.h"
#include "Glow.h"
#include "GFXLoad.h"
#include "Protocol.h"
#include "VisualFix.h"

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
			gGFXLoad.Load();
			gProtocol.Load();
			gVisualFix.Load();
			// ----
			gGlow.isEnabled = GetPrivateProfileInt("GLOW", "Enabled", 0, "./Option.ini"); // I just put it here
			// ----
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