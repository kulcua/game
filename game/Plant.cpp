#include "Plant.h"
#include "Ground.h"
#include "PlayScene.h"
#include "EffectPool.h"

CPlant::CPlant(float y) {
	startY = y;
	vy = -PLANT_SPEED;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;

	if (y > startY && vy > 0)
		vy = -vy;
}

void CPlant::SetState(int state)
{
	switch (state)
	{
	case PLANT_STATE_DIE:
	{
		die = true;
		Effect* effect1 = EffectPool::GetInstance()->Create();
		if (effect1 != NULL)
			effect1->Init(EffectName::marioTailAttack, x, y);
		Effect* effect2 = EffectPool::GetInstance()->Create();
		if (effect2 != NULL)
			effect2->Init(EffectName::fireballDestroy, x, y);
		Effect* effect3 = EffectPool::GetInstance()->Create();
		if (effect3 != NULL)
			effect3->InitPoint(EffectPoint::p100, x, y);
	}
		break;
	}
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + PLANT_WIDTH;
	b = y + PLANT_HEIGHT;
}

