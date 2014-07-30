#pragma once
#include <windows.h>

class VisualFix
{
public:
	// ----
	void	Load();
	void	RecvHPSD(PMSG_REFILL * Data);
	void	RecvUpPoint(PMSG_CHARMAPJOINRESULT *lpRecv);
	void	RecvDamage(PMSG_ATTACKRESULT *lpRecv);
	void	RecvIndex(PMSG_JOINRESULT * Data);
	void	RecvKilledObject(PMSG_DIEPLAYER *lpRecv);
	void	RecvRespawn();
	static void SetDetailText(DWORD unk, char* function, char* params, char* param1, char* param2, char* param3, char* param4, char* param5, char* param6, char* param7, char* param8, char* param9, char* param10);
	// ----
	static void SetHP(DWORD, char*, char*, int, int);
	// ----
	short	aIndex;
	int	AttackHP;
	int	AttackSD;
	int	Life;
	int	SD;
	int	Mana;
	int	AG;
	int	MaxLife;
	int	MaxSD;
	int	MaxMana;
	int	MaxAG;
	int	UpPoint;
	bool PlayerKill;
	int	AttackRate;
	int	DamageRate;
	// ----
}; extern VisualFix gVisualFix;