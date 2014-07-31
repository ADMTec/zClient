#include "stdafx.h"
#include "VisualFix.h"
#include "Import.h"
#include "TMemory.h"
#include "Other.h"

VisualFix gVisualFix;

Naked(MPVisualFix)
{
	_asm
	{
		// ----
		MOV gVisualFix.movEax, EAX
		MOV gVisualFix.movEcx, ECX
		MOV gVisualFix.movEdx, EDX
		MOV gVisualFix.movEbx, EBX
		MOV gVisualFix.movEsp, ESP
		MOV gVisualFix.movEbp, EBP
		MOV gVisualFix.movEsi, ESI
		MOV gVisualFix.movEdi, EDI
		// ----
	}

	if ((gVisualFix.Mana != gVisualFix.OldMana) || gVisualFix.MaxMana != gVisualFix.OldMaxMana)
	{
		printf("Mana:%d OldMana:%d MaxMana:%d OldMaxMana:%d\n", gVisualFix.Mana, gVisualFix.OldMana, gVisualFix.MaxMana, gVisualFix.OldMaxMana);
		// ----
		gVisualFix.OldMana = gVisualFix.Mana;
		gVisualFix.OldMaxMana = gVisualFix.MaxMana;
		// ----
		_asm
		{
			// ----
			MOV EAX, gVisualFix.movEax
			MOV ECX, gVisualFix.movEcx
			MOV EDX, gVisualFix.movEdx
			MOV EBX, gVisualFix.movEbx
			MOV ESP, gVisualFix.movEsp
			MOV EBP, gVisualFix.movEbp
			MOV ESI, gVisualFix.movEsi
			MOV EDI, gVisualFix.movEdi
			// ----
			JMP gVisualFix.jmpMPVisualFix00
		}
	}

	_asm
	{
		// ----
		MOV EAX, gVisualFix.movEax
		MOV ECX, gVisualFix.movEcx
		MOV EDX, gVisualFix.movEdx
		MOV EBX, gVisualFix.movEbx
		MOV ESP, gVisualFix.movEsp
		MOV EBP, gVisualFix.movEbp
		MOV ESI, gVisualFix.movEsi
		MOV EDI, gVisualFix.movEdi
		// ----
		JMP gVisualFix.jmpMPVisualFix01
	}
}

Naked(HPVisualFix)
{
	_asm
	{
		// ----
		MOV gVisualFix.movEax, EAX
		MOV gVisualFix.movEcx, ECX
		MOV gVisualFix.movEdx, EDX
		MOV gVisualFix.movEbx, EBX
		MOV gVisualFix.movEsp, ESP
		MOV gVisualFix.movEbp, EBP
		MOV gVisualFix.movEsi, ESI
		MOV gVisualFix.movEdi, EDI
		// ----
	}

	if ((gVisualFix.Life != gVisualFix.OldLife) || gVisualFix.MaxLife != gVisualFix.OldMaxLife)
	{
		printf("Life:%d OldLife:%d MaxLife:%d OldMaxLife:%d\n", gVisualFix.Life, gVisualFix.OldLife, gVisualFix.MaxLife, gVisualFix.OldMaxLife);
		// ----
		gVisualFix.OldLife = gVisualFix.Life;
		gVisualFix.OldMaxLife = gVisualFix.MaxLife;
		// ----
		_asm
		{
			// ----
			MOV EAX, gVisualFix.movEax
			MOV ECX, gVisualFix.movEcx
			MOV EDX, gVisualFix.movEdx
			MOV EBX, gVisualFix.movEbx
			MOV ESP, gVisualFix.movEsp
			MOV EBP, gVisualFix.movEbp
			MOV ESI, gVisualFix.movEsi
			MOV EDI, gVisualFix.movEdi
			// ----
			JMP gVisualFix.jmpHPVisualFix00
		}
	}

	_asm
	{
		// ----
		MOV EAX, gVisualFix.movEax
		MOV ECX, gVisualFix.movEcx
		MOV EDX, gVisualFix.movEdx
		MOV EBX, gVisualFix.movEbx
		MOV ESP, gVisualFix.movEsp
		MOV EBP, gVisualFix.movEbp
		MOV ESI, gVisualFix.movEsi
		MOV EDI, gVisualFix.movEdi
		// ----
		JMP gVisualFix.jmpHPVisualFix01
	}
}

