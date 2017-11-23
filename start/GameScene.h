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

struct Cell
{
	GridEntity* entity;
	LilyPad* lilyPad;
	Point2 position;
};

/// @brief The MyScene class is the Scene implementation.
class GameScene : public Scene
{
public:
	/// @brief Constructor
	GameScene();
	/// @brief Destructor
	virtual ~GameScene();

	void handleMovement();

	LilyPad* getClickedLilyPad();

	bool isFinished();

	void removeLilyPad(LilyPad*);
	void removeFrog();


	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	RGBAColor* bgColor;
	GridEntity* grid;
	Frog* playerFrog;
	std::vector<LilyPad*> lilypads;
	std::vector<Cell*> cells;

	LilyPad* getLilyPadByExactPos(Point2 exactPos);
	LilyPad* getLilyPadByGridPos(Point2 gridPos);
	Cell* getCellByGridPos(Point2 gridPos);

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;
	int border;
};

#endif /* GAMESCENE_H */
