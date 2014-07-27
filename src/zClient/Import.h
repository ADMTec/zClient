#pragma once
#include <gl\GL.h>
//#pragma comment(lib, "Opengl32.lib")
//#pragma comment(lib, "glu32.lib")	
// ----
#define MAX_WIN_WIDTH	640
#define MAX_WIN_HEIGHT	480
// ----
#define pVersion		0x0118EF48
#define pAddress		0x0118DB1A
// ----
#define pGameLoad		((int(__cdecl*)()) 0x004D8180)
#define pWinWidth		*(GLsizei*)0x118EE38
#define pWinHeight		*(GLsizei*)0x118EE3C
#define pWinWidthReal	*(float*)0x11B3794
#define pWinHeightReal	*(float*)0x11B3798
// ----
#define pGameResolutionMode *(int*)0x11C3B38
#define pGameWindowMode *(int*)0x118D204
#define pInterfaceFunctionCall			((void(__cdecl*)(...)) 0x00927D4B)
// ----
#define pMapNumber		*(int*)0x118EDF8
#define pCameraZoom		0x118EE20
// ----
#define MuWndProc		((int(__cdecl*)(HWND,UINT,HDC,LPARAM)) 0x004D6F98)
#define pThisHWND		*(HWND*)0x011C3E7C
#define pThisHDC		*(HDC*)0x011C3E84
#define pThisHGLRC		*(HGLRC*)0x011C3E88
#define pWindowLong		*(DWORD*)0x011C3E34
#define pdwNewLong		0x004D7C5F
// ----
#define pLoadImages			((void(__cdecl*)()) 0x007BF9F5)
#define pDrawInGame			((void(__cdecl*)(...)) 0x0045124F)
// ----
#define pFileReader			((int(__cdecl*)(...)) 0x005526C2)
#define pModelDecode		((void(__cdecl*)(...)) 0x005D0F68)