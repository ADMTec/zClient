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
// ----------------------------------------------------------------------------------------------
#define MAKE_NUMBERW(x,y)  ( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )

struct PBMSG_HEAD
{
public:
	void set(LPBYTE lpBuf, BYTE head, BYTE size)	// line : 18
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 22

	void setE(LPBYTE lpBuf, BYTE head, BYTE size)	// line : 25
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 29

	BYTE c; //0
	BYTE size; //1
	BYTE headcode; //2
};

struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PMSG_REFILL
{
	PBMSG_HEAD h;	// C1:26
	BYTE IPos;	// 3
	BYTE LifeH;	// 4
	BYTE LifeL;	// 5
	BYTE Flag;	// 6
	BYTE btShieldH;	// 7
	BYTE btShieldL;	// 8
	// ----
	int Life; //9
	int Shield; //A
};

struct PMSG_MANASEND
{
	PBMSG_HEAD h;	// C1:27
	BYTE IPos;	// 3
	BYTE ManaH;	// 4
	BYTE ManaL;	// 5
	BYTE BPH;	// 6
	BYTE BPL;	// 7
	// ----
	int Mana;
	int BP;
};

struct PMSG_CHARMAPJOINRESULT
{
	PBMSG_HEAD h;	// C3:F3:03
	BYTE subcode;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
	BYTE MapNumber;	// 6
	BYTE Dir;	// 7

	BYTE ExpHHH; //
	BYTE ExpHHL; //
	BYTE ExpHLH; //
	BYTE ExpHLL; //
	BYTE ExpLHH; //
	BYTE ExpLHL; //
	BYTE ExpLLH; //
	BYTE ExpLLL; //

	BYTE NextExpHHH; //
	BYTE NextExpHHL; //
	BYTE NextExpHLH; //
	BYTE NextExpHLL; //
	BYTE NextExpLHH; //
	BYTE NextExpLHL; //
	BYTE NextExpLLH; //
	BYTE NextExpLLL; //

	WORD LevelUpPoint;	// 10
	WORD Str;	// 12
	WORD Dex;	// 14
	WORD Vit;	// 16
	WORD Energy;	// 18
	WORD Life;	// 1A
	WORD MaxLife;	// 1C
	WORD Mana;	// 1E
	WORD MaxMana;	// 20
	WORD wShield;	// 22
	WORD wMaxShield;	// 24
	WORD BP;	// 26
	WORD MaxBP;	// 28
	int Money;	// 2C
	BYTE PkLevel;	// 30
	BYTE CtlCode;	// 31
	short AddPoint;	// 32
	short MaxAddPoint;	// 34
	WORD Leadership;	// 36
	WORD wMinusPoint;	// 38
	WORD wMaxMinusPoint;	// 3A
	BYTE btExtendedInvenCount; //
	short sExGameServerCode; //
	BYTE btExtendedWarehouseCount; //
	int  UpPoint;
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;	// C1:DC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE DamageH;	// 5
	BYTE DamageL;	// 6
	BYTE unk1; //A
	BYTE DamageType;	// 7
	BYTE btShieldDamageH;	// 8
	BYTE btShieldDamageL;	// 9
	BYTE unk2; //B
	//---
	int AttackHP;
	int AttackSD;
};

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;	// C1:F1
	BYTE scode;	// 3
	BYTE result;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
	BYTE CliVersion[5];	// 7
};

struct PMSG_DIEPLAYER
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;

	//Season 3.5 changed (old Season 3.0 was only BYTE)
	BYTE SkillH;
	BYTE SkillL;

	BYTE KillerNumberH;
	BYTE KillerNumberL;
};