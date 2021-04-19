#include "Effect.h"

Effect::Effect()
{
	SetAnimation();
	die = true;
}

void Effect::Init(EffectName name, float x, float y)
{
	SetName(name);
	die = false;
	inUse = true;
	SetPosition(x, y);
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
	StartAnimate();
	if (animateTimeStart > 0 && GetTickCount64() - animateTimeStart > EFFECT_ANIMATE_TIME)
	{
		die = true;
	}
}

void Effect::Render()
{
	int ani = 0;
	if (name == EffectName::fireballDestroy)
		ani = EFFECT_ANI_FIREBALL_DESTROYED;
	else if (name == EffectName::marioTailAttack)
		ani = EFFECT_ANI_MARIO_TAIL_ATTACK;
	animation_set->at(ani)->Render(x, y, NULL);
}

void Effect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + EFFECT_WIDTH;
	b = y + EFFECT_HEIGHT;
}