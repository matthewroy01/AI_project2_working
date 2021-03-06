#include "UIManager.h"

#include "Game.h"
#include "GraphicsSystem.h"
#include "InputManager.h"
#include "UnitManager.h"

#include <string.h>

UIManager::UIManager()
{
	Init();
}

UIManager::~UIManager()
{
	// delete the font
	al_destroy_font(mpFont);
	mpFont = NULL;
}

bool UIManager::Init()
{
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	// install font
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
		return false;
	}

	return true;
}

void UIManager::doUI()
{
	std::string tmpStr;

	// mouse position
	int tmpX, tmpY;
	tmpX = GET_GAME->getInputManager()->getInputMousePos().getX();
	tmpY = GET_GAME->getInputManager()->getInputMousePos().getY();
	tmpStr = std::to_string(tmpX) + ":" + std::to_string(tmpY);

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), tmpX, tmpY, ALLEGRO_ALIGN_CENTRE, tmpStr.c_str());

	if (mShouldDisplayInfo)
	{
		// modes
		tmpStr = (std::string)"Mode: " + std::to_string(GET_GAME->getUnitManager()->GetCurrentMode()) + " : " +
			(std::string)"Vel " + std::to_string((int)GET_GAME->getUnitManager()->getAllVelocity()) + " : " +
			(std::string)"Rad " + std::to_string((int)GET_GAME->getUnitManager()->getAllRadius()) + " : " +
			(std::string)"Ang " + std::to_string(GET_GAME->getUnitManager()->getAllAngular());
		al_draw_text(mpFont, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, tmpStr.c_str());
	}
}