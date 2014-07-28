#include "stdafx.h"
#include "Resolution.h"
#include "Import.h"
#include "TMemory.h"

Resolution gResolution;

void Resolution::Load()
{
	gTMemory.SetOp((LPVOID)0x004D945F, (LPVOID)this->GameLoad, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x00987BCC, (LPVOID)this->ChatPositionFix, ASM::CALL);
}

void Resolution::ChatPositionFix(LPVOID This, char *szFunctionName, char *szParams, double PosX, double PosY, double i6, double i7)
{
	if (PosY == 0)
		PosY = pWinHeight - 575.0;

	pInterfaceFunctionCall(This, szFunctionName, szParams, PosX, PosY, i6, i7);
}

int Resolution::GameLoad()
{
	float pZoom;
	gTMemory.GetFloat((LPVOID)pCameraZoom, pZoom);
	gTMemory.SetFloat((LPVOID)pCameraZoom, 75.0);

	printf("Zoom:%f\n",pZoom);
	// ----
	printf("pGameLoad\n");
	pGameLoad();

	switch (pGameResolutionMode)
	{
		case 5:
		{
			pWinWidth = 1280;
			pWinHeight = 720;
		}
		break;
		case 6:
		{
			pWinWidth = 1366;
			pWinHeight = 768;
		}
		break;
	}

	pWinWidthReal = (float)pWinWidth / MAX_WIN_WIDTH;
	pWinHeightReal = (float)pWinHeight / MAX_WIN_HEIGHT;

	return 1;
}