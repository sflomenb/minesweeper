#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include "cell.hh"
using namespace std;

#ifndef WIN
#define WIN 1
#endif
#ifndef LOSE
#define LOSE -1
#endif
#ifndef CONTINUE
#define CONTINUE 0
#endif
class MineSweeper {
public:
	//constructor
	MineSweeper(int width, int height, int number_of_mines) {
		this->width = width;
		this->height = height;
		this->totalCell = width * height;
		this->number_of_mines = number_of_mines;
		this->checkedCell = 0;
		this->gameState = CONTINUE;

	}
	void initBoard();
	void printBoard();
	int randomInt(int max);
	int getCoord(int bound, string xory);
	void dig(int x, int y);
	vector<pair<int, int> > getNearCell(int x, int y);
	void startGame();
	void chain_effect(int xCoord, int yCoord);
	void makeAMove();
	void updateGameState();
	void checkNearbyCell(int xCoord, int yCoord);
	void endGame();

private:
	int gameState;
	int width;
	int height;
	int totalCell;
	int checkedCell;
	int number_of_mines;
	vector<vector<Cell*> > board;
};

void MineSweeper::endGame(){

}

void MineSweeper::startGame() {
	cout << "welcome to command-line MineSweeper game... " << endl;
	initBoard();
	printBoard();
	while (gameState == CONTINUE) {
		makeAMove();
		printBoard();
		updateGameState();
	}
	if (gameState == LOSE) {
		cout << "you LOSE" << endl;
	}
	else {
		cout << "you WIN" << endl;
	}
	endGame();


}

void MineSweeper::updateGameState() {
	// update checkedCell
	checkedCell = 0;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (board[j][i]->isChecked()) {
				checkedCell ++;
			}
		}
	}

	if (checkedCell == (totalCell - number_of_mines)) {
		gameState = WIN;
	}

}

void MineSweeper::chain_effect(int xCoord, int yCoord) {
	queue<pair<int, int> > q;
	q.emplace(make_pair(xCoord, yCoord));
	int x = 0;
	int y = 0;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		// check nearby cell
		// get cell with minenumber = 0
		vector<pair<int, int> > nearCells = getNearCell(x, y);
		for (auto p : nearCells) {

			if (this->board[p.second][p.first]->getMineNumber() == 0
			        && !(this->board[p.second][p.first]->isChecked())) {
				// put to q
				q.push(p);
			}
		}
		if (this->board[y][x]->getMineNumber() == 0) {
			checkNearbyCell(x, y);
		}
		q.pop();
	}


}


void MineSweeper::makeAMove() {
	int xCoord = getCoord(width, "x");
	int yCoord = getCoord(height, "y");
	dig(xCoord, yCoord);
	if (gameState != LOSE)  {
		// expand
		chain_effect(xCoord, yCoord);
	}

}


void MineSweeper::checkNearbyCell(int xCoord, int yCoord) {
	vector<pair<int, int> > nearCells = getNearCell(xCoord, yCoord);
	for (pair<int, int> p : nearCells) {
		if (!(this->board[p.second][p.first]->isMine())) {
			this->board[p.second][p.first]->markCheck();
		}
	}
}
void MineSweeper::dig(int x, int y) {
	if (board[y][x]->dig()) {
		gameState = LOSE;
	}
	else {
		gameState = CONTINUE;
	}
}

int MineSweeper::getCoord(int bound, string xory) {
	int coordinate = 0;
	string input = "";
	while (true) {
		cout << "Please enter " << xory << " coordinate: ";
		getline(cin, input);

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (myStream >> coordinate) {
			if (coordinate < bound) {
				break;
			}
		}
		cout << "Invalid number or out of bound, please try again" << endl;
	}
	return coordinate;
}

vector<pair<int, int> > MineSweeper::getNearCell(int x, int y) {
	vector<pair<int, int> > nearCells;
	nearCells.push_back(make_pair(x - 1, y - 1));
	nearCells.push_back(make_pair(x, y - 1));
	nearCells.push_back(make_pair(x + 1, y - 1));
	nearCells.push_back(make_pair(x - 1, y));
	nearCells.push_back(make_pair(x + 1, y));
	nearCells.push_back(make_pair(x - 1, y + 1));
	nearCells.push_back(make_pair(x, y + 1));
	nearCells.push_back(make_pair(x + 1, y + 1));
	for (vector<pair<int, int> >::iterator it = nearCells.begin(); it != nearCells.end();)
	{
		if (it->first < 0 || it->second < 0 || it->first >= width || it->second >= height ) {
			it = nearCells.erase(it);
		}
		else {
			++it;
		}
	}
	return nearCells;

}


int MineSweeper::randomInt(int max) {
	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, max - 1); // guaranteed unbiased
	return uni(rng);
}


void MineSweeper::initBoard() {
	// creat vector
	for (int i = 0; i < height; ++i)
	{
		vector<Cell*> row;
		for (int j = 0; j < width; ++j)
		{
			// Cell *cell = new Cell();
			row.push_back(new Cell());
		}
		board.push_back(row);
	}

	// assign mine
	int mineNumber = 0;
	for (int i = 0; i < number_of_mines; ++i)
	{
		// random location for mine
		int xCoord = randomInt(width);
		int yCoord = randomInt(height);
		if (!board[yCoord][xCoord]->isMine()) {
			board[yCoord][xCoord]->buryMine();
			//increase nearby cell's mine count by one.
			// get nearyby cell
			vector<pair<int, int> > nearCells = getNearCell(xCoord, yCoord);
			// for each cell increase mine count by one
			for (pair<int, int> p : nearCells) {
				mineNumber = this->board[p.second][p.first]->getMineNumber() + 1;
				// cout << "mineNumber: " << mineNumber << endl;
				this->board[p.second][p.first]->setMineNumber(mineNumber);
			}
		}
		else {
			i --;
		}
	}

}


void MineSweeper::printBoard() {
	cout << "board: " << endl;
	string sym = " ";
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (!board[i][j]->isChecked()) {
				sym += "T";
			}
			else if (board[i][j]->isMine())       {
				sym += "X";
			}
			else {
				sym += to_string(board[i][j]->getMineNumber());
			}
			cout << sym;
			sym = " ";

		}
		cout << endl;
	}
	cout << endl;
}
