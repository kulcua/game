#include "SwitchItem.h"

SwitchItem::SwitchItem()
{
	SetAnimation(SWITCH_ANI_ID);
}

void SwitchItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void SwitchItem::Render()
{
	int ani;
	if (state == SWITCH_STATE_DISABLE)
		ani = SWITCH_ANI_DISABLE;
	else ani = SWITCH_ANI_ENABLE;
	animation_set->at(ani)->Render(x, y, nx);
}