//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
/*

===== item_suit.cpp ========================================================

  handling for the player's suit.
*/

#include "cbase.h"
#include "player.h"
#include "gamerules.h"
#include "items.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define SF_SUIT_SHORTLOGON		0x0001

class CItemSuit : public CItem
{
public:
	DECLARE_CLASS( CItemSuit, CItem );

	void Precache(void);
	void Spawn(void);
	bool MyTouch(CBasePlayer*pPlayer);
};

void CItemSuit::Precache(void)
{
	PrecacheModel("models/items/militaryvest.mdl");
	PrecacheScriptSound("ItemBattery.Touch");
	BaseClass::Precache();
}

void CItemSuit::Spawn(void)
{
	Precache();
	SetModel("models/items/militaryvest.mdl");
	BaseClass::Spawn();
}

bool CItemSuit::MyTouch(CBasePlayer *pPlayer)
{
	int pPlayerArmor = pPlayer->ArmorValue();

	if (pPlayerArmor > 50 || pPlayerArmor == 50)
		return FALSE;

	if (!pPlayer->IsSuitEquipped())
	{
		pPlayer->EquipSuit(false);
	}

	pPlayer->SetArmorValue(50);

	CPASAttenuationFilter filter(this, "ItemBattery.Touch");
	EmitSound(filter, entindex(), "ItemBattery.Touch");

	return true;
}

LINK_ENTITY_TO_CLASS(item_suit, CItemSuit);
