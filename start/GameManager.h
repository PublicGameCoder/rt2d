#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <rt2d/core.h>

#include "GameScene.h"
#include "Scoremanager.h"

class GameManager {
public:

	GameManager();

	virtual ~GameManager();

	void start();

	static ScoreManager* getScoreManager() { return GameManager::sm; };
private:
	static ScoreManager* GameManager::sm;
};

#endif // !GAMEMANAGER_H
