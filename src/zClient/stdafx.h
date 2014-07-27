#pragma once
// ----------------------------------------------------------------------------------------------
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdarg.h>
#include <process.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/wglext.h>
#include <gl/glext.h>
#include "detours.h"
#include <cg/cg.h>
#include <cg/cgGL.h>
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Detours.lib")
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")
// ----------------------------------------------------------------------------------------------
#define GL_TEXTURE_RECTANGLE_NV 0x84F5
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define IDI_ICON1                       101