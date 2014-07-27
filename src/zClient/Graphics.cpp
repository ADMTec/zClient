#include "stdafx.h"
#include "Graphics.h"
#include "Import.h"
#include "TMemory.h"
#include "Glow.h"

Graphics gGraphics;

void (WINAPI *glEnable_original)(GLenum cap) = glEnable;

void WINAPI glEnable_hook(GLenum cap)
{
	//MaxAnisotropy
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &gGraphics.g_nMaxAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (int)gGraphics.g_nMaxAnisotropy);

	//Linear
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable_original(cap);
}

void Graphics::Load()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID &)glEnable_original, glEnable_hook);
	DetourTransactionCommit();
	// ----
	gTMemory.SetOp((LPVOID)0x0062EF74, (LPVOID)this->gluPerspectiveEx, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x00630E7F, (LPVOID)this->gluPerspectiveEx, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x009CEBC9, (LPVOID)this->gluPerspectiveEx, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x009CEF64, (LPVOID)this->gluPerspectiveEx, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x009CF70B, (LPVOID)this->gluPerspectiveEx, ASM::CALL);
	// ----
	gTMemory.SetByte((LPVOID)0x004D98D2, 0xB0);
	gTMemory.SetByte((LPVOID)0x004D98D3, 0x01);
	gTMemory.SetByte((LPVOID)0x004D98D4, 0x90);
	gTMemory.SetByte((LPVOID)0x004D98D5, 0x90);
	gTMemory.SetByte((LPVOID)0x004D98D6, 0x90);
	// ----
	gTMemory.SetOp((LPVOID)0x004D98B5, (LPVOID)this->CreateWindowMu, ASM::CALL);
	// ----
	gTMemory.SetOp((LPVOID)0x007BF771, (LPVOID)this->LoadImages, ASM::CALL);
	// ----
	gTMemory.SetOp((LPVOID)0x007CA832, (LPVOID)this->DrawInGame, ASM::CALL);
}

void Graphics::DrawInGame(int iType)
{
	gGlow.RenderGlow();
	// ----
	pDrawInGame(iType);
}

void Graphics::LoadImages()
{
	gGlow.Load();

	pLoadImages();
}

void Graphics::gluPerspectiveEx(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	if (fovy == 35.0 && pMapNumber == 94 && (pGameResolutionMode == 5 || pGameResolutionMode == 6)) //Zoom in Login Screen
		fovy = 28.0;

	gluPerspective(fovy, aspect, zNear, zFar);
}

