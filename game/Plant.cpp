#include "Plant.h"
#include "Ground.h"
#include "Game.h"
#include "EffectPool.h"
#include "Mario.h"

CPlant::CPlant(float y) {
	startY = y;
	vy = -PLANT_SPEED;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (abs(mario->x - x) > PLANT_NEAR_MARIO_DISTANCE)
		isNearMario = false;
	else isNearMario = true;

	y += dy;

	if (y > startY)
	{
		vy = 0;
		if (isNearMario == false)
			vy = -PLANT_SPEED;
	}
}

void CPlant::SetState(int state)
{
	switch (state)
	{
	case PLANT_STATE_DIE:
	{
		Effect* effect1 = EffectPool::GetInstance()->Create();
		if (effect1 != NULL)
			effect1->Init(EffectName::marioTailAttack, x, y);
		//Effect* effect2 = EffectPool::GetInstance()->Create();
		//if (effect2 != NULL)
		//	effect2->Init(EffectName::fireballDestroy, x, y);
		Effect* effect3 = EffectPool::GetInstance()->Create();
		if (effect3 != NULL)
			effect3->InitPoint(EffectPoint::p100, x, y);
		die = true;
		break;
	}
	}
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + PLANT_WIDTH;
	b = y + PLANT_HEIGHT;
}

