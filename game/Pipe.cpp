#include "Pipe.h"
#include "Sprites.h"

CPipe::CPipe(float x, float y, int spriteId)
{
	this->x = x;
	this->y = y;
	this->spriteId = spriteId;
}

void CPipe::Render()
{
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y, NULL);
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIPE_WIDTH;
	b = y + PIPE_HEIGHT;
}
