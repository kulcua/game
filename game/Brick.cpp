#include "Brick.h"
#include "Utils.h"

CBrick::CBrick(int type, float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	this->type = type;
	SetAnimation(BRICK_ANI_ID);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (GetState() == BRICK_STATE_DISABLE)
	{
		y += dy;

		if (y < start_y) // take brick to start_y after deflect cause disable
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

void CBrick::Render()
{
	int ani = 0;
	if (state == BRICK_STATE_DISABLE)
		ani = BRICK_ANI_DISABLE;	
	else if (type == BRICK_TYPE_QUESTION)
		ani = BRICK_ANI_QUESTION;
	else if (type == BRICK_TYPE_BLOCK)
		ani = BRICK_ANI_BLOCK;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_DISABLE:
		vy -= BRICK_JUMP_DEFLECT_Y;
		item->die = false;
		break;
	}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}