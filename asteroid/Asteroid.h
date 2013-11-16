#pragma once
#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Physics.h"

class Asteroid : public Physics{
public:
	int id;
	static int astNum;
	XMFLOAT2 scale;
	XMFLOAT2 size;
	bool destroyed;

	float radius;
	Asteroid();

	void seedRan();
};

#endif