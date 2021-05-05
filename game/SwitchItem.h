#pragma once
#include "Item.h"

#define	SWITCH_ANI_ID 21
#define SWITCH_ANI_ENABLE 0
#define SWITCH_ANI_DISABLE 1
#define SWITCH_STATE_DISABLE 100

class SwitchItem : public CItem
{
	void SetAnimation(int ani);
public:
	SwitchItem();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
