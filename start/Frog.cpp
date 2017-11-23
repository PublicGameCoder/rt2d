#include "Frog.h"

Frog::Frog() : Entity()
{
	this->addSprite("assets/frog.tga");
	this->sprite()->color = GREEN;
	this->scale = Point3(0.8,0.8,0);
	//std::cout << "FrogSprite added" << std::endl;
}

Frog::~Frog()
{

}

void Frog::update(float deltaTime)
{

}