#include <windows.h>
#include <stdio.h>
#include "Glow.h"
#include "Import.h"

Glow gGlow;

void Glow::Load()
{
	this->cg_blur_steps = 4;
	this->cg_enagled_glow = 1;

	this->glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");

	unsigned char* pBlankTex = new unsigned char[pWinWidth*pWinHeight * 3];
	memset(pBlankTex, 0, pWinWidth*pWinHeight * 3);

	glGenTextures(1, &this->g_uiSceneTex);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiSceneTex);
	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB8, pWinWidth, pWinHeight, 0, GL_RGB8, GL_UNSIGNED_BYTE, pBlankTex);

	glGenTextures(1, &this->g_uiBlurTex);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiBlurTex);
	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB8, pWinWidth / 2, pWinHeight / 2, 0, GL_RGB8, GL_UNSIGNED_BYTE, pBlankTex);

	delete[] pBlankTex;

	this->g_bInitialised = true;

	this->g_cgContext = cgCreateContext();
	if (!this->g_cgContext)
	{
		MessageBox(NULL, "Couldn't make Cg context", NULL, NULL);
		return;
	}

	this->g_cgVertProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	if (this->g_cgVertProfile == CG_PROFILE_UNKNOWN)
	{
		MessageBox(NULL, "Couldn't fetch valid VP profile", NULL, NULL);
		return;
	}

	cgGLSetOptimalOptions(this->g_cgVertProfile);

	if (!LoadProgram(&this->g_cgVP_GlowDarken, this->g_cgVertProfile, "Data/Custom/Shader/glow_darken_vp.cg"))
		return;

	if (!LoadProgram(&this->g_cgVP_GlowBlur, this->g_cgVertProfile, "Data/Custom/Shader/glow_blur_vp.cg"))
		return;

	if (!LoadProgram(&this->g_cgVP_GlowCombine, this->g_cgVertProfile, "Data/Custom/Shader/glow_combine_vp.cg"))
		return;

	this->g_cgpVP0_ModelViewMatrix = cgGetNamedParameter(this->g_cgVP_GlowDarken, "ModelViewProj");
	this->g_cgpVP1_ModelViewMatrix = cgGetNamedParameter(this->g_cgVP_GlowBlur, "ModelViewProj");
	this->g_cgpVP1_XOffset = cgGetNamedParameter(this->g_cgVP_GlowBlur, "XOffset");
	this->g_cgpVP1_YOffset = cgGetNamedParameter(this->g_cgVP_GlowBlur, "YOffset");
	this->g_cgpVP2_ModelViewMatrix = cgGetNamedParameter(this->g_cgVP_GlowCombine, "ModelViewProj");

	this->g_cgFragProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	if (this->g_cgFragProfile == CG_PROFILE_UNKNOWN)
	{
		MessageBox(NULL, "Couldn't fetch valid FP profile", NULL, NULL);
		return;
	}

	cgGLSetOptimalOptions(this->g_cgFragProfile);

	if (!LoadProgram(&this->g_cgFP_GlowDarken, this->g_cgFragProfile, "Data/Custom/Shader/glow_darken_fp.cg"))
		return;

	if (!LoadProgram(&this->g_cgFP_GlowBlur, this->g_cgFragProfile, "Data/Custom/Shader/glow_blur_fp.cg"))
		return;

	if (!LoadProgram(&this->g_cgFP_GlowCombine, this->g_cgFragProfile, "Data/Custom/Shader/glow_combine_fp.cg"))
		return;
}

bool Glow::LoadProgram(CGprogram* pDest, CGprofile profile, const char* szFile)
{
	char file[512];
	sprintf_s(file, "%s", szFile);

	*pDest = cgCreateProgramFromFile(this->g_cgContext, CG_SOURCE, file, profile, "main", 0);
	if (!(*pDest)) {
		MessageBox(NULL, cgGetErrorString(cgGetError()), NULL, NULL);
		return false;
	}

	cgGLLoadProgram(*pDest);

	return true;
}

