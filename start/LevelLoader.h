#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <iostream>
#include <fstream>
#include <vector>

/*
:---------------------:
: File Data Structure :
:---------------------:

File data indentifier with lvl extension. [ 00.lvl ]
=====================================================

Number of Levels : Grid X size : Grid Y size : <Water/LilyPad/Frog & LilyPad>..

:---------------------:
:  Example  (Number)  :
:---------------------:

1 3 3 0 2 0 1 1 0 1 1 1

:---------------------:
:  Example  (Binair)  :
:---------------------:

000000001 000000011 000000011 000000000 000000010 000000000 000000001 000000001 000000000 000000001 000000001 000000001

:---------------------:
:   Example's  Grid   :
:---------------------:
f
:       :
-------------
: 0 2 0 :
: 1 1 0 :
: 1 1 1 :
-------------
:       :
*/

using namespace std;

class LevelLoader {
public:

	LevelLoader();

	virtual ~LevelLoader();

	vector<vector<vector<char>>> LevelLoader::getLevels();

private:
	string directory = "./leveldatas/";

	vector<vector<vector<char>>> allLevels;
	vector<vector<vector<char>>> loadFile(string fileName);

	void createLevels();
	void saveFile(string fileName, std::vector<std::vector<std::vector<char>>> levels);
};

#endif // !LEVELLOADER_H
