#include "Text.h"
#include "FontManager.h"
#include <string.h>
#include "Camera.h"
#include "Game.h"

void Text::Render()
{
	float xPostition;
	for (int i = 0; i < length; i++)
	{
		int character = characterRender % 10;
		xPostition = x + TEXT_WIDTH * (length - i - 1);
		FontManager::GetInstance()->Render(to_string(character), xPostition, y);
		characterRender = characterRender / 10;
	}
}

void Text::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TEXT_WIDTH;
	b = y + TEXT_WIDTH;
}

void TextPowerSign::Render()
{
	float xPostition;
	for (int i = 0; i < length; i++)
	{
		xPostition = x + TEXT_WIDTH * i;
		if (i == length - 1)
		{
			if (power == length)
				FontManager::GetInstance()->Render("powerWhite", xPostition, y);
			else
				FontManager::GetInstance()->Render("powerBlack", xPostition, y);
		}
		else if (i < power)
		{
			FontManager::GetInstance()->Render("arrowWhite", xPostition, y);
		}
		else if (i < length - 1)
		{
			FontManager::GetInstance()->Render("arrowBlack", xPostition, y);
		}
	}
}

void TextString::SetContent(string content)
{
	this->content = content;
}

void TextString::Render()
{
	CCamera* cam = CGame::GetInstance()->GetCam();
	float xCenter = cam->x + CAM_WIDTH /2 - (content.size() * TEXT_WIDTH)/2;
	for (int i = 0; i < content.size(); i++) {
		float xPostition = xCenter + TEXT_WIDTH * i;
		string c(1, content[i]);
		FontManager::GetInstance()->Render(c, xPostition, y);
	}
}

void TextString::RenderCard(string cardName)
{
	int length = (content.size() + 2) * TEXT_WIDTH;
	CCamera* cam = CGame::GetInstance()->GetCam();
	float xCenter = (cam->x + CAM_WIDTH / 2) - length / 2;
	for (int i = 0; i < content.size(); i++) {
		float xPostition = xCenter + TEXT_WIDTH * i;
		string c(1, content[i]);
		FontManager::GetInstance()->Render(c, xPostition, y);
	}
	float xPostition = xCenter + length;
	float yCard = y - 20;
	FontManager::GetInstance()->Render(cardName, xPostition, yCard);
}

TextCard::TextCard()
{
	SetAnimation(TEXT_CARD_ANI_ID);
}

void TextCard::Render()
{
	int ani = 0;
	if (blink)
	{
		if (content == "mushroom")
			ani = TEXT_CARD_ANI_MUSHROOM_BLINK;
		else if (content == "star")
			ani = TEXT_CARD_ANI_STAR_BLINK;
		else ani = TEXT_CARD_ANI_WHITEFLOWER_BLINK;
	}
	else {
		if (content == "mushroom")
			ani = TEXT_CARD_ANI_MUSHROOM;
		else if (content == "star")
			ani = TEXT_CARD_ANI_STAR;
		else ani = TEXT_CARD_ANI_WHITEFLOWER;
	}
	animation_set->at(ani)->Render(x, y, nx, ny, 255);
}