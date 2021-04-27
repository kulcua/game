#pragma once
#include "GameObject.h"
#define EFFECT_WIDTH 30
#define EFFECT_HEIGHT 30
#define EFFECT_ANIMATE_TIME 500
#define EFFECT_ANI_ID	65
#define EFFECT_ANI_FIREBALL_DESTROYED	0
#define EFFECT_ANI_MARIO_TAIL_ATTACK	1
#define EFFECT_ANI_DEBRIS_BRICK		2
#define EFFECT_DEBRIS_DELFECT_VY_12	0.8f
#define EFFECT_DEBRIS_DELFECT_VY_34	0.5f
#define EFFECT_DEBRIS_GRAVITY	0.0015f
#define  EFFECT_DEBRIS_VX 0.2f

enum class EffectName {
	fireballDestroy,
	marioTailAttack,
	debrisBrick
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
	void InitDebris(int position, float x, float y);
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

