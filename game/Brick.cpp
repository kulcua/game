#include "Brick.h"
#include "Utils.h"

CBrick::CBrick(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	start_y = y; //save y
	this->typeItem = type;
	SetAnimation(22);
}

void CBrick::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (y < start_y)
	{
		//vy += BRICK_DROP_SPEED_Y * dt;  
		y++; //cong ve vi tri cu cua y
	}
}

void CBrick::Render()
{
	int ani;
	if (state == BRICK_STATE_DISABLE)
	{
		//return;
		ani = BRICK_ANI_DISABLE;
	}	
	else
	{
		ani = BRICK_ANI_ENABLE;
	}
	animation_set->at(ani)->Render(x, y, NULL);
	//RenderBoundingBox();
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_DISABLE:
		y -= BRICK_JUMP_DEFLECT_Y;
		break;
	default:
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