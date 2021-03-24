#pragma once
#include "GameObject.h"
#include "Plant.h"
#include "Mario.h"

#define FIREBALL_WIDTH 25
#define FIREBALL_HEIGHT 25
#define FIREBALL_SPEED 0.1f
#define FIREBALL_ANI_ID 62
#define FIREBALL_CHECK_POS_SHOOT_X 72
#define FIREBALL_CHECK_X 150
#define FIREBALL_CHECK_Y 120
#define FIREBALL_VELOCITY_X 0.35f
#define FIREBALL_GRAVITY 0.0015f
#define FIREBALL_DEFLECT_Y 0.3f

class CFireBall : public CGameObject
{
	friend class FireBallPool;
	bool isForPlant;
	
	union
	{
		// State when it's in use.
		struct
		{
			CMario* mario;
			CPlant* plant;
		} live;

		// State when it's available.
		CFireBall* next;
	} state_;

	void SetAnimationFireBall();
public:
	bool inUse;
	CFireBall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CFireBall* GetNext() const { return state_.next; }
	void SetNext(CFireBall* next) { state_.next = next; }

	void Init(CMario* mario, CPlant* plant);
	void Init(CMario* mario);

	bool Animate() { 
		if (!inUse) return false;		
		else if (die)
		{
			inUse = false;
			return true;
		}
		return false;
	}
};
