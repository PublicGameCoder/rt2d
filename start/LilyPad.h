/**
 * @file D:\Projecten\Project_RT2D\Game_Emulator\rt2d\start\LilyPad.h.
 *
 * Declares the lily pad class.
 */

#ifndef LILYPAD_H
#define LILYPAD_H

#include <rt2d/entity.h>

/**
 * The MyScene class is the Scene implementation.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class LilyPad : public Entity
{
public:

	/**
	 * Constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	LilyPad();

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~LilyPad();

	/**
	 * update is automatically called every frame.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param deltaTime the elapsed time in seconds.
	 */

	virtual void update(float deltaTime);

	/**
	 * Query if this object is cursor on object 2D.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return True if cursor on object 2d, false if not.
	 */

	bool isCursorOnObject2d();

	/**
	 * Sets grid position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param newGridPos The new grid position.
	 */

	void setGridPos(Point2 newGridPos) {
		gridPos = newGridPos;
	}

	/**
	 * Gets grid position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return The grid position.
	 */

	Point2 getGridPos() { return gridPos; }

private:
	/** The grid position. */
	Point2 gridPos = Point2(0, 0);
};

#endif /* LILYPAD_H */