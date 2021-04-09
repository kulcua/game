#pragma once
#include "Utils.h"
#define TEXT_WIDTH 24

class Text
{
	float x, y;
	int content;
	int numberOfText;
public:
	Text(int numberOfText) { this->numberOfText = numberOfText; };
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	void SetContent(int content) { this->content = content; }
	void Render();
};

