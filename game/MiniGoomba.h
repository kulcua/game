#pragma once
#include "GameObject.h"

#define MINI_GOOMBA_SPEED_VX 0.3f
#define MINI_GOOMBA_SPEED_VY 0.05f
#define MINI_GOOMBA_BBOX_SIZE 20
#define MINI_GOOMBA_ANI_ID 33
#define MINI_GOOMBA_TIME_FLIP 1000
#define MINI_GOOMBA_TIME_DIE 5500

class MiniGoomba : public CGameObject
{
	friend class MiniGoombaPool;
	MiniGoomba* next;
	int animateTimeStart;
	int timeToDie;
	int timeFlip;
public:
	MiniGoomba();
	bool inUse;
	void Init(float x, float y);
	void StartAnimate();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	MiniGoomba* GetNext() const { return next; }
	void SetNext(MiniGoomba* next) { this->next = next; }
	bool GetBackToPool();
};
