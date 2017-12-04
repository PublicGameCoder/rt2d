/**
 * @file D:\Projecten\Project_RT2D\Game_Emulator\rt2d\start\Frog.h.
 *
 * Declares the frog class.
 */

#ifndef FROG_H
#define FROG_H

#include <rt2d/entity.h>

/**
 * A frog.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class Frog : public Entity
{
public:

	/**
	 * Default constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	Frog();

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~Frog();

	/**
	 * Updates the given deltaTime.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param deltaTime The delta time.
	 */

	virtual void update(float deltaTime);

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
	 * Sets a position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param otherPosition The other position.
	 */

	void setPosition(Point3 otherPosition);

	/**
	 * Move towards.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param otherPosition The other position.
	 */

	void moveTowards(Point3 otherPosition);

	/**
	 * Gets grid position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return The grid position.
	 */

	Point2 getGridPos() { return gridPos; }

	/**
	 * Gets the facing.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return A Point2.
	 */

	Point2 facing();

	/**
	 * Query if this object is timed out.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return True if timed out, false if not.
	 */

	bool isTimedOut();

private:
	/** Destination for the. */
	Point3 destination;
	/** The grid position. */
	Point2 gridPos = Point2(0,0);

	/**
	 * Distances.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param pos1 The first position.
	 * @param pos2 The second position.
	 *
	 * @return A float.
	 */

	float distance(Point3 pos1, Point3 pos2);
	/** True to timed out. */
	bool timedOut = false;

	/**
	 * Is timed out.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param state True to state.
	 */

	void isTimedOut(bool state) {
		timedOut = state;
	}
};

#endif /* FROG_H */