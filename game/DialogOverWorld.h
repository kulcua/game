#pragma once
#include "GameObject.h"
#define DIALOG_WIDTH 385
#define DIALOG_HEIGHT 110
#define DIALOG_ANI_ID 21
class DialogOverWorld : public CGameObject
{
public:
	DialogOverWorld();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};