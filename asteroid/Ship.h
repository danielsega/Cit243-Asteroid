#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

#include "Physics.h"

class Ship : public Physics{
private:
	float rot;
public:
	float radius;
	XMFLOAT2 size;
	
	Ship();

	float &rotateRight();

	float &rotateLeft();

	float &getRot();
};

#endif