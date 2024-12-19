#include "Airplane.h"

bool Airplane::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q)
	{
		leftWingNode->rotate(Vector3(0, 0, 1), Degree(5));
		rightWingNode->rotate(Vector3(0, 0, 1), Degree(-5));
	}
	else if (evt.keysym.sym == SDLK_w)
	{
		leftWingNode->rotate(Vector3(0, 0, 1), Degree(-5));
		rightWingNode->rotate(Vector3(0, 0, 1), Degree(5));
	}

	return IG2Object::keyPressed(evt);
}
