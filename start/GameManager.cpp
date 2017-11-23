#include "GameManager.h"

ScoreManager* GameManager::sm = new ScoreManager();

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
	sm->savedata();
	delete sm;
}

void GameManager::start() {
	// Core instance
	Core core;

	// Scene01
	GameScene* gameScene = new GameScene();
	while (gameScene->isRunning()) {
		core.run(gameScene);
		core.showFrameRate(5);
	}

	delete gameScene;
}