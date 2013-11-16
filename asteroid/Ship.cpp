#include "Ship.h"

Ship::Ship(){
		rot = 0;
		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2;

		velocity.x = .2;
		velocity.y = .2;

		radius = 0;
}

float& Ship::rotateLeft(){
	if (rot < 0)
		rot += 360;
	rot-= velocity.x;
	return rot;
}

float& Ship::rotateRight(){
	if (rot > 360)
		rot -= 360;
	rot+= velocity.x;
	return rot;
}

float& Ship::getRot(){
	return rot;
}