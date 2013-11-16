#include "Asteroid.h"

Asteroid::Asteroid(){
	seedRan();
	position.x = (rand() % SCREEN_WIDTH);
	position.y = rand() % SCREEN_HEIGHT;


	scale.x = ((double) rand() / (RAND_MAX));

	//--Makes scale at least bigger than 0.3
	while (scale.x < 0.3){
		scale.x = ((double) rand() / (RAND_MAX));
	}
	scale.y = scale.x;

	velocity.x = (rand() % 10) * .01;
	velocity.y = (rand() % 10) * .01;

	destroyed = false;
	astNum++;
	id = astNum;
}

void Asteroid::seedRan(){
	return srand(rand());
}