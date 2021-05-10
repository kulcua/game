#include "ParaKoopa.h"

ParaKoopa::ParaKoopa() 
{
	level = PARAKOOPA_LEVEL_JUMP;
	SetState(PARAKOOPA_STATE_JUMP);
}

void ParaKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPA_BBOX_WIDTH;
	if (state == KOOPA_STATE_WALKING)
		b = y + KOOPA_BBOX_HEIGHT;
	else if (state == PARAKOOPA_STATE_JUMP)
		b = y + PARAKOOPA_BBOX_JUMP_HEIGHT;
	else
		b = y + KOOPA_BBOX_HEIGHT_DIE;
}

void ParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CKoopa::Update(dt, coObjects);
	
	if (level == PARAKOOPA_LEVEL_JUMP && isOnGround)
	{
		vy = -PARAKOOPA_JUMP_SPEED;
		isOnGround = false;
	}
}

void ParaKoopa::Render()
{
	int ani = 0;
	if (state == KOOPA_STATE_BALL)
	{
		if (vx == 0)
			ani = PARAKOOPA_ANI_BALL;
		else ani = PARAKOOPA_ANI_BALL_ROLL;
	}
	else if (state == KOOPA_STATE_WALKING)
		ani = PARAKOOPA_ANI_WALK;
	else
		ani = PARAKOOPA_ANI_JUMP;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void ParaKoopa::SetState(int state)
{
	CKoopa::SetState(state);
	switch (state)
	{
	case PARAKOOPA_STATE_JUMP:
		vy = -PARAKOOPA_JUMP_SPEED;
		vx = KOOPA_WALKING_SPEED * nx;
		isOnGround = false;
		break;
	}
}