HWND Graphics::CreateWindowMu(HINSTANCE hInstance)
{
	int v1;
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	struct tagRECT Rect;
	WNDCLASSEX WndClass;
	LPCSTR lpWindowName;
	HWND hWnd;

	lpWindowName = "MU";
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)MuWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIconA(0, "IDI_ICON1");
	WndClass.hCursor = LoadCursorA(0, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = 0;
	WndClass.lpszClassName = lpWindowName;
	WndClass.hIconSm = LoadIcon(0, "IDI_ICON1");

	RegisterClassExA(&WndClass);

	if (pGameWindowMode == 1)
	{
		Rect.left = 0;
		Rect.top = 0;
		Rect.right = pWinWidth;
		Rect.bottom = pWinHeight;

		if (pGameWindowMode == 1)
			AdjustWindowRect(&Rect, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_CAPTION, 0);
		else
			AdjustWindowRect(&Rect, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION, 0);

		Rect.right -= Rect.left;
		Rect.bottom -= Rect.top;

		if (pGameWindowMode == 1)
		{
			v1 = Rect.bottom;
			v2 = Rect.right;
			v3 = (GetSystemMetrics(SM_CYSCREEN) - Rect.bottom) / 2;
			v4 = GetSystemMetrics(SM_CXSCREEN);

			hWnd = CreateWindowExA(
				0,
				lpWindowName,
				lpWindowName,
				WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_CAPTION,
				(v4 - Rect.right) / 2,
				v3,
				v2,
				v1,
				0,
				0,
				hInstance,
				0);
		}
		else
		{
			v5 = Rect.bottom;
			v6 = Rect.right;
			v7 = (GetSystemMetrics(SM_CYSCREEN) - Rect.bottom) / 2;
			v8 = GetSystemMetrics(SM_CXSCREEN);

			hWnd = CreateWindowExA(
				0,
				lpWindowName,
				lpWindowName,
				WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION,
				(v8 - Rect.right) / 2,
				v7,
				v6,
				v5,
				0,
				0,
				hInstance,
				0);
		}
	}
	else
	{
		hWnd = CreateWindowExA(
			WS_EX_TOPMOST | WS_EX_APPWINDOW,
			lpWindowName,
			lpWindowName,
			WS_POPUP,
			0,
			0,
			pWinWidth,
			pWinHeight,
			0,
			0,
			hInstance,
			0);
	}
	
	pWindowLong = SetWindowLongPtr(hWnd, -0x04, 0x4D7C5F);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		1,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	GLuint PixelFormat;

	if (hWnd == 0)
	{
		return FALSE;
	}

	pThisHDC = GetDC(hWnd);

	if (pThisHDC == 0)
	{
		DestroyWindow(hWnd);
		hWnd = 0;
		return FALSE;
	}

	if (!gGraphics.arbMultisampleSupported)
	{
		PixelFormat = ChoosePixelFormat(pThisHDC, &pfd);

		if (PixelFormat == 0)
		{
			ReleaseDC(hWnd, pThisHDC);
			pThisHDC = 0;
			DestroyWindow(hWnd);
			hWnd = 0;
			return FALSE;
		}
	}
	else
	{
		PixelFormat = gGraphics.arbMultisampleFormat;
	}

	if (SetPixelFormat(pThisHDC, PixelFormat, &pfd) == FALSE)
	{
		ReleaseDC(hWnd, pThisHDC);
		pThisHDC = 0;
		DestroyWindow(hWnd);
		hWnd = 0;
		return FALSE;
	}

		pThisHGLRC = wglCreateContext(pThisHDC);

		if (pThisHGLRC == 0)
	{
		ReleaseDC(hWnd, pThisHDC);
		pThisHDC = 0;
		DestroyWindow(hWnd);
		hWnd = 0;
		return FALSE;
	}

	if (wglMakeCurrent(pThisHDC, pThisHGLRC) == FALSE)
	{
		wglDeleteContext(pThisHGLRC);
		pThisHGLRC = 0;
		ReleaseDC(hWnd, pThisHDC);
		pThisHDC = 0;
		DestroyWindow(hWnd);
		hWnd = 0;
		return FALSE;
	}

	if (!gGraphics.arbMultisampleSupported)
	{
		if (gGraphics.InitMultisample(hInstance, hWnd, pfd))
		{
			gGraphics.DestroyWindowGL(hWnd);
			return CreateWindowMu(hInstance);
		}
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return hWnd;
}

bool Graphics::DestroyWindowGL(HWND hWnd)
{
	if (pThisHWND != 0)
	{
		if (pThisHDC != 0)
		{
			wglMakeCurrent(pThisHDC, 0);
			if (pThisHGLRC != 0)
			{
				wglDeleteContext(pThisHGLRC);
				pThisHGLRC = 0;
			}
			ReleaseDC(pThisHWND, pThisHDC);
			pThisHDC = 0;
		}
		DestroyWindow(pThisHWND);
		pThisHWND = 0;
	}

	return TRUE;
}

bool Graphics::InitMultisample(HINSTANCE hInstance, HWND hWnd, PIXELFORMATDESCRIPTOR pfd)
{
	int iAASettings = GetPrivateProfileInt("AAMODE", "AntiAlias", 0, "./Option.ini");

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if (!wglChoosePixelFormatARB)
	{
		if (pThisHWND != 0)												// Does The Window Have A Handle?
		{
			if (pThisHDC != 0)											// Does The Window Have A Device Context?
			{
				wglMakeCurrent(pThisHDC, 0);							// Set The Current Active Rendering Context To Zero
				if (pThisHGLRC != 0)										// Does The Window Have A Rendering Context?
				{
					wglDeleteContext(pThisHGLRC);							// Release The Rendering Context
					pThisHGLRC = 0;										// Zero The Rendering Context
				}
				ReleaseDC(pThisHWND, pThisHDC);						// Release The Device Context
				pThisHDC = 0;											// Zero The Device Context
			}
			DestroyWindow(pThisHWND);									// Destroy The Window
			pThisHWND = 0;												// Zero The Window Handle
		}

		MessageBoxA(0, "Your graphics card driver doesn't support wglChoosePixelFormatARB.", "OpenGL Set Pixel Format Error.", 0x30u);
		::ExitProcess(0);

		this->arbMultisampleSupported = false;
		return false;
	}

	HDC hDC = GetDC(hWnd);

	int pixelFormat;
	int valid;
	UINT numFormats;
	float fAttributes[] = { 0, 0 };

	int iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 24,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 16,
		WGL_STENCIL_BITS_ARB, 0,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, iAASettings,
		0, 0
	};

	valid = wglChoosePixelFormatARB(hDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);

	if (valid && numFormats >= 1)
	{
		this->arbMultisampleSupported = true;
		this->arbMultisampleFormat = pixelFormat;

		return this->arbMultisampleSupported;
	}

	if (pThisHWND != 0)												// Does The Window Have A Handle?
	{
		if (pThisHDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent(pThisHDC, 0);							// Set The Current Active Rendering Context To Zero
			if (pThisHGLRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext(pThisHGLRC);							// Release The Rendering Context
				pThisHGLRC = 0;										// Zero The Rendering Context
			}
			ReleaseDC(pThisHWND, pThisHDC);						// Release The Device Context
			pThisHDC = 0;											// Zero The Device Context
		}
		DestroyWindow(pThisHWND);									// Destroy The Window
		pThisHWND = 0;												// Zero The Window Handle
	}

	char szMsg[128];
	sprintf_s(szMsg, "Your graphics card driver doesn't support x%d MultiSample.", iAASettings);
	MessageBoxA(0, szMsg, "OpenGL Set Pixel Format Error.", 0x30u);
	::ExitProcess(0);

	return  this->arbMultisampleSupported;
}