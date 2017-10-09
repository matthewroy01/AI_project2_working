#ifndef TOGGLEDISPLAYINFOMESSAGE_H
#define TOGGLEDISPLAYINFOMESSAGE_H

#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class ToggleDisplayInfoMessage :public GameMessage
{
public:
	ToggleDisplayInfoMessage();
	~ToggleDisplayInfoMessage();

	void process();

private:
	
};

#endif