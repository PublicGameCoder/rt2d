#include <fstream>
#include <sstream>

#include "GameScene.h"


GameScene::GameScene(std::vector<std::vector<char>> selectedgrid) : Scene()
{
	numbergrid = selectedgrid;

	bgColor = new RGBAColor(
		(uint8_t)0,
		(uint8_t)0,
		(uint8_t)255
		);

	LilyPad* testLily = new LilyPad();

	Point2 dimensions = testLily->sprite()->size;
	cellwidth = dimensions.x;
	cellheight = dimensions.y;

	delete testLily;
	border = 1;

	createGrid();
}

void GameScene::resetLevel() {
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
	createGrid();
}

void GameScene::createGrid() {
	if (numbergrid.size() <= 0 || numbergrid[0].size() <= 0) {
		return;
	}
	gridheight = numbergrid.size();
	gridwidth = numbergrid[0].size();
	grid = new GridEntity();
	int xgridpos = (SWIDTH / 2) - (gridwidth*(cellwidth + border) / 2);
	int ygridpos = (SHEIGHT / 2) - (gridheight*(cellheight + border) / 2);
	grid->position = Point2(xgridpos, ygridpos);

	Point2 frogPos;

	// create cells
	for (int y = 0; y<gridheight; y++) {
		for (int x = 0; x<gridwidth; x++) {
			short int dataStore = numbergrid[y][x];
			if ((dataStore) == 0) {
				Cell* cell = new Cell();
				cell->position.x = x;
				cell->position.y = y;

				cell->entity = new GridEntity();
				cell->entity->addSprite(AUTOGENWHITE);
				cell->entity->sprite()->color = *bgColor;
				cell->entity->sprite()->size.x = cellwidth;
				cell->entity->sprite()->size.y = cellheight;

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

				cell->lilyPad->position.x = x*(cellwidth + border);
				cell->lilyPad->position.y = y*(cellheight + border);

				cells.push_back(cell);
				lilypads.push_back(cell->lilyPad);
				grid->addChild(cell->lilyPad);
			}
			else if (dataStore == 2) {
				Cell* cell = new Cell();
				cell->position.x = x;
				cell->position.y = y;

				cell->lilyPad = new LilyPad();
				cell->lilyPad->setGridPos(Point2(x, y));
				cell->lilyPad->sprite()->size.x = cellwidth;
				cell->lilyPad->sprite()->size.y = cellheight;

				cell->lilyPad->position.x = x*(cellwidth + border);
				cell->lilyPad->position.y = y*(cellheight + border);

				cells.push_back(cell);
				lilypads.push_back(cell->lilyPad);
				grid->addChild(cell->lilyPad);

				frogPos = Point2(x, y);
			}
		}
	}
	playerFrog = new Frog();
	playerFrog->setGridPos(frogPos);
	Point3 frogsPosition;
	frogsPosition.x = frogPos.x*(cellwidth + border);
	frogsPosition.y = frogPos.y*(cellwidth + border);
	playerFrog->setPosition(frogsPosition);
	grid->addChild(playerFrog);

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
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	if (input()->getMouseDown(0)) {
		handleMovement();
	}
}

bool GameScene::isFinished() {
	if (playerFrog->isTimedOut())return false;
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
	if (playerFrog->isTimedOut())return;
	Point2 gridPosFrog = playerFrog->getGridPos();
	LilyPad* lilyPad = getClickedLilyPad();
	if (!lilyPad) { return; }
	Point2 gridPosLily = lilyPad->getGridPos();
	if (gridPosFrog == gridPosLily) { return; }

	Point2 facing = playerFrog->facing();//Get's the facing of the frog
	bool xrow = (gridPosFrog.x == gridPosLily.x);//True if the x positions on the grid are the same.
	bool yrow = (gridPosFrog.y == gridPosLily.y);//True if the y positions on the grid are the same.
	if (xrow | yrow) {
		if (xrow) {
			int x = gridPosFrog.x;
			int curY = gridPosFrog.y;
			int amountBetween = gridPosLily.y - gridPosFrog.y;
			bool negative = (amountBetween < 0);
			if (negative) {
				amountBetween *= -1;
			}
			for (int y = 1; y < amountBetween; y++) {
				LilyPad* lilyBetween = getLilyPadByGridPos(Point2(x, curY + ((negative) ? (y * -1) : y)));
				if (!lilyBetween)continue;
				if (lilyBetween != lilyPad) return;
			}
		}
		else if (yrow) {
			int y = gridPosFrog.y;
			int curX = gridPosFrog.x;
			int amountBetween = gridPosLily.x - gridPosFrog.x;
			bool negative = (amountBetween < 0);
			if (negative) {
				amountBetween *= -1;
			}
			for (int x = 1; x < amountBetween; x++) {
				LilyPad* lilyBetween = getLilyPadByGridPos(Point2(curX + ((negative) ? (x * -1) : 1), y));
				if (!lilyBetween)continue;
				if (lilyBetween != lilyPad) return;
			}
		}

		Point3 dir = lilyPad->position - playerFrog->position;

		//Right
		if (dir.x > 0) {
			if (facing.x == -1)return;//Facing Left
			playerFrog->rotation.z = (90 * DEG_TO_RAD);
		}
		//Left
		if (dir.x < 0) {
			if (facing.x == 1)return;//Facing Right
			playerFrog->rotation.z = (-90 * DEG_TO_RAD);
		}
		//Down
		if (dir.y > 0) {
			if (facing.y == -1)return;//Facing Up
			playerFrog->rotation.z = (180 * DEG_TO_RAD);
		}
		//Up
		if (dir.y < 0) {
			if (facing.y == 1)return;//Facing Down
			playerFrog->rotation.z = (360 * DEG_TO_RAD);
		}

		Point2 gridPos = playerFrog->getGridPos();
		playerFrog->moveTowards(lilyPad->position);
		playerFrog->setGridPos(gridPosLily);
		LilyPad* prevLily = getLilyPadByGridPos(gridPos);
		if (prevLily) {
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