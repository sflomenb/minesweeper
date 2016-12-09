#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdexcept>      // std::invalid_argument
#include "minesweeper.hh"
#include <random>
#include <utility>      // std::pair, std::make_pair

#define SPACE " "
#define NOTCHECK  "O"
#define MINESYM  "X"
#define NOTMINESYM  "_"

using namespace std;

bool argumentCheck(int width, int height, int number_of_mines) {
	// neither arguments can be zero
	if (width == 0 || height == 0 || number_of_mines == 0) {
		cout << "argument error: please give correct argument " << endl;
		return false;
	}

	// number_of_mines must be less than total number of cell
	// need overflow check here
	if (number_of_mines >= width * height) {
		cout << "argument error: please give correct argument" << endl;
		return false;
	}
	return true;

}

// ERR62-CPP. Detect errors when converting a string to a number
bool StringToInt(const string& str, int& result) {
	try {
		size_t lastChar;
		result = stoi(str, &lastChar, 10);
		return lastChar == str.size();
	} catch (invalid_argument&) {
		return false;
	} catch (out_of_range&){
		return false;
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 4) {
		cout << "argument error:" << endl;
		cout << "wrong number of argument" << endl;
		exit(1);// not good there
	}
	int width = 0;
	int height = 0;
	int number_of_mines = 0;
	StringToInt(argv[1], width);
	StringToInt(argv[2], height);
	StringToInt(argv[3], number_of_mines);

	if (!argumentCheck(width, height, number_of_mines)) {
		exit(1);
	}

	MineSweeper *game = new MineSweeper(width, height, number_of_mines);
	game->startGame();

	return 0;
}