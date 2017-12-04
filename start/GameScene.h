/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <rt2d/scene.h>

#include "Frog.h"
#include "LilyPad.h"
#include "GridEntity.h"

/**
 * A cell.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

struct Cell
{
	/** The entity. */
	GridEntity* entity;
	/** The lily pad. */
	LilyPad* lilyPad;
	/** The position. */
	Point2 position;
};

/**
 * The MyScene class is the Scene implementation.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class GameScene : public Scene
{
public:

	/**
	 * Constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param selectedgrid The selectedgrid.
	 */

	GameScene(std::vector<std::vector<char>> selectedgrid);

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~GameScene();

	/**
	 * Handles the movement.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void handleMovement();

	/**
	 * Gets clicked lily pad.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return Null if it fails, else the clicked lily pad.
	 */

	LilyPad* getClickedLilyPad();

	/**
	 * Query if this object is finished.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return True if finished, false if not.
	 */

	bool isFinished();

	/**
	 * Removes the lily pad described by parameter1.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param [in,out] parameter1 If non-null, the first parameter.
	 */

	void removeLilyPad(LilyPad*);

	/**
	 * Removes the frog.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void removeFrog();

	/**
	 * Resets the level.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void resetLevel();

	/**
	 * update is automatically called every frame.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param deltaTime the elapsed time in seconds.
	 *
	 * ### return void.
	 */

	virtual void update(float deltaTime);

private:
	/** The background color. */
	RGBAColor* bgColor;
	/** The grid. */
	GridEntity* grid;
	/** The player frog. */
	Frog* playerFrog;
	/** The lilypads. */
	std::vector<LilyPad*> lilypads;
	/** The cells. */
	std::vector<Cell*> cells;

	/**
	 * Gets lily pad by exact position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param exactPos The exact position.
	 *
	 * @return Null if it fails, else the lily pad by exact position.
	 */

	LilyPad* getLilyPadByExactPos(Point2 exactPos);

	/**
	 * Gets lily pad by grid position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param gridPos The grid position.
	 *
	 * @return Null if it fails, else the lily pad by grid position.
	 */

	LilyPad* getLilyPadByGridPos(Point2 gridPos);

	/**
	 * Gets cell by grid position.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param gridPos The grid position.
	 *
	 * @return Null if it fails, else the cell by grid position.
	 */

	Cell* getCellByGridPos(Point2 gridPos);

	/** The gridwidth. */
	int gridwidth;
	/** The gridheight. */
	int gridheight;
	/** The cellwidth. */
	int cellwidth;
	/** The cellheight. */
	int cellheight;
	/** The border. */
	int border;
protected:
	/** The numbergrid. */
	std::vector<std::vector<char>> numbergrid {
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 0, 2, 0 },
	};

	/**
	 * Creates the grid.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void createGrid();
};

#endif /* GAMESCENE_H */
