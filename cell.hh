#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <random>

using namespace std;
class Cell {
public:
	//constructor
	Cell() {
		mine = false;
		checked = false;
		mineNumber = 0;
	}
	Cell(bool isMine) {
		mine = isMine;
		checked = false;
		mineNumber = 0;
	}
	void buryMine();
	void markCheck();
	bool isChecked();
	bool isMine();
	bool dig();
	void setMineNumber(int num);
	int getMineNumber();
private:
	bool mine;
	bool checked;
	int mineNumber;
};

int Cell::getMineNumber(){
	return mineNumber;
}

void Cell::setMineNumber(int num) {
	this->mineNumber = num;
}
void Cell::buryMine() {
	this->mine = true;
}
void Cell::markCheck() {
	this->checked = true;
}

bool Cell::dig() {
	markCheck();
	return isMine();
}
bool Cell::isMine() {
	return this->mine;
}

bool Cell::isChecked() {
	return this->checked;
}

