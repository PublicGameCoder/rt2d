#include "LevelLoader.h"

/**
 *	@brief		This is the constructor of this class.
 */
LevelLoader::LevelLoader() {
	//createLevels();
	allLevels = loadFile("00.lvl");//Loads the levels from file path "./leveldatas/00.lvl"
}

void LevelLoader::createLevels() {
	/*
	std::vector<std::vector<std::vector<char>>> levels;

	//Level 1
	std::vector<std::vector<char>> numbergrid = {
		{ 1, 1 },
		{ 0, 1 },
		{ 2, 1 },
	};
	levels.push_back(numbergrid);

	//Level 2
	numbergrid = {
		{ 2, 0, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
	};
	levels.push_back(numbergrid);

	//Level 3
	numbergrid = {
		{ 1, 1, 1, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 0, 2, 0 },
	};
	levels.push_back(numbergrid);
	
	//Level 4
	numbergrid = {
		{ 0, 1, 1, 0, 0 },
		{ 2, 0, 1, 1, 1 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0 },
	};
	levels.push_back(numbergrid);
	
	//Level 5
	numbergrid = {
		{ 0, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 0, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 2, 0, 0, 1, 0 },
	};
	levels.push_back(numbergrid);

	saveFile("00.lvl", levels);
	*/
}

vector<vector<vector<char>>> LevelLoader::getLevels() {
	return this->allLevels;
}

vector<vector<vector<char>>> LevelLoader::loadFile(string fileName) {
	fileName = directory + fileName;
	vector<vector<vector<char>>> levels;
	ifstream file(fileName, ios::in | ios::binary);
	if (!file.is_open()) {
		cout << "couldn't load path fileName" << endl;
		return levels;
	}

	char lvlAmountBuff[1];
	file.read(lvlAmountBuff, 1);
	char lvlAmount = lvlAmountBuff[0];
	for (char i = 0; i < lvlAmount; i++) {
		char sizeBuff[2];
		file.read(sizeBuff, 2);
		const char xSize = sizeBuff[0];
		const char ySize = sizeBuff[1];
		const short int size = (xSize+2) * ySize;
		if (size > 1088) {
			cout << "loading size is bigger then 1088!" << endl;//32 x 32 = 1024. +2 for each level = 1088 (34 * 32 = 1088)
			cout << "size: " << (short int)size << endl;
			cout << "width: " << (short int)xSize << endl;
			cout << "height: " << (short int)ySize << endl;
			return levels;
		}
		char dataBuff[1088];
		file.read(dataBuff, size-2);
		vector<vector<char>> gridY;
		int counter = -1;
		for (short int y = 0; y < ySize; y++) {
			vector<char> gridX;
			for (short int x = 0; x < xSize; x++) {
				counter++;
				gridX.push_back(dataBuff[counter]);
			}
			gridY.push_back(gridX);
		}
		levels.push_back(gridY);
	}
	file.close();
 	return levels;
}

void LevelLoader::saveFile(string fileName, std::vector<std::vector<std::vector<char>>> levels) {
	fileName = directory + fileName;

	ofstream file(fileName, ios::out | ios::binary);

	const short int s = levels.size();
	if (s > 100) {
		cout << "you can't save more then 100 levels in a single file" << endl;
		return;
	}
	char lvlAmountBuf[1];
	lvlAmountBuf[0] = s; 
	file.write(lvlAmountBuf, 1);

	for (int i = 0; i < s; i++){
		std::vector<std::vector<char>> numbergrid = levels[i];
		const short int xSize = numbergrid[0].size();
		const short int ySize = numbergrid.size();
		const int buffSize = ((xSize + 2) * ySize);
		if (buffSize > 1088) {
			cout << "saving size is bigger then 1088!" << endl;//32 x 32 = 1024. +2 for each level = 1088 (34 * 32 = 1088)
			return;
		}
		char lvlBuffer[1088];
		lvlBuffer[0] = xSize;
		lvlBuffer[1] = ySize;
		int counter = 1;
		for (int y = 0; y < ySize; y++) {
			for (int x = 0; x < xSize; x++) {
				counter++;
				lvlBuffer[counter] = numbergrid[y][x];
			}
		}
		file.write(lvlBuffer, buffSize);
	}

	file.close();
}

LevelLoader::~LevelLoader() {
		
}