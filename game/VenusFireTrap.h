#pragma once
#include "Plant.h"

#define VENUS_ANI_DOWN 0
#define VENUS_ANI_UP 1
#define VENUS_ANI_SHOOT_DOWN 2
#define VENUS_ANI_SHOOT_UP 3
#define VENUS_SHOOT_TIME 2000
#define VENUS_RED_TYPE 0
#define VENUS_GREEN_TYPE 1

class VenusFireTrap : public CPlant
{
	friend class FireBallPool;

	ULONGLONG shootTimeStart = 0;
	FireBallPool* pool;
	bool shootingTime = false;

	void FindPositionForShooting();
	void SetDirectionShootingFollowMario();
public:
	bool isUp = false;
	bool createFireball = false;
	int type;

	VenusFireTrap(float y, int type);
	void StartShootTime();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

