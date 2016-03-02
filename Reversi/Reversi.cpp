#include "Reversi.h"
#include <iostream>
Reversi::Reversi(void)
{
	init();
}


Reversi::~Reversi(void)
{
}

void Reversi::init(void){
	for (int i = 0; i < 8; i++) { //intializing board
		for (int j = 0; j < 8; j++) {
			mBoard[j][i] = eEMPTY;
			chkBoard[j][i] = 0;
			stepRecord[0][j][i] = mBoard[j][i];
		}
		mArry[i] = eEMPTY;
		directions[i] = 0;
	}
	mBoard[3][3] = eBLACK;
	mBoard[4][4] = eBLACK;
	mBoard[3][4] = eWHITE;
	mBoard[4][3] = eWHITE;
	stepRecord[0][3][3] = mBoard[3][3];
	stepRecord[0][4][4] = mBoard[4][4];
	stepRecord[0][3][4] = mBoard[3][4];
	stepRecord[0][4][3] = mBoard[4][3];
	mArry[0] = eWHITE;
	numRecord = 1;
	curRecord = 1;
	bBW = true;
	isPassed = false;
}

bool Reversi::isBW(void){
	return bBW;
}

bool Reversi::isEnd(void){

	return true;
}

bool Reversi::isPass(){
	bool bPass = true;
	for (int i = 0; i < 8; i++) {
		directions[i] = 0;
		for (int j = 0; j < 8; j++) {
			chkBoard[j][i] = 0;
			if (mBoard[j][i] == eEMPTY) {
				if (North(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (NorthEast(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (East(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (SouthEast(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (South(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (SouthWest(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (West(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
				if (NorthWest(i, j)) {
					bPass = false;
					chkBoard[j][i] = 1;
				}
			}
			
		}
	}
	return bPass;
}

void Reversi::setBW(int x, int y){
	int iEnemy = eEMPTY; //Enemy's color
	int myColor = eEMPTY; //My color
	if (bBW && mBoard[y][x] == eEMPTY){
		mBoard[y][x] = eBLACK;
		iEnemy = eWHITE;
		myColor = eBLACK;
	}
	else if(!bBW && mBoard[y][x] == eEMPTY) {
		mBoard[y][x] = eWHITE; 
		iEnemy = eBLACK; 
		myColor = eWHITE;
	}
	else {
		return;
	}
	//North
	if (mBoard[y - 1][x] == iEnemy) {
		int i = 1;
		while (mBoard[y - i][x] == iEnemy && y - i >= 0) {
			i++;
		}
		if (i > 1 && mBoard[y - i][x] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y - j][x] = myColor;
			}
		}
	}
	//North East
	if (mBoard[y - 1][x + 1] == iEnemy) {
		int i = 1;
		while (mBoard[y - i][x + i] == iEnemy && y - i >= 0 && x + i <= 7) {
			i++;
		}
		if (i > 1 && mBoard[y - i][x + i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y - j][x + j] = myColor;
			}
		}
	}
	//East
	if (mBoard[y][x + 1] == iEnemy) {
		int i = 1;
		while (mBoard[y][x + i] == iEnemy && x + i <= 7) {
			i++;
		}
		if (i > 1 && mBoard[y][x + i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y][x + j] = myColor;
			}
		}
	}
	//South East
	if (mBoard[y + 1][x + 1] == iEnemy) {
		int i = 1;
		while (mBoard[y + i][x + i] == iEnemy && y + i <= 7 && x + i <= 7) {
			i++;
		}
		if (i > 1 && mBoard[y + i][x + i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y + j][x + j] = myColor;
			}
		}
	}
	//South
	if (mBoard[y + 1][x] == iEnemy) {
		int i = 1;
		while (mBoard[y + i][x] == iEnemy && y + i <= 7) {
			i++;
		}
		if (i > 1 && mBoard[y + i][x] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y + j][x] = myColor;
			}
		}
	}
	bool bMode = true;
	//South West
	if (mBoard[y + 1][x - 1] == iEnemy) {
		int i = 1;
		while (mBoard[y + i][x - i] == iEnemy && y + i <= 7 && x - i >= 0) {
			i++;
		}
		if (i > 1 && mBoard[y + i][x - i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y + j][x - j] = myColor;
			}
		}
	}
	//West
	if (mBoard[y][x - 1] == iEnemy) {
		int i = 1;
		while (mBoard[y][x - i] == iEnemy && x - i >= 0) {
			i++;
		}
		if (i > 1 && mBoard[y][x - i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y][x - j] = myColor;
			}
		}
	}
	//North West
	if (mBoard[y - 1][x - 1] == iEnemy) {
		int i = 1;
		while (mBoard[y - i][x - i] == iEnemy && y - i >= 0 && x - i >= 0) {
			i++;
		}
		if (i > 1 && mBoard[y - i][x - i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y - j][x - j] = myColor;
			}
		}
	}
	//After all chess flipped, record the board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			stepRecord[curRecord][j][i] = mBoard[j][i];
		}
	}
	mArry[curRecord] = myColor;
	if (numRecord == curRecord) {
		numRecord++;
		curRecord++;
	}
	else {
		curRecord++;
		numRecord = curRecord;
	}
}

int Reversi::getBW(int x, int y){
	return mBoard[y][x];
}

bool Reversi::moveAnalyze(int x, int y){
	bool result = false; //Legal = true; Illegal = false; 
	int iEnemy = eEMPTY; //Enemy's color
	int myColor = eEMPTY;
	if (bBW) { iEnemy = eWHITE; myColor = eBLACK; }
	else { iEnemy = eBLACK; myColor = eWHITE; }
	//Check 8 directions if the set can be set on the coordinate
	//If bMode == false, enter flipping mode;
	//North
	if (North(x, y)) {
		result = true;
	}
	//North East
	if (NorthEast(x, y)) {
		result = true;
	}
	//East
	if (East(x, y)) {
		result = true;
	}
	//South East
	if (SouthEast(x, y)) {
		result = true;
	}
	//South
	if (South(x, y)) {
		result = true;
	}
	//South West
	if (SouthWest(x, y)) {
		result = true;
	}
	//West
	if (West(x, y)) {
		result = true;
	}
	//North West
	if (NorthWest(x, y)) {
		result = true;
	}
	
	return result;
}

void Reversi::Undo(void)
{
	if (curRecord > 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mBoard[j][i] = stepRecord[curRecord-2][j][i];
			}
		}
		if (mArry[curRecord - 1] == 2) {
			bBW = false;
		}
		else if (mArry[curRecord - 1] == 1) {
			bBW = true;
		}
		curRecord--;
	}
}

