#include "Effect.h"
#include "Utils.h"
#include "Mario.h"

Effect::Effect()
{
	SetAnimation();
	die = true;
	mario = CMario::GetInstance();
}

void Effect::Init(EffectName name, float x, float y)
{
	SetName(name);
	die = false;
	inUse = true;
	SetPosition(x, y);
}

void Effect::InitPoint(EffectPoint ePoint, float x, float y)
{
	Effect::Init(EffectName::point, x, y);
	this->ePoint = ePoint;
	int point = 0;
	if (ePoint == EffectPoint::p100)
		point = 100;
	else if (ePoint == EffectPoint::p200)
		point = 200;
	else if (ePoint == EffectPoint::p1000)
		point = 1000;
	mario->SetPoint(point);
}

void Effect::InitDebris(int pos, float x, float y)
{
	Effect::Init(EffectName::debrisBrick, x, y);
	if (pos == 1 || pos == 2)
		vy = -EFFECT_DEBRIS_DELFECT_VY_12;
	else vy = -EFFECT_DEBRIS_DELFECT_VY_34;

	if (pos == 1 || pos == 3)
		vx = -EFFECT_DEBRIS_VX;
	else vx = EFFECT_DEBRIS_VX;
}

void Effect::SetAnimation()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(EFFECT_ANI_ID);
	SetAnimationSet(ani_set);
}


void Effect::StartAnimate()
{
	if (animateTimeStart == 0)
		animateTimeStart = GetTickCount64();
}

bool Effect::GetBackToPool()
{
	if (!inUse) return false;
	else if (die)
	{
		inUse = false;
		animateTimeStart = 0;
		return true;
	}
	return false;
}


void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	StartAnimate();
	if (animateTimeStart > 0 && GetTickCount64() - animateTimeStart > EFFECT_ANIMATE_TIME)
	{
		die = true;
	}

	if (name == EffectName::debrisBrick)
	{
		vy += EFFECT_DEBRIS_GRAVITY * dt;

		x += dx;
		y += dy;
	}

	if (name == EffectName::point)
	{
		vy = -EFFECT_POIINT_DELFECT_VY;
		y += dy;
	}
}

void Effect::Render()
{
	int ani = 0;
	if (name == EffectName::fireballDestroy)
		ani = EFFECT_ANI_FIREBALL_DESTROYED;
	else if (name == EffectName::marioTailAttack)
		ani = EFFECT_ANI_MARIO_TAIL_ATTACK;
	else if (name == EffectName::debrisBrick)
		ani = EFFECT_ANI_DEBRIS_BRICK;
	else if (name == EffectName::point)
	{
		if (ePoint == EffectPoint::p100)
			ani = EFFECT_ANI_POINT_100;
		else if (ePoint == EffectPoint::p200)
			ani = EFFECT_ANI_POINT_200;
		else if (ePoint == EffectPoint::p1000)
			ani = EFFECT_ANI_POINT_1000;
	}
	animation_set->at(ani)->Render(x, y, NULL);
}

void Effect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 0;
	b = y + 0;
}