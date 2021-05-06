#pragma once
#include "GameObject.h"
#define CARD_ANI_ID	55
#define CARD_ANI_DEFAULT 0
#define CARD_ANI_MUSHROOM 1
#define CARD_ANI_STAR 2
#define CARD_ANI_WHITE_FLOWER 3
#define CARD_BBOX_WIDTH 50
#define CARD_BBOX_HEIGHT 50
#define CARD_ACTIVE_SPEED_VY 0.3f

enum class CardType {
	mushroom,
	star,
	white_flower,
	num_card
};

class Card : public CGameObject
{
	void SetAnimation(int ani);
	bool active;
	CardType card;
public:
	Card();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void GetCard();
};

