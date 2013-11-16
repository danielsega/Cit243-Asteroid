#pragma once
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "Physics.h"

class Missile : public Physics{
public:

	bool fired;
	Missile();
};

#endif