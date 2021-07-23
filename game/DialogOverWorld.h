#pragma once
#include "GameObject.h"
#include "Text.h"
#define DIALOG_WIDTH 385
#define DIALOG_HEIGHT 110
#define DIALOG_ANI_ID 21
#define DIALOG_ANI_GAMEOVER 0
#define DIALOG_ANI_WORLD 1
#define DIALOG_TIME_TO_CLOSE	2000
#define DIALOG_WORLD_X	270
#define DIALOG_WORLD_Y	40
#define DIALOG_LIFE_X	300
#define DIALOG_LIFE_Y	100

class DialogOverWorld : public CGameObject
{
	Text* world, *life;
	ULONGLONG timeStart;
	static DialogOverWorld* __instance;
public:
	static DialogOverWorld* GetInstance();
	DialogOverWorld();
	void Render();
	void Update();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void StartTime();
	void CheckShowDialog();
};