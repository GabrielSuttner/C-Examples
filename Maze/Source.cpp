#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "Maze.h"
using namespace std;

void clear(stringstream* ss);

int main(int argc, char** argv) {
	VS_MEM_CHECK

	//Error Check to ensure there are enough files passed as arguments. 
	if (argc < 3) {
		cout << "Error: not enough files provided" << endl;
		return 1;
	}

	fstream inFS;
	fstream outFS;
	
	inFS.open(argv[1]);
	outFS.open(argv[2]);

	//if one of the files doesn't open correctly.
	if (!inFS.is_open()) {
		cout << "couldn't open " << argv[1] << endl;
	}
	if (!outFS.is_open()) {
		cout << "couldn't open " << argv[2] << endl;
	}
	string sLine;
	stringstream ssLine;

	//pull the first line to determine the size of the maze. 
	getline(inFS, sLine);
	ssLine << sLine;

	int height;
	int width;
	int layer;

	ssLine >> height >> width >> layer;
	//clears contents of stringstream
	clear(&ssLine);

	Maze maze;
	maze.createMaze(height, width, layer);

	//fill out the arrays
	for (int i = 0; i < layer; i++) {
		for (int j = 0; j < height; j++) {
			getline(inFS, sLine);
			if (sLine.empty()) {
				getline(inFS, sLine);
			}
			ssLine << sLine;
			for (int k = 0; k < width; k++) {
				int num;
				ssLine >> num;
				if ((i == (layer - 1)) && (j == (height - 1)) && (k == width - 1)) {
					num = 3;
				}
				maze.setValue( j, k, i, num);
			}
			clear(&ssLine);
		}
	}
	
	clear(&ssLine);
	//calls the solve function.
	maze.solve();

	sLine = maze.toString();
	outFS << sLine;

	//close all files. 
	inFS.close();
	outFS.close();
	return 0;
}
//helper function
void clear(stringstream* ss) {
	ss->clear();
	ss->str(string());
}