void VisualFix::Load()
{
	this->jmpHPVisualFix00 = 0x009945CE;
	this->jmpHPVisualFix01 = 0x00994607;
	// ----
	this->jmpMPVisualFix00 = 0x00994625;
	this->jmpMPVisualFix01 = 0x0099465E;
	// ----
	gTMemory.SetRange((LPVOID)0x009945B0, 6, ASM::NOP);
	gTMemory.SetOp((LPVOID)0x009945B0, HPVisualFix, ASM::JMP);
	// ----
	gTMemory.SetRange((LPVOID)0x00994607, 6, ASM::NOP);
	gTMemory.SetOp((LPVOID)0x00994607, MPVisualFix, ASM::JMP);
	// ----
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
	this->OldLife = 0;
	this->OldMaxLife = 0;
	this->OldMana = 0;
	this->OldMaxMana = 0;
	this->BonusExp = 100;
	// ----
	gTMemory.SetOp((LPVOID)0x009945FF, this->SetHP, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x00976FE4, this->SetHP, ASM::CALL);
	gTMemory.SetOp((LPVOID)0x00994656, this->SetMP, ASM::CALL);
	// ----
	gTMemory.SetOp((LPVOID)0x009763FF, this->SetDetailText, ASM::CALL);
	// ----
	gTMemory.SetOp((LPVOID)0x009956B9, this->SetBonusExp, ASM::CALL);
	//E8 8D26F9FF      CALL main.00927D4B
}

void VisualFix::SetBonusExp(DWORD unk, char* function, char* params, char* param1)
{
	printf("SetBonusExp:%s\n",param1);
	pGFXSetDetail(unk, function, params, param1);
}

void VisualFix::SetDetailText(DWORD unk, char* function, char* params, char* param1, char* param2, char* param3, char* param4, char* param5, char* param6, char* param7, char* param8, char* param9, char* param10)
{
	printf("Param6:%s , Param7:%s, Param8:%s\n",param6,param7,param8);
	char szHP[128];
	sprintf_s(szHP, "<FONT color='#ffffffff'>HP: %d / %d</FONT><BR>", gVisualFix.Life, gVisualFix.MaxLife);

	char szMP[128];
	sprintf_s(szMP, "<FONT color='#ffffffff'>Mana: %d / %d</FONT><BR>", gVisualFix.Mana, gVisualFix.MaxMana);

	pGFXSetDetail(unk, function, params, param1, param2, param3, param4, param5, szMP, param7, param8, szHP, param10);
}

void VisualFix::SetMP(DWORD unk, char* function, char* params, int param1, int param2)
{
	printf("SetMP:%d %d\n",param1,param2);
	pGFXSetInfo(unk, function, params, gVisualFix.Mana, gVisualFix.MaxMana);
}

void VisualFix::SetHP(DWORD unk, char* function, char* params, int param1, int param2)
{
	printf("SetHP:%d %d %d\n",unk, param1, param2);
	pGFXSetInfo(unk, function, params, gVisualFix.Life, gVisualFix.MaxLife);
}

void VisualFix::RecvIndex(PMSG_JOINRESULT *lpRecv)
{
	this->aIndex = MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL);
	this->PlayerKill = FALSE;
}

void VisualFix::RecvDamage(PMSG_ATTACKRESULT *lpRecv)
{
	this->AttackHP = lpRecv->AttackHP;
	this->AttackSD = lpRecv->AttackSD;

	short tIndex = MAKE_NUMBERW(lpRecv->NumberH & 0x7F, lpRecv->NumberL);

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

void VisualFix::RecvMPAG(PMSG_MANASEND* lpRecv)
{
	if (lpRecv->IPos == 0xFF)
	{
		this->Mana = lpRecv->Mana;
		this->AG = lpRecv->BP;
	}
	else if (lpRecv->IPos == 0xFE)
	{
		this->MaxMana = lpRecv->Mana;
		this->MaxAG = lpRecv->BP;
	}
	if (this->Mana > this->MaxMana)
	{
		this->Mana = this->MaxMana;
	}
}

void VisualFix::RecvUpPoint(PMSG_CHARMAPJOINRESULT *lpRecv)
{
	this->UpPoint = lpRecv->UpPoint;
	this->Life = lpRecv->Life;
}

void VisualFix::RecvRespawn()
{
	this->PlayerKill = FALSE;
	this->Life = this->MaxLife;
	this->SD = this->MaxSD;
}