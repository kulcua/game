#pragma once
#include "GameObject.h"
#define CARD_ANI_ID	55
#define CARD_BBOX_WIDTH 50
#define CARD_BBOX_HEIGHT 50

class Card : public CGameObject
{
	void SetAnimation(int ani);
public:
	Card();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

