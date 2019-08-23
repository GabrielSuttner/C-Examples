#include "Maze.h"
//This function is called from Main to do the bulk of the work. 
void Maze::solve() {
	//I use unsigned char as the counter so that it only takes one Byte. 
	unsigned char counter = 0x15;
	int l = 0, h = 0, w = 0;
	int dec;

	int stop = 0;
	bool again = 1;

	//place a specific character at the opening at the end of the maze. 
	unsigned char* end = &solveArray[layer - 1][height - 1][width - 1];

	unsigned char* position = &solveArray[l][h][w];

	while (stop != 3) {
		if (again == 1) {
			dec = decision(l, h, w);
			ARRAY = counter;
		}
		again = 1;
		switch (dec) {
		case 0:
			ARRAY = 0xff;
			dec = recursion(l, h, w);
			if (dec == 7) {
				stop = 3;
			}
			again = 0;
			break;
		case 1:
			w--;
			break;
		case 2:
			w++;
			break;
		case 3:
			h--;
			break;
		case 4:
			h++;
			break;
		case 5:
			l++;
			break;
		case 6:
			l--;
			break;
		case 7:
			stop = 3;
			continue;
			break;
		}
		position = &ARRAY;
		if (position == end) {
			stop = 3;
		}
		counter = ((counter == 0x5f) || (counter == 0x58)) ? counter + 2 : counter++;
		if (counter == 0x7f) {
			break;
		}

	}
	position = NULL;
	end = NULL;
	delete position;
	delete end;
};

int Maze::recursion(int l, int h, int w) {
	ARRAY = 0xff;
	int output;
	//return the direction to go back
	if ((w > 0) && solveArray[l][h][w - 1] != 'X' && solveArray[l][h][w - 1] < ARRAY) {
		output = 1;
	}
	else if
		((w < this->width - 1) && solveArray[l][h][w + 1] != 'X' && solveArray[l][h][w + 1] < ARRAY) {
		output = 2;
	}
	else if
		((h > 0) && solveArray[l][h - 1][w] != 'X' && solveArray[l][h - 1][w] < ARRAY) {
		output = 3;
	}
	else if
		((h < this->height - 1) && solveArray[l][h + 1][w] != 'X' && solveArray[l][h + 1][w] < ARRAY) {
		output = 4;
	}
	else if
		((l > 0) && solveArray[l - 1][h][w] != 'X' && solveArray[l - 1][h][w] < ARRAY) {
		output = 6;
	}
	else if
		((l < this->layer - 1) && solveArray[l + 1][h][w] != 'X' && solveArray[l + 1][h][w] < ARRAY) {
		output = 5;
	}
	else {
		output = 7;
	}
	if (output == 7) {
		success = 0;
	}
	return output;
}
int Maze::decision(int l, int h, int w) {
	int output;
	//return the direction to go
	if (ARRAY == 3) {
		return 7;
	}
	if ((w > 0) && solveArray[l][h][w - 1] == '_') {
		output = 1;
	}
	else if
		((w < this->width - 1) && solveArray[l][h][w + 1] == '_') {
		output = 2;
	}
	else if
		((h > 0) && solveArray[l][h - 1][w] == '_') {
		output = 3;
	}
	else if
		((h < this->height - 1) && solveArray[l][h + 1][w] == '_') {
		output = 4;
	}
	else if
		((l < this->layer - 1) && solveArray[l + 1][h][w] == '_') {
		output = 5;
	}
	else if
		((l > 0) && solveArray[l - 1][h][w] == '_') {
		output = 6;
	}
	else {
		output = 0;
	}

	return output;
}

//this function creates a 3 dimensional maze. 
void Maze::createMaze(int height, int width, int layer){
	this->layer = layer;
	this->width = width;
	this->height = height;
	myArray = new int** [layer];

	for (int i = 0; i < layer; i++) {
		this->myArray[i] = new int* [height];
		for (int j = 0; j < height; j++) {
			myArray[i][j] = new int[width];
		}
	}
	//create the second array to print out
	solveArray = new unsigned char** [layer];
	for (int i = 0; i < layer; i++) {
		this->solveArray[i] = new unsigned char* [height];
		for (int j = 0; j < height; j++) {
			solveArray[i][j] = new unsigned char[width];
		}
	}
}

//output the contents of the maze. 
std::string Maze::toString() const {
	std::stringstream ssOutput;
	solveArray[this->layer - 1][this->height - 1][this->width - 1] = 0x33;
	if (myArray != NULL) {
		ssOutput << "Solve Maze:\n";
		for (int i = 0; i < layer; i++) {
			ssOutput << "Layer " << i + 1 << '\n';
			for (int j = 0; j < height; j++) {
				ssOutput << " ";
				for (int k = 0; k < width; k++) {
					char c = (myArray[i][j][k] == 0) ? '_' : 'X';
					if (i == layer - 1 && k == width - 1 && j == height - 1) {
						c = 0x5f;
					}
					ssOutput << c << " ";
				}
				ssOutput << '\n';
			}
		}
		ssOutput << "\n";
	}
	if (!success) {
		ssOutput << "No Solution Exists!";
	}
	if (solveArray != NULL && success) {
		char t;
		ssOutput << "Solution:\n";
		for (int i = 0; i < layer; i++) {
			ssOutput << "Layer " << i + 1 << '\n';
			for (int j = 0; j < height; j++) {
				ssOutput << " ";
				for (int k = 0; k < width; k++) {
					if (solveArray[i][j][k] != 0x5f && solveArray[i][j][k] != 0x58 && solveArray[i][j][k] != 0xff && solveArray[i][j][k] != 0x33) {
						t = 0x32;
					}
					else if (solveArray[i][j][k] == 0xff) {
						t = 0x5f;
					}
					else {
						t = solveArray[i][j][k];
					}
					ssOutput << t << " ";
				}
				ssOutput << '\n';
			}
		}
		ssOutput << "\n";
	}
	
	return ssOutput.str();
};