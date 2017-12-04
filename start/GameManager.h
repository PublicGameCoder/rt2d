#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <rt2d/core.h>
#include <rt2d/input.h>
#include <rt2d/singleton.h>

#include "GameScene.h"

#include "LevelLoader.h"


class GameManager {
public:

	GameManager();

	virtual ~GameManager();

	void start();

private:
	Input* input;
};

#endif // !GAMEMANAGER_H
