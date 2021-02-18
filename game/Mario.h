#pragma once
#include "GameObject.h"
#include "Utils.h"

class CMario : public CGameObject
{
	friend class MarioState;

	int level;
	int ani;

	int untouchable;
	DWORD untouchable_start;

	DWORD run_start;

	bool kick;
	DWORD kick_start;

	bool level_up;
	DWORD level_up_start;
	
	DWORD spin_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	float a;
public:
	bool isGrounded;
	MarioState* state_;

	void HandleInput(Input input);

	bool isSit;
	bool isDrop;
	bool isDropFly;
	bool isJump;
	bool isRun; //check run o keyboard -> doi van toc run
	bool run; //check run hay prefly

	bool isPreFly;
	bool isFly;

	bool spin;

	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }

	void SetAnimation(int a) { ani = a; }
	int GetAnimation() { return ani; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartRun() {
		if (!run && !isFly) { run = true;	run_start = GetTickCount(); }
	}
	void StartKick() { kick = true; kick_start = GetTickCount(); }
	void StartSpin() { spin = true; spin_start = GetTickCount(); }
	void StartLevelUp() { level_up = true; level_up_start = GetTickCount(); }

	//void CollisionAABB(vector<LPGAMEOBJECT> *coObjects);
	
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

