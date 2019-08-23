//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef MAZE_H
#define MAZE_H
#define ARRAY solveArray[l][h][w]
#include "MazeInterface.h"
#include <string>
#include <sstream>
class Maze : MazeInterface
{
private:
	int*** myArray;
	unsigned char*** solveArray;
	int layer;
	int height;
	int width;
	bool success;

public:
	Maze(void) : layer(0), height(0), width(0), myArray(NULL), solveArray(NULL), success(1) {};
	~Maze(void) {
		if (myArray != NULL) {
			for (int i = 0; i < layer; i++) {
				for (int j = 0; j < height; j++) {
					delete[] myArray[i][j];
					delete[] solveArray[i][j];
				}
				delete[] myArray[i];
				delete[] solveArray[i];
			}
			delete[] myArray;
			delete[] solveArray;
		}
	};

	void solve();
	/**function to go back a space*/
	int recursion(int l, int h, int w);
	/*0 dead end 1 left 2 right 3 up 4 down 5 in 6 out*/
	int decision(int l, int h, int w);

	/**creates the maze*/
	void createMaze(int height, int width, int layer);

	/**Values set as height, width, layer*/
	void setValue(int height, int width, int layer, int value) {
		myArray[layer][height][width] = value;
		solveArray[layer][height][width] = (value == 1) ? 'X' : '_';
	};

	/** Solve maze
	   @return true if solveable, else false
	*/
	bool find_maze_path() {
		return success;
	};

	/** Output maze (same order as input maze)
	  @return string of 2D layers
	*/
	std::string toString() const;
};
#endif // MAZE_H
