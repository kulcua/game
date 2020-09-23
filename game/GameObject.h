#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Animations.h"
#include "Sprites.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

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
public:
	float x;
	float y;

	float dx;
	float dy;

	float vx;
	float vy;

	int nx;
	int state;

	DWORD dt;

	DWORD die_time_start;

	LPANIMATION_SET animation_set;

public:
	bool die;
	void StartDieTime() { die = true; die_time_start = GetTickCount(); }

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->y = y; }
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
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny,
		float &rdx,
		float &rdy);

	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	~CGameObject();
};

