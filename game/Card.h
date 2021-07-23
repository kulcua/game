#pragma once
#include "GameObject.h"
#include "Text.h"
#define CARD_ANI_ID	55
#define CARD_ANI_DEFAULT 0
#define CARD_ANI_MUSHROOM 1
#define CARD_ANI_STAR 2
#define CARD_ANI_WHITE_FLOWER 3
#define CARD_BBOX_WIDTH 50
#define CARD_BBOX_HEIGHT 50
#define CARD_ACTIVE_SPEED_VY 0.3f
#define CARD_COURSE_CLEAR_Y 50
#define CARD_GOT_CARD_Y 130

enum class CardType {
	mushroom,
	star,
	white_flower,
	num_card
};

class Card : public CGameObject
{
	bool active;
	bool textCard;
	CardType card;
	TextString* courseClear;
	TextString* gotCard;
public:
	Card();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	CardType RandomCard();
	string GetCardName();
};

