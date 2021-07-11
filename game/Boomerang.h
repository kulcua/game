#pragma once
#include "GameObject.h"
#define BOOMERANG_BBOX_SIZE 40
#define BOOMERANG_SPEED_VX 0.3f
#define BOOMERANG_SPEED_VY 0.05f
#define BOOMERANG_ANI_ID 47
#define BOOMERANG_TIME_RETURN 1000
#define BOOMERANG_TIME_DIE 2000

class Boomerang : public CGameObject
{
	friend class BoomerangPool;
	Boomerang* next;
	ULONGLONG animateTimeStart;
public:
	Boomerang();
	bool inUse;
	void Init(float x, float y, int nx);
	void StartAnimate();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	Boomerang* GetNext() const { return next; }
	void SetNext(Boomerang* next) { this->next = next; }
	bool GetBackToPool();
};

