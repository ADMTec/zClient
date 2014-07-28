#pragma once
#include <windows.h>

class Graphics
{
public:
	// ----
	void	Load();
	static void gluPerspectiveEx(GLdouble fovy, GLdouble	aspect, GLdouble zNear, GLdouble zFar);
	static HWND	CreateWindowMu(HINSTANCE hInstance);
	bool InitMultisample(HINSTANCE hInstance, HWND hWnd, PIXELFORMATDESCRIPTOR pfd);
	static void LoadImages();
	static void DrawInGame(int iType);
	bool DestroyWindowGL(HWND hWnd);
	// ----
	int g_nMaxAnisotropy;
	int arbMultisampleFormat;
	bool arbMultisampleSupported;
	// ----
	bool isAnisoEnabled;
}; extern Graphics gGraphics;

