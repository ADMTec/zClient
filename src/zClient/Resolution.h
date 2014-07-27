#pragma once
#include <windows.h>

class Resolution
{
public:
	// ----
	void	Load();
	static int GameLoad();
	static void ChatPositionFix(LPVOID This, char *szFunctionName, char *szParams, double PosX, double PosY, double i6, double i7);
}; extern Resolution gResolution;