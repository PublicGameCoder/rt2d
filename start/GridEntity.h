/**
 * @file D:\Projecten\Project_RT2D\Game_Emulator\rt2d\start\GridEntity.h.
 *
 * Declares the grid entity class.
 */

#ifndef GRIDENTITY_H
#define GRIDENTITY_H

#include <rt2d/entity.h>

/**
 * The MyScene class is the Scene implementation.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class GridEntity : public Entity
{
public:

	/**
	 * Constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	GridEntity();

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~GridEntity();

	/**
	 * update is automatically called every frame.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param deltaTime the elapsed time in seconds.
	 */

	virtual void update(float deltaTime);

};

#endif // !GRIDENTITY_H
