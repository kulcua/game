#include "Text.h"
#include "FontManager.h"
#include <string.h>

void Text::Render()
{
	float xPostition;
	for (int i = 0; i < numberOfText; i++)
	{
		int character = characterRender % 10;
		xPostition = x + TEXT_WIDTH * (numberOfText - i - 1);
		FontManager::GetInstance()->Render(to_string(character), xPostition, y);
		characterRender = characterRender / 10;
	}
}

void TextPowerSign::Render()
{
	float xPostition;
	for (int i = 0; i < numberOfText; i++)
	{
		xPostition = x + TEXT_WIDTH * i;
		if (i == numberOfText - 1)
		{
			if (power == numberOfText)
				FontManager::GetInstance()->Render("powerWhite", xPostition, y);
			else
				FontManager::GetInstance()->Render("powerBlack", xPostition, y);
		}
		else if (i < power)
		{
			FontManager::GetInstance()->Render("arrowWhite", xPostition, y);
		}
		else if (i < numberOfText - 1)
		{
			FontManager::GetInstance()->Render("arrowBlack", xPostition, y);
		}
	}
}