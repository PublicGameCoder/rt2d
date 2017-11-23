/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	bgColor = new RGBAColor(
		(uint8_t)0,
		(uint8_t)0,
		(uint8_t)255
		);

	LilyPad* lilyPad = new LilyPad();

	gridwidth = 3;
	gridheight = 3;

	std::vector<std::vector<int>> numbergrid {
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 0, 2, 0 },
	};

	cellwidth = 128;//lilyPad->getSize().x;
	cellheight = 128;//lilyPad->getSize().y;
	border = 1;

	delete lilyPad;

	grid = new GridEntity();
	int xgridpos = (SWIDTH / 2) - (gridwidth*(cellwidth + border) / 2);
	int ygridpos = (SHEIGHT / 2) - (gridheight*(cellheight + border) / 2);
	grid->position = Point2(xgridpos, ygridpos);

	// create cells
	for (int y = 0; y<gridheight; y++) {
		for (int x = 0; x<gridwidth; x++) {
			int dataStore = numbergrid[y][x];
			if (dataStore == 0) {
				Cell* cell = new Cell();
				cell->position.x = x;
				cell->position.y = y;

				cell->entity = new GridEntity();
				cell->entity->addSprite(AUTOGENWHITE);
				cell->entity->sprite()->color = *bgColor;
				cell->entity->sprite()->size.x = cellwidth;
				cell->entity->sprite()->size.y = cellheight;

				// initial position
				cell->entity->position.x = x*(cellwidth + border);
				cell->entity->position.y = y*(cellheight + border);

				cells.push_back(cell);
				grid->addChild(cell->entity);
			}
			else if (dataStore == 1) {
				Cell* cell = new Cell();
				cell->position.x = x;
				cell->position.y = y;

				cell->lilyPad = new LilyPad();
				cell->lilyPad->setGridPos(Point2(x, y));
				cell->lilyPad->sprite()->size.x = cellwidth;
				cell->lilyPad->sprite()->size.y = cellheight;

				// initial position
				cell->lilyPad->position.x = x*(cellwidth + border);
				cell->lilyPad->position.y = y*(cellheight + border);

				cells.push_back(cell);
				lilypads.push_back(cell->lilyPad);
				grid->addChild(cell->lilyPad);
				//std::cout << ("Lilypad placed! at:" + std::to_string(cell->lilyPad->position.x)+" | "+ std::to_string(cell->lilyPad->position.x) ) << std::endl;
			} else if (dataStore == 2) {
				Cell* cell = new Cell();
				cell->position.x = x;
				cell->position.y = y;

				cell->lilyPad = new LilyPad();
				cell->lilyPad->setGridPos(Point2(x, y));
				cell->lilyPad->sprite()->size.x = cellwidth;
				cell->lilyPad->sprite()->size.y = cellheight;

				// initial position
				cell->lilyPad->position.x = x*(cellwidth + border);
				cell->lilyPad->position.y = y*(cellheight + border);

				cells.push_back(cell);
				lilypads.push_back(cell->lilyPad);
				grid->addChild(cell->lilyPad);

				playerFrog = new Frog();
				playerFrog->setGridPos(Point2(x, y));
				playerFrog->position.x = x*(cellwidth + border);
				playerFrog->position.y = y*(cellwidth + border);
				grid->addChild(playerFrog);
				//std::cout << ("Lilypad placed! at:" + std::to_string(cell->lilyPad->position.x) + " | " + std::to_string(cell->lilyPad->position.x)) << std::endl;
			}
		}
	}

	this->addChild(grid);
}


GameScene::~GameScene()
{
	for (int i = 0; i < lilypads.size(); i++) {
		lilypads[i] = NULL;
	}

	for (int i = 0; i < grid->children().size(); i++) {
		Entity* entity = grid->getChild(i);
		if (!entity)continue;
		grid->removeChild(entity);
		delete entity;
	}

	delete grid;
}

void GameScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	if (input()->getMouseDown(0)) {
		handleMovement();
	}

	if (isFinished()) {
		std::cout << "FINISHED!" << std::endl;
	}
}

