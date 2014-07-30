#include "stdafx.h"
#include "Protocol.h"
#include "Import.h"
#include "TMemory.h"
#include "Other.h"
#include "VisualFix.h"

Protocol gProtocol;

void Protocol::Load()
{
	//0065E94C   > E8 1C5A0000    CALL main.0066436D
	gTMemory.SetOp((LPVOID)0x0065E94C, this->DataRecv, ASM::CALL);
}

void Protocol::DataRecv(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	//printf("Recv:[%02X][%02X][%02X][%02X]\n",Data[0],Data[1],Data[2],Data[3]);
	BYTE ProtocolType = Data[0];

	if (ProtocolType == 0xC1)
	{
		switch (BYTE(Case))
		{
			case 0x11:
			{
				gVisualFix.RecvDamage((PMSG_ATTACKRESULT*)Data);
			}
			break;
			case 0x17:
			{
				gVisualFix.RecvKilledObject((PMSG_DIEPLAYER*)Data);
			}
			break;
			case 0xF1:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;
				switch (lpDef->subcode)
				{
					case 0x00:
					{
						gVisualFix.RecvIndex((PMSG_JOINRESULT*)Data);
					}
					break;
				}
			}
			break;
			case 0xF3:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;
				// ----
				switch (lpDef->subcode)
				{
					case 0x03:
					{
						gVisualFix.RecvUpPoint((PMSG_CHARMAPJOINRESULT*)Data);
					}
					break;
					case 0x04:
					{
						gVisualFix.RecvRespawn();
					}
					break;
				}
			}
			break;
			case 0x26:
			{
				gVisualFix.RecvHPSD((PMSG_REFILL*)Data);
			}
			break;
		}
	}

	pDataRecv(Case, Data, Len, aIndex);
}
