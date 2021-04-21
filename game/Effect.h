#pragma once
#include "GameObject.h"
#define EFFECT_WIDTH 30
#define EFFECT_HEIGHT 30
#define EFFECT_ANIMATE_TIME 200
#define EFFECT_ANI_ID	65
#define EFFECT_ANI_FIREBALL_DESTROYED	0
#define EFFECT_ANI_MARIO_TAIL_ATTACK	1

enum class EffectName {
	fireballDestroy,
	marioTailAttack,
	brickDestroy
};

class Effect : public CGameObject
{
	friend class EffectPool;
	EffectName name;
	Effect* next;
	int animateTimeStart;
public:
	Effect();
	bool inUse;
	void Init(EffectName name, float x, float y);
	void SetAnimation();
	void SetName(EffectName name) { this->name = name; }
	void StartAnimate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	Effect* GetNext() const { return next; }
	void SetNext(Effect* next) { this->next = next; }
	bool GetBackToPool();
};

