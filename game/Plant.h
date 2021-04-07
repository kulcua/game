#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"

#define PLANT_ANI_DOWN 0
#define PLANT_ANI_UP 1
#define PLANT_ANI_SHOOT_DOWN 2
#define PLANT_ANI_SHOOT_UP 3

#define PLANT_WIDTH 50
#define PLANT_HEIGHT 94
#define PLANT_SPEED 0.04f

#define PLANT_SHOOT_TIME 2000

class CPlant : public CGameObject
{
	friend class FireBallPool;
	void FindPositionForShooting();
	void SetDirectionShootingFollowMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();	
	DWORD shootTimeStart;
	CMario* mario;
	FireBallPool* pool;
	bool shootingTime;

	float startY;
	
public:
	bool isUp;
	bool createFireball;
	CPlant(float y);
	void StartShootTime() {
		shootingTime = true;
		shootTimeStart = GetTickCount64();
		createFireball = true;
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

