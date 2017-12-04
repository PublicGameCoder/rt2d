/**
 * @file D:\Projecten\Project_RT2D\Game_Emulator\rt2d\start\GameManager.h.
 *
 * Declares the game manager class.
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <rt2d/core.h>
#include <rt2d/input.h>
#include <rt2d/singleton.h>

#include "GameScene.h"

#include "LevelLoader.h"

/**
 * Manager for games.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class GameManager {
public:

	/**
	 * Default constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	GameManager();

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~GameManager();

	/**
	 * Starts this object.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void start();

private:
	/** The input. */
	Input* input;
};

#endif // !GAMEMANAGER_H
