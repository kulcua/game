#include "Card.h"
#include <cstdlib>
#include <ctime>

Card::Card()
{
	SetAnimation(CARD_ANI_ID);
}

void Card::GetCard() {
	active = true;
	// random 0-2 CardType
	int divisor = static_cast<int>(CardType::num_card);
	srand(time(NULL));
	card = static_cast<CardType>(rand() % divisor);
}

void Card::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (active)
	{
		vy = -CARD_ACTIVE_SPEED_VY;
		y += dy;
	}
}

void Card::Render()
{
	int ani = CARD_ANI_DEFAULT;
	if (active)
	{
		if (card == CardType::mushroom)
			ani = CARD_ANI_MUSHROOM;
		else if (card == CardType::star)
			ani = CARD_ANI_STAR;
		else if (card == CardType::white_flower)
			ani = CARD_ANI_WHITE_FLOWER;
	}
	animation_set->at(ani)->Render(x, y, nx);
}

void Card::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX_WIDTH;
	b = y + CARD_BBOX_HEIGHT;
}