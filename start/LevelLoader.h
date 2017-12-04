/**
 * @file D:\Projecten\Project_RT2D\Game_Emulator\rt2d\start\LevelLoader.h.
 *
 * Declares the level loader class.
 */

#ifndef LEVELLOADER_H
///< .
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

/** . */
using namespace std;

/**
 * A level loader.
 *
 * @author Mike De Groot
 * @date 4-12-2017
 */

class LevelLoader {
public:

	/**
	 * Default constructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	LevelLoader();

	/**
	 * Destructor.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	virtual ~LevelLoader();

	/**
	 * Gets the levels.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @return The levels.
	 */

	vector<vector<vector<char>>> LevelLoader::getLevels();

private:
	/** Pathname of the directory. */
	string directory = "./leveldatas/";

	/** all levels. */
	vector<vector<vector<char>>> allLevels;

	/**
	 * Loads a file.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param fileName Filename of the file.
	 *
	 * @return The file.
	 */

	vector<vector<vector<char>>> loadFile(string fileName);

	/**
	 * Creates the levels.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 */

	void createLevels();

	/**
	 * Saves a file.
	 *
	 * @author Mike De Groot
	 * @date 4-12-2017
	 *
	 * @param fileName Filename of the file.
	 * @param levels   The levels.
	 */

	void saveFile(string fileName, std::vector<std::vector<std::vector<char>>> levels);
};

#endif // !LEVELLOADER_H
