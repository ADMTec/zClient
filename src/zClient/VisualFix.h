#pragma once
#include <windows.h>

class VisualFix
{
public:
	// ----
	void	Load();
	void	RecvHPSD(PMSG_REFILL * Data);
	void	RecvMPAG(PMSG_MANASEND * Data);
	void	RecvUpPoint(PMSG_CHARMAPJOINRESULT *lpRecv);
	void	RecvDamage(PMSG_ATTACKRESULT *lpRecv);
	void	RecvIndex(PMSG_JOINRESULT * Data);
	void	RecvKilledObject(PMSG_DIEPLAYER *lpRecv);
	void	RecvRespawn();
	static void SetDetailText(DWORD , char* , char* , char* , char* , char* , char* , char* , char* , char* , char* , char* , char* );
	static void SetHP(DWORD, char*, char*, int, int);
	static void SetMP(DWORD, char*, char*, int, int);
	static void SetBonusExp(DWORD, char*, char*, char*);
	// ----
	short	aIndex;
	int	AttackHP;
	int	AttackSD;
	int	Life;
	int OldLife;
	int	SD;
	int	Mana;
	int OldMana;
	int	AG;
	int	MaxLife;
	int OldMaxLife;
	int	MaxSD;
	int	MaxMana;
	int OldMaxMana;
	int	MaxAG;
	int	UpPoint;
	bool PlayerKill;
	int	AttackRate;
	int	DamageRate;
	int BonusExp;
	// ----
	DWORD movEax;
	DWORD movEcx;
	DWORD movEdx;
	DWORD movEbx;
	DWORD movEsp;
	DWORD movEbp;
	DWORD movEsi;
	DWORD movEdi;
	DWORD jmpHPVisualFix00;
	DWORD jmpHPVisualFix01;
	DWORD jmpMPVisualFix00;
	DWORD jmpMPVisualFix01;
}; extern VisualFix gVisualFix;