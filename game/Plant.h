#pragma once
#include "GameObject.h"
#include "Utils.h"

#define PLANT_STATE_DISABLE 100
#define PLANT_STATE_ENABLE 200

#define PLANT_ANI_DOWN 0
#define PLANT_ANI_UP 1
#define PLANT_ANI_SHOOT_DOWN 2
#define PLANT_ANI_SHOOT_UP 3

#define PLANT_WIDTH 16
#define PLANT_HEIGHT 31
#define PLANT_SPEED 0.02f

#define PLANT_SHOOT_TIME 2000

class CPlant : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();	
	DWORD shoot_time_start;
	CGameObject *player;
	bool shoot;
	
public:
	bool isUp;
	bool fireball; //check ban only 1 vien dan
	CPlant(CGameObject *player);
	void StartShootTime() {
		shoot = true;
		shoot_time_start = GetTickCount();
		fireball = true;
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