void Reversi::Redo(void)
{

	if (curRecord < numRecord) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mBoard[j][i] = stepRecord[curRecord][j][i];
			}
		}
		if (mArry[curRecord-1] == 2) {
			bBW = false;
		}
		else if (mArry[curRecord-1] == 1) {
			bBW = true;
		}
		curRecord++;
	}
}

bool Reversi::North(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK; 
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y - 1][x] == iEnemy) {
		i++;
	}
	while (mBoard[y - i][x] == iEnemy && y - i > 0) {
		i++;
	}
	if (mBoard[y - i][x] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::NorthEast(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y - 1][x + 1] == iEnemy) {
		i++;
	}
	while (mBoard[y - i][x + i] == iEnemy && y - i > 0 && x + i < 7) {
		i++;
	}
	if (mBoard[y - i][x + i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::East(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y][x + 1] == iEnemy) {
		i++;
	}
	while (mBoard[y][x + i] == iEnemy && x + i < 7) {
		i++;
	}
	if (mBoard[y][x + i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::SouthEast(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y + 1][x + 1] == iEnemy) {
		i++;
	}
	while (mBoard[y + i][x + i] == iEnemy && y + i < 7 && x + i < 7) {
		i++;
	}
	if (mBoard[y + i][x + i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::South(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y + 1][x] == iEnemy) {
		i++;
	}
	while (mBoard[y + i][x] == iEnemy && y + i < 7) {
		i++;
	}
	if (mBoard[y + i][x] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::SouthWest(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y + 1][x - 1] == iEnemy) {
		i++;
	}
	while (mBoard[y + i][x - i] == iEnemy && y + i < 7 && x - i > 0) {
		i++;
	}
	if (mBoard[y + i][x - i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::West(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y][x - 1] == iEnemy) {
		i++;
	}
	while (mBoard[y][x - i] == iEnemy && x - i > 0) {
		i++;
	}
	if (mBoard[y][x - i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Reversi::NorthWest(int x, int y) {
	int MyColor = eEMPTY, iEnemy = eEMPTY;
	if (bBW) {
		MyColor = eBLACK;
		iEnemy = eWHITE;
	}
	else {
		MyColor = eWHITE;
		iEnemy = eBLACK;
	}
	int i = 0;
	if (mBoard[y - 1][x - 1] == iEnemy) {
		i++;
	}
	while (mBoard[y - i][x - i] == iEnemy && x - i > 0 && y - i >0) {
		i++;
	}
	if (mBoard[y - i][x - i] == MyColor && i > 0) {
		return true;
	}
	else {
		return false;
	}
}
