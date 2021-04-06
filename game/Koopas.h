#pragma once
class CMario;
#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.04f
#define KOOPAS_BALL_SPEED 0.4f
#define KOOPAS_GRAVITY	0.004f

#define KOOPAS_BBOX_WIDTH 50
#define KOOPAS_BBOX_HEIGHT 82
#define KOOPAS_BBOX_HEIGHT_DIE 50

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_BALL 200
#define KOOPAS_STATE_DIE 300

#define KOOPAS_ANI_WALKING 0
#define KOOPAS_ANI_BALL 1
#define KOOPAS_ANI_DIE 2

#define MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT 16
#define MARIO_SMALL_HANDLED_SHELL_HEIGHT 4
#define MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT 24
#define MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT 20
#define MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT 36

class CKoopas: public CGameObject
{
	float start_x, end_x;
	bool isHandled;
	CMario* mario_;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CKoopas(float start_x, float end_x);
	void HandleByMario(CMario* mario);
	void SetPositionHandled();
	void KickByMario(CMario* mario);
	virtual void SetState(int state);
};

