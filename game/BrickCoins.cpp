#include "BrickCoins.h"
#include "Utils.h"

BrickCoins::BrickCoins(int type, float x, float y) : CBrick(type, x, y)
{
	level = BRICK_LEVEL_MANY_ITEM;
	state = BRICK_STATE_NORMAL;
}

void BrickCoins::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (GetState() == BRICK_STATE_THROW_ITEM)
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
			if (numItem == 0)
			{
				SetState(BRICK_STATE_DISABLE);
			}
			else {
				SetState(BRICK_STATE_NORMAL);
			}
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
	//RenderBoundingBox();
}

void BrickCoins::SetState(int state)
{
	CBrick::SetState(state);
	switch (state)
	{
	case BRICK_STATE_THROW_ITEM:
	{
		if (numItem > 0)
		{
			numItem--;
			items[numItem]->die = false;
			vy = -BRICK_JUMP_DEFLECT_Y;
		}
		break;
	} 
	}
}