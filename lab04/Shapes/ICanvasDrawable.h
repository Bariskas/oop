#pragma once
#include "CCanvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() {};
	virtual void Draw(CCanvas& canvas) const = 0;
};