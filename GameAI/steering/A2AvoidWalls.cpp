#include "A2AvoidWalls.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "GraphicsSystem.h"

A2AvoidWalls::A2AvoidWalls(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* A2AvoidWalls::getSteering()
{
	for (int i = 0; i < GET_GAME->getUnitManager()->getNumberOfWalls(); i++)
	{
		if (getBoxOnBox(GET_GAME->getUnitManager()->GetWall(i)))
		{
			// flee
			std::cout << "avoid wall" << std::endl;
			mLinear = Vector2D(GRAPHICS_SYSTEM->getWidth() / 2, GRAPHICS_SYSTEM->getHeight() / 2) - mpMover->getPosition();

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();

			mpMover->setNewOrientation();
			mAngular = mpMover->getOrientation();

			return this;
		}
	}

	mLinear = Vector2D(0, 0);
	mAngular = 0;
	return this;
}

bool A2AvoidWalls::getBoxOnBox(KinematicUnit* target)
{
	if (
		target->getPosition().getX() < mpMover->getPosition().getX() + mpMover->getWidth() &&
		target->getPosition().getX() + target->getWidth() > mpMover->getPosition().getX() &&
		target->getPosition().getY() < mpMover->getPosition().getY() + mpMover->getHeight() &&
		target->getPosition().getY() + target->getHeight() > mpMover->getPosition().getY())
	{
		return true;
	}
	return false;
}