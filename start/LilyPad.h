#ifndef LILYPAD_H
#define LILYPAD_H

#include <rt2d/entity.h>

/// @brief The MyScene class is the Scene implementation.
class LilyPad : public Entity
{
public:
	/// @brief Constructor
	LilyPad();
	/// @brief Destructor
	virtual ~LilyPad();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	bool isCursorOnObject2d();

	void setGridPos(Point2 newGridPos) {
		gridPos = newGridPos;
	}

	Point2 getGridPos() { return gridPos; }

private:
	Point2 gridPos = Point2(0, 0);
};

#endif /* LILYPAD_H */