void Glow::DrawQuad(int width, int height, int ofsX, int ofsY)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0, height);
	glVertex3f(0, 0, -1);
	glTexCoord2f(width, height);
	glVertex3f(1, 0, -1);
	glTexCoord2f(width, 0);
	glVertex3f(1, 1, -1);
	glEnd();
}

void Glow::DoBlur(unsigned int uiSrcTex, unsigned int uiTargetTex, int srcTexWidth, int srcTexHeight, int destTexWidth, int destTexHeight, float xofs, float yofs)
{
	cgGLBindProgram(this->g_cgVP_GlowBlur);
	cgGLBindProgram(this->g_cgFP_GlowBlur);

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

	this->glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

	this->glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

	this->glActiveTextureARB(GL_TEXTURE3_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

	cgGLSetParameter1f(this->g_cgpVP1_XOffset, xofs);
	cgGLSetParameter1f(this->g_cgpVP1_YOffset, yofs);

	glViewport(0, 0, destTexWidth, destTexHeight);

	DrawQuad(srcTexWidth, srcTexHeight);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiTargetTex);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, destTexWidth, destTexHeight, 0);
}

void Glow::RenderGlow()
{
	if (!this->g_bInitialised)
		this->Load();

	if (this->cg_blur_steps == 0)
		return;

	if (this->cg_enagled_glow == 0)
		return;

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiSceneTex);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, pWinWidth, pWinHeight, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, 0.1, 100);

	glColor3f(1, 1, 1);

	cgGLEnableProfile(this->g_cgVertProfile);
	cgGLEnableProfile(this->g_cgFragProfile);

	cgGLBindProgram(this->g_cgVP_GlowDarken);
	cgGLBindProgram(this->g_cgFP_GlowDarken);

	cgGLSetStateMatrixParameter(this->g_cgpVP0_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	glViewport(0, 0, pWinWidth / 4, pWinHeight / 4);

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiSceneTex);

	this->DrawQuad(pWinWidth, pWinHeight);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiBlurTex);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, pWinWidth / 4, pWinHeight / 4, 0);

	cgGLBindProgram(this->g_cgVP_GlowBlur);
	cgGLBindProgram(this->g_cgFP_GlowBlur);

	cgGLSetStateMatrixParameter(this->g_cgpVP1_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	int iNumBlurSteps = this->cg_blur_steps;
	for (int i = 0; i < iNumBlurSteps; i++)
	{
		this->DoBlur(this->g_uiBlurTex, this->g_uiBlurTex, pWinWidth / 2, pWinHeight / 2, pWinWidth / 2, pWinHeight / 2, 1, 0);
		this->DoBlur(this->g_uiBlurTex, this->g_uiBlurTex, pWinWidth / 2, pWinHeight / 2, pWinWidth / 2, pWinHeight / 2, 0, 1);
	}

	cgGLBindProgram(this->g_cgVP_GlowCombine);
	cgGLBindProgram(this->g_cgFP_GlowCombine);

	cgGLSetStateMatrixParameter(this->g_cgpVP2_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiSceneTex);

	this->glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->g_uiBlurTex);

	glViewport(0, 0, pWinWidth, pWinHeight);
	this->DrawQuad(pWinWidth / 4, pWinHeight / 4);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	cgGLDisableProfile(this->g_cgVertProfile);
	cgGLDisableProfile(this->g_cgFragProfile);

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_RECTANGLE_NV);

	this->glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_RECTANGLE_NV);

	this->glActiveTextureARB(GL_TEXTURE2_ARB);
	glDisable(GL_TEXTURE_RECTANGLE_NV);

	this->glActiveTextureARB(GL_TEXTURE3_ARB);
	glDisable(GL_TEXTURE_RECTANGLE_NV);

	this->glActiveTextureARB(GL_TEXTURE0_ARB);
}