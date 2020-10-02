#include "Koopas.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPAS_BBOX_WIDTH;
	if (state != KOOPAS_STATE_DIE)
	{
		b = y + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		b = y + KOOPAS_BBOX_HEIGHT_DIE;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	// TO-DO: make sure Koopas can interact with the world and to each of them too!

	x += dx;
	y += dy;

	if (vx < 0 && x < 510) {
		x = 510; vx = -vx;
		nx = 1;
	}

	if (vx > 0 && x > 600) {
		x = 600; vx = -vx;
		nx = -1;
	}
}

void CKoopas::Render()
{
	int ani;
	if (state == KOOPAS_STATE_DIE)
	{
		ani = KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_BALL)
		ani = KOOPAS_ANI_BALL;
	else
		ani = KOOPAS_ANI_WALKING;

	animation_set->at(ani)->Render(x, y, nx);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		break;
	
	case KOOPAS_STATE_BALL:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		break;

	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	}
}
