#include "stdafx.h"
#include "TMemory.h"
#include "Import.h"
#include "Resolution.h"
#include "Other.h"
#include "Graphics.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			InitConsole();
			// ----
			gResolution.Load();
			gGraphics.Load();
			gOther.Load();
			// ----
			MessageBox(0, "Loaded", "Caption", 0);
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