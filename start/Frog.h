#ifndef FROG_H
#define FROG_H

#include <rt2d/entity.h>

class Frog : public Entity
{
public:

	Frog();

	virtual ~Frog();

	virtual void update(float deltaTime);

	void setGridPos(Point2 newGridPos) {
		gridPos = newGridPos;
	}

	void setPosition(Point3 otherPosition);
	void moveTowards(Point3 otherPosition);

	Point2 getGridPos() { return gridPos; }

	Point2 facing();

	bool isTimedOut();

private:
	Point3 destination;
	Point2 gridPos = Point2(0,0);
	float distance(Point3 pos1, Point3 pos2);
	bool timedOut = false;
	void isTimedOut(bool state) {
		timedOut = state;
	}
};

#endif /* FROG_H */