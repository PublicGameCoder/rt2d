#include "GameManager.h"

GameManager::GameManager()
{
	input = Singleton<Input>::instance();
}

GameManager::~GameManager()
{

}

void GameManager::start() {

	LevelLoader* levelLoader = new LevelLoader();

	std::vector<GameScene*> scenes;
	cout << "Loading levels." << endl;
	vector<vector<vector<char>>> levels = levelLoader->getLevels();
	for (int i = 0; i < levels.size(); i++) {
		std::vector<std::vector<char>> level = levels[i];
		GameScene* levelScene = new GameScene(level);
		scenes.push_back(levelScene);
	}
	if (scenes.size() <= 0) {
		cout << "No levels have been loaded!" << endl;
		return;
	}else {
		cout << scenes.size() << " level(s) have been loaded!" << endl;
	}
	// Core instance
	Core core;

	// Scene01
	short int levelIndex = 0;
	GameScene* gameScene = scenes[levelIndex];
	while (true) {
		if (gameScene == NULL) {
			break;
		}
		if (input->getKeyDown(KeyCode::Space)) {
			delete gameScene;
			std::vector<std::vector<char>> resettedlevel = levelLoader->getLevels()[levelIndex];
			scenes[levelIndex] = new GameScene(resettedlevel);
			gameScene = scenes[levelIndex];
		}
		if (gameScene->isFinished()) {
			levelIndex++;
			if (levelIndex < scenes.size()) {
				gameScene = scenes[levelIndex];
			} else {
				cout << "Finished!" << endl;
				break;
			}
		}
		if (!gameScene->isRunning()) {
			break;
		}
		core.run(gameScene);
		core.showFrameRate(5);
	}
	for (int i = 0; i < scenes.size(); i++) {
		delete scenes[i];
	}
	scenes.clear();

}