#include "BrickCoins.h"
#include "Utils.h"

BrickCoins::BrickCoins(int type, float x, float y) : CBrick(type, x, y)
{
	level = BRICK_LEVEL_MANY_ITEM;
	start_y = y;
}

void BrickCoins::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (numItem == 0)
		SetState(BRICK_STATE_DISABLE);
	else if (GetState() == BRICK_STATE_THROW_ITEM && numItem > 0)
	{
		y += dy;

		if (y < start_y)
		{
			vy = BRICK_RETURN_START_POS_VY;
		}
		else
		{
			y = start_y;
			vy = 0;
		}
	}
}

void BrickCoins::Render()
{
	int ani = 0;
	if (state == BRICK_STATE_DISABLE)
		ani = BRICK_ANI_DISABLE;
	else ani = BRICK_ANI_BLOCK;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void BrickCoins::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_THROW_ITEM:
	{
		vy = -BRICK_JUMP_DEFLECT_Y;
		numItem--;
		if (numItem > 0)
			items[numItem]->die = false;
		/*DebugOut(L"%d\n", numItem);*/
	} break;
	}
}