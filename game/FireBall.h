#pragma once
#include "GameObject.h"
#include "Plant.h"
#include "Mario.h"

#define FIREBALL_WIDTH 9
#define FIREBALL_HEIGHT 9
#define FIREBALL_SPEED 0.06f
#define FIREBALL_ANI_ID 62
#define FIREBALL_CHECK_POS_SHOOT_X 72
#define FIREBALL_CHECK_X 150
#define FIREBALL_CHECK_Y 120
#define FIREBALL_VELOCITY_X 0.1f
#define FIREBALL_GRAVITY 0.0007f
#define FIREBALL_DEFLECT_Y 0.15f

class CFireBall : public CGameObject
{
	friend class FireBallPool;
	bool isForPlant;
	int framesLeft_;

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
	CFireBall();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CFireBall* GetNext() const { return state_.next; }
	void SetNext(CFireBall* next) { state_.next = next; }

	void Init(CMario* mario, CPlant* plant);
	void Init(CMario* mario);

	/*bool InUse() const { return !die; }*/

	bool InUse() { return !die; }

	bool Animate()
	{
		return !die;
		//if (!InUse()) return false;

		///*framesLeft_--;
		//x_ += xVel_;
		//y_ += yVel_;*/

		////return framesLeft_ == 0;
		//return true;
	}
};
