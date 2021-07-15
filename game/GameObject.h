#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Animations.h"
#include "Sprites.h"

using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisonEvent;
typedef CCollisonEvent* LPCOLLISIONEVENT;
struct CCollisonEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	float dx, dy;

	// *RELATIVE* movement distance between this object and obj
	CCollisonEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny; 
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
protected:
	friend class Grid;
	Grid* grid_;
public:
	float oldX, oldY;

	float x = 0;
	float y = 0;

	float dx;
	float dy;

	float vx;
	float vy;

	int nx = -1;
	int ny = -1;

	int state;

	DWORD dt;

	int width;
	int height;

	LPANIMATION_SET animation_set;
	void SetAnimation(int ani);
public:
	CGameObject();
	void SetGrid(Grid* grid, int id);
	bool die = false;
	bool isOnGround;
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	bool AABB(CGameObject *obj);
	
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvent);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvent,
		vector<LPCOLLISIONEVENT>& coEventResult,
		float &nx,
		float &ny);

	//CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects) {};

	~CGameObject();
};

