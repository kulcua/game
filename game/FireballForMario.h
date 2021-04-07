#pragma once
#include "FireBall.h"
#include "Mario.h"
class FireballForMario : public CFireBall
{
};

class CFireBall : public CGameObject
{
	friend class FireBallPool;
	bool isForPlant;

	bool isDestroyed;
	DWORD destroyTimeStart;

	void StartDestroy() { isDestroyed = true; destroyTimeStart = GetTickCount64(); }

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
	void UpdateForMario(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateForPlant(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CFireBall* GetNext() const { return state_.next; }
	void SetNext(CFireBall* next) { state_.next = next; }

	void InitForPlant(CPlant* plant);
	void InitForMario();

	bool GetBackToPool();
};
