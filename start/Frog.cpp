#include "Frog.h"

Frog::Frog() : Entity()
{
	this->addSprite("assets/frog.tga");
	this->sprite()->color = GREEN;
	this->scale = Point3(0.8,0.8,0);
	this->destination = this->position;
	this->sprite()->size = Point2(96, 96);
	//std::cout << "FrogSprite added" << std::endl;
}

Frog::~Frog()
{

}

float _delta = 0;
void Frog::update(float deltaTime)
{
	_delta = deltaTime;
	moveTowards(destination);
}

void Frog::moveTowards(Point3 otherPosition) {
	destination = otherPosition;
	if (this->position != otherPosition) {
		this->isTimedOut(true);
		Point3 dir = otherPosition - this->position;
		float x = dir.x;
		float y = dir.y;
		float z = dir.z;
		float m = sqrt((x*x) + (y*y) + (z*z));
		dir.x /= m;
		dir.y /= m;
		dir.z /= m;
		float speed = 400;
		if (distance(this->position, this->destination) > distance(this->position, this->position+((dir * speed)*_delta) )) {
			this->position += (dir * speed)*_delta;
		}else {
			this->setPosition(destination);
		}
	}
	else if (this->isTimedOut()) {
		this->isTimedOut(false);
	}
}

float Frog::distance(Point3 pos1, Point3 pos2) {
	float distX = pos2.x - pos1.x;
	float distY = pos2.y - pos1.y;
	float distZ = pos2.z - pos1.z;
	return sqrt((distX*distX) + (distY*distY) + (distZ*distZ));
}

void Frog::setPosition(Point3 newposition) {
	this->position = newposition;
	destination = newposition;
}

Point2 Frog::facing() {
	int xface = 0;
	int yface = 0;

	int rot = rotation.z * RAD_TO_DEG;

	if (rot == 90) {
		xface = 1;
		yface = 0;
	}
	else if (rot == 180) {
		xface = 0;
		yface = 1;
	}
	else if (rot == -90) {
		xface = -1;
		yface = 0;
	}
	else {
		xface = 0;
		yface = -1;
	}

	return Point2(xface, yface);
}

bool Frog::isTimedOut() {
	return this->timedOut;
}