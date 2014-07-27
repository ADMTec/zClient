#pragma once
#include "stdafx.h"
#include <windows.h>

class Glow
{
public:
	// ----
	void	Load();
	void	RenderGlow();
	bool	LoadProgram(CGprogram* pDest, CGprofile profile, const char* szFile);
	void	DrawQuad(int width, int height, int ofsX = 0, int ofsY = 0);
	void	DoBlur(unsigned int uiSrcTex, unsigned int uiTargetTex, int srcTexWidth, int srcTexHeight, int destTexWidth, int destTexHeight, float xofs, float yofs);
	// ----
	bool g_bInitialised;
	unsigned int g_uiSceneTex;
	unsigned int g_uiBlurTex;
	int cg_blur_steps;
	int cg_enagled_glow;
	// ----
	PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
	// ----
	CGcontext g_cgContext;
	CGprofile g_cgVertProfile;
	CGprofile g_cgFragProfile;
	// ----
	CGprogram g_cgVP_GlowDarken;
	CGprogram g_cgFP_GlowDarken;
	// ----
	CGprogram g_cgVP_GlowBlur;
	CGprogram g_cgFP_GlowBlur;
	// ----
	CGprogram g_cgVP_GlowCombine;
	CGprogram g_cgFP_GlowCombine;
	// ----
	CGparameter g_cgpVP0_ModelViewMatrix;
	CGparameter g_cgpVP1_ModelViewMatrix;
	CGparameter g_cgpVP1_XOffset;
	CGparameter g_cgpVP1_YOffset;
	CGparameter g_cgpVP2_ModelViewMatrix;
}; extern Glow gGlow;