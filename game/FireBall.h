#pragma once
#include "GameObject.h"
#include "VenusFireTrap.h"
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
#define FIREBALL_DESTROYED_TIME 200

class CFireBall : public CGameObject
{
	friend class FireBallPool;
	bool isForPlant;

	DWORD destroyTimeStart;

	void StartDestroy();

	union
	{
		struct
		{
			CMario* mario;
			VenusFireTrap* venus;
		} live;
		CFireBall* next;
	} state_;

	void SetAnimationFireBall();
public:
	bool inUse;
	CFireBall();
	void UpdateForMario(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateForPlant(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CFireBall* GetNext() const { return state_.next; }
	void SetNext(CFireBall* next) { state_.next = next; }

	void InitForPlant(VenusFireTrap* venus);
	void InitForMario();

	bool GetBackToPool();
};
