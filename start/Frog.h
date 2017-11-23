#ifndef FROG_H
#define FROG_H

#include <rt2d/entity.h>

/// @brief The MyScene class is the Scene implementation.
class Frog : public Entity
{
public:
	/// @brief Constructor
	Frog();
	/// @brief Destructor
	virtual ~Frog();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void setGridPos(Point2 newGridPos) {
		gridPos = newGridPos;
	}

	Point2 getGridPos() { return gridPos; }

private:
	Point2 gridPos = Point2(0,0);
};

#endif /* FROG_H */