#include "Text.h"
#include "FontManager.h"
#include <string.h>

void Text::Render()
{
	float xPostition;

	for (int i = 0; i < numberOfText; i++)
	{
		int character = content % 10;
		xPostition = x + TEXT_WIDTH * (numberOfText - i- 1);
		FontManager::GetInstance()->Render(to_string(character), xPostition, y);
		content = content / 10;
	}
}