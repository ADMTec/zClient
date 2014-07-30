#include "stdafx.h"
#include "VisualFix.h"
#include "Import.h"
#include "TMemory.h"
#include "Other.h"

VisualFix gVisualFix;

void VisualFix::Load()
{
	this->aIndex = 0;
	this->AttackHP = 0;
	this->AttackSD = 0;
	this->Life = 0;
	this->SD = 0;
	this->Mana = 0;
	this->AG = 0;
	this->MaxLife = 0;
	this->MaxSD = 0;
	this->MaxMana = 0;
	this->MaxAG = 0;
	this->UpPoint = 0;
	this->PlayerKill = TRUE;
	this->AttackRate = 0;
	this->DamageRate = 0;
	// ----
	//00976FBE   E8 880DFBFF      CALL main.00927D4B
	gTMemory.SetOp((LPVOID)0x00976FBE, this->SetHP, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x009945FF, this->SetHP, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x00976FE4, this->SetHP, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x0097D5E3, this->SetHP, ASM::CALL);
	//00976FE4   E8 620DFBFF      CALL main.00927D4B
	//009945FF   E8 4737F9FF      CALL main.00927D4B
	//0097D5E3   E8 63A7FAFF      |CALL main.00927D4B
	//009763EF   68 C0A30201      PUSH main.0102A3C0; ASCII "%s %s %s %s %s %s %s %s %s %s %s"
	//009763F4   68 E4A30201      PUSH main.0102A3E4; ASCII "SetDetailText"
	//009763F9   FFB5 3CF3FFFF    PUSH DWORD PTR SS : [EBP - CC4]
	//009763FF   E8 4719FBFF      CALL main.00927D4B
	gTMemory.SetOp((LPVOID)0x009763FF, this->SetDetailText, ASM::CALL);
}

void VisualFix::SetDetailText(DWORD unk, char* function, char* params, char* param1, char* param2, char* param3, char* param4, char* param5, char* param6, char* param7, char* param8, char* param9, char* param10)
{
	//printf("SetDetailText:%d\n",unk);

	char szHP[64];
	sprintf_s(szHP, "<FONT color='#ffffffff'>HP: %d / %d</FONT><BR>", gVisualFix.Life, gVisualFix.MaxLife);

	pGFXSetDetail(unk, function, params, param1, param2, param3, param4, param5, param6, param7, param8, szHP, param10);
}

void VisualFix::SetHP(DWORD unk, char* function, char* params, int param1, int param2)
{
	//printf("SetHP:%d\n",unk);
	pGFXSetInfo(unk, function, params, gVisualFix.Life, gVisualFix.MaxLife);
}

void VisualFix::RecvIndex(PMSG_JOINRESULT *lpRecv)
{
	printf("RecvIndex: %d\n", MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL));
	this->aIndex = MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL);
	this->PlayerKill = FALSE;
}

void VisualFix::RecvDamage(PMSG_ATTACKRESULT *lpRecv)
{
	printf("RecvDamage1 %d %d %d\n", lpRecv->AttackHP, lpRecv->AttackSD, MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL));

	this->AttackHP = lpRecv->AttackHP;
	this->AttackSD = lpRecv->AttackSD;

	short tIndex = MAKE_NUMBERW(lpRecv->NumberH & 0x7F, lpRecv->NumberL);
	printf("RecvDamage2 %d %d %d\n", lpRecv->AttackHP, lpRecv->AttackSD, tIndex);
	if (this->aIndex == tIndex)
	{
		this->Life -= this->AttackHP;
		this->SD -= this->AttackSD;

		if (this->Life < 0)
		{
			this->Life = 0;
		}
	}
}

void VisualFix::RecvKilledObject(PMSG_DIEPLAYER *lpRecv)
{
	printf("RecvKilledObject %d %d", MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL), this->aIndex);
	short tIndex = MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL);
	if (this->aIndex == tIndex)
	{
		this->Life = 0;
		this->SD = 0;
		this->PlayerKill = TRUE;
	}
}

void VisualFix::RecvHPSD(PMSG_REFILL * Data)
{
	printf("RecvHPSD:%d %d %d\n",Data->IPos,Data->Life,Data->Shield);

	if (Data->IPos == 0xFF)
	{
		this->Life = Data->Life;
		this->SD = Data->Shield;
	}
	else if (Data->IPos == 0xFE)
	{
		this->MaxLife = Data->Life;
		this->MaxSD = Data->Shield;
	}
	if (this->Life > this->MaxLife)
	{
		this->Life = this->MaxLife;
	}
	if (this->PlayerKill == TRUE)
	{
		this->Life = 0;
		this->SD = 0;
	}
}

void VisualFix::RecvUpPoint(PMSG_CHARMAPJOINRESULT *lpRecv)
{
	printf("RecvUpPoint %d\n",lpRecv->Life);
	this->UpPoint = lpRecv->UpPoint;
	this->Life = lpRecv->Life;
}

void VisualFix::RecvRespawn()
{
	printf("RecvRespawn %d %d\n",this->MaxLife,this->MaxSD);
	this->PlayerKill = FALSE;
	this->Life = this->MaxLife;
	this->SD = this->MaxSD;
}