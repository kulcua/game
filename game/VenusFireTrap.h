#pragma once
#include "Plant.h"

#define VENUS_ANI_DOWN 0
#define VENUS_ANI_UP 1
#define VENUS_ANI_SHOOT_DOWN 2
#define VENUS_ANI_SHOOT_UP 3

#define VENUS_WIDTH 50
#define VENUS_RED_HEIGHT 94
#define VENUS_GREEN_HEIGHT 73

#define VENUS_SHOOT_TIME 2000

#define VENUS_RED_TYPE 0
#define VENUS_GREEN_TYPE 1

class VenusFireTrap : public CPlant
{
	friend class FireBallPool;

	DWORD shootTimeStart;
	FireBallPool* pool;
	bool shootingTime;

	void FindPositionForShooting();
	void SetDirectionShootingFollowMario();
public:
	bool isUp;
	bool createFireball;
	int type;

	VenusFireTrap(float y, int type);
	void StartShootTime();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

