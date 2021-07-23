#include "Card.h"
#include <cstdlib>
#include <ctime>
#include "Camera.h"
#include "Game.h"

Card::Card()
{
	card = CardType::num_card;
	active = false;
	textCard = false;
	SetAnimation(CARD_ANI_ID);
	courseClear = new TextString();
	courseClear->SetContent("course clear");
	gotCard = new TextString();
	gotCard->SetContent("you got a card");
}

CardType Card::RandomCard() {
	active = true;
	// random 0-2 CardType
	int divisor = static_cast<int>(CardType::num_card);
	srand((unsigned int)time(NULL));
	card = static_cast<CardType>(rand() % divisor);
	return card;
}

void Card::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (active)
	{
		if (textCard == false)
		{
			CCamera* cam = CGame::GetInstance()->GetCam();
			textCard = true;
			courseClear->SetPosition(0, cam->y + CARD_COURSE_CLEAR_Y);
			gotCard->SetPosition(0, cam->y + CARD_GOT_CARD_Y);
			TextCard* cardHud = new TextCard();
			cardHud->SetContent(GetCardName());
			cardHud->blink = true;
			CGame::GetInstance()->GetCurrentScene()->GetHUD()->cards.push_back(cardHud);
			CGame::GetInstance()->GetCurrentScene()->isFinished = true;
		}
		vy = -CARD_ACTIVE_SPEED_VY;
		y += dy;
	}
}

string Card::GetCardName()
{
	string cardName;
	if (card == CardType::mushroom)
	{
		cardName = "mushroom";
	}
	else if (card == CardType::star)
	{
		cardName = "star";
	}
	else if (card == CardType::white_flower) {
		cardName = "whiteflower";
	}
	return cardName;
}

void Card::Render()
{
	int ani = CARD_ANI_DEFAULT;
	if (active)
	{
		if (card == CardType::mushroom)
		{
			ani = CARD_ANI_MUSHROOM;
		}
		else if (card == CardType::star)
		{
			ani = CARD_ANI_STAR;
		}
		else if (card == CardType::white_flower) {
			ani = CARD_ANI_WHITE_FLOWER;
		}
		courseClear->Render();
		gotCard->RenderCard(GetCardName());
	}
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void Card::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX_WIDTH;
	b = y + CARD_BBOX_HEIGHT;
}