bool GameScene::isFinished() {
	int lilypadsLeftOver = 0;
	int s = lilypads.size();
	for (int i = 0; i < s; i++) {
		LilyPad* lily = lilypads[i];
		if (lily) {
			lilypadsLeftOver++;
		}
	}
	if (lilypadsLeftOver <= 1) {
		return true;
	}
	else {
		return false;
	}
}

void GameScene::handleMovement() {
	Point2 gridPosFrog = playerFrog->getGridPos();
	LilyPad* lilyPad = getClickedLilyPad();
	if (!lilyPad) { return; }
	Point2 gridPosLily = lilyPad->getGridPos();

	if (gridPosFrog.x == gridPosLily.x || gridPosFrog.y == gridPosLily.y ) {
		Point3 dir = playerFrog->position - lilyPad->position;
		if (dir.x > 0) {
			playerFrog->rotation.z = (-90 * DEG_TO_RAD);
		}
		if (dir.x < 0) {
			playerFrog->rotation.z = (90 * DEG_TO_RAD);
		}
		if (dir.y > 0) {
			playerFrog->rotation.z = (0 * DEG_TO_RAD);
		}
		if (dir.y < 0) {
			playerFrog->rotation.z = (180 * DEG_TO_RAD);
		}

		Point2 gridPos = playerFrog->getGridPos();
		playerFrog->position = lilyPad->position;
		playerFrog->setGridPos(gridPosLily);
		LilyPad* prevLily = getLilyPadByGridPos(gridPos);
		if (!prevLily) {
			//std::cout << "Prev lily == null" << std::endl;
		}
		else {

			removeLilyPad(prevLily);
		}
	}
}

void GameScene::removeLilyPad(LilyPad* lilyPad) {
	if (!lilyPad)return;
	//remove from cell
	Cell* lilysCell = getCellByGridPos(lilyPad->getGridPos());
	lilysCell->lilyPad = NULL;

	//remove from lilypads
	int s = lilypads.size();
	for (int i = 0; i < s; i++) {
		LilyPad* lily = lilypads[i];
		if (!lily)continue;
		if (lily == lilyPad) {

			lilypads[i] = NULL;
				break;
		}
	}

	grid->removeChild(lilyPad);

	//deleting lilypad
	delete lilyPad;
}

void GameScene::removeFrog() {
		grid->removeChild(playerFrog);
		delete playerFrog;
}

LilyPad* GameScene::getClickedLilyPad() {
	LilyPad* clickedLilyPad = NULL;
	int s = lilypads.size();
	for (int i = 0; i < s; i++) {
		LilyPad* lilyPad = lilypads[i];
		if (!lilyPad)continue;
		if (lilyPad->isCursorOnObject2d() && input()->getMouseDown(0)) {
			clickedLilyPad = lilyPad;
		}
	}
	return clickedLilyPad;
}

LilyPad* GameScene::getLilyPadByExactPos(Point2 exactPos) {
	int s = lilypads.size();
	LilyPad* lilypad = NULL;
	for (int i = 0; i < s; i++) {
		LilyPad* curlilyPad = lilypads[i];
		if (!curlilyPad)continue;
		Point2 pos = curlilyPad->worldposition();
		if (pos.x == exactPos.x && pos.y == exactPos.y) {
			lilypad = curlilyPad;
			break;
		}
	}
	return lilypad;
}

LilyPad* GameScene::getLilyPadByGridPos(Point2 gridPos) {
	int s = lilypads.size();
	LilyPad* lilypad = NULL;
	for (int i = 0; i < s; i++) {
		LilyPad* curlilyPad = lilypads[i];
		if (!curlilyPad)continue;
		Point2 pos = curlilyPad->getGridPos();
		if (pos.x == gridPos.x && pos.y == gridPos.y) {
			lilypad = curlilyPad;
			break;
		}
	}
	return lilypad;
}

Cell* GameScene::getCellByGridPos(Point2 gridPos) {
	int s = cells.size();
	Cell* cell = NULL;
	for (int i = 0; i < s; i++) {
		Cell* curCell = cells[i];
		Point2 pos = curCell->position;
		if (pos.x == gridPos.x && pos.y == gridPos.y) {
			cell = curCell;
			break;
		}
	}
	return cell;
}