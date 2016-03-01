#include "Reversi.h"
#include <iostream>
Reversi::Reversi(void)
{
	for (int i = 0; i < 8; i++) { //intializing board
		for (int j = 0; j < 8; j++) {
			mBoard[j][i] = eEMPTY;
		}
	}
	mBoard[3][3] = eBLACK;
	mBoard[4][4] = eBLACK;
	mBoard[3][4] = eWHITE;
	mBoard[4][3] = eWHITE;
	bBW = true;
	bMode = false;
}


Reversi::~Reversi(void)
{
}

void Reversi::init(void){
	
}

bool Reversi::isBW(void){
	return bBW;
}

bool Reversi::isEnd(void){
	int countSlots = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (mBoard[j][i] == eEMPTY){ countSlots++; }
		}
	}
	if (countSlots == 0){ return true; }
	else { return false; }
}

bool Reversi::isPass(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (moveAnalyze(j, i)){
				return false;
			}
		}
	}
	bBW = !bBW;
	return true;
}

void Reversi::setBW(int x, int y){
	if (bBW){ mBoard[y][x] = eBLACK; }
	else { mBoard[y][x] = eWHITE; }
	bBW = !bBW;
	if (bMode) {
		bMode = false;
		moveAnalyze(x, y);
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
	if (y > 0){	//If the position is not on the border
		if (mBoard[y-1][x] == iEnemy){
			int i = 1;
			while (mBoard[y-i][x] == iEnemy && y - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y - i][x] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y - i][x] == iEnemy && y - i >= 0) {
						mBoard[y - i][x] = myColor;
						i++;
					}
				}
			}
		}
	}
	//North East
	if (y > 0 && x < 7){	//If the position is not on the border
		if (mBoard[y - 1][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y - i][x + i] == iEnemy && y - i >= 0 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y - i][x + i] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y - i][x + i] == iEnemy && y - i >= 0 && x + i <= 7) {
						mBoard[y - i][x + i] = myColor;
						i++;
					}
				}
			}
		}
	}
	//East
	if (x < 7){	//If the position is not on the border
		if (mBoard[y][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y][x + i] == iEnemy && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y][x + i] == mBoard[y][x]){
				result = true;
				if (!bMode) {
					i = 0;
					while (mBoard[y][x + i] == iEnemy && x + i <= 7) {
						mBoard[y][x + i] = myColor;
						i++;
					}
				}
			}
			std::cout << "here" << std::endl;
		}
	}
	//South East
	if (y < 7 && x < 7){	//If the position is not on the border
		if (mBoard[y + 1][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x + i] == iEnemy && y + i <= 7 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y + i][x + i] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y + i][x + i] == iEnemy && y + i <= 7 && x + i <= 7) {
						mBoard[y + i][x + i] = myColor;
						i++;
					}
				}
			}
		}
	}
	//South
	if (y < 7){	//If the position is not on the border
		if (mBoard[y + 1][x] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x] == iEnemy && y + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y + i][x] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y + i][x] == iEnemy && y + i <= 7) {
						mBoard[y + i][x] = myColor;
						i++;
					}
				}
			}
		}
	}
	//South West
	if (y < 7 && x > 0){	//If the position is not on the border
		if (mBoard[y + 1][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x - i] == iEnemy && y + i <= 7 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y + i][x - i] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y + i][x - i] == iEnemy && y + i <= 7 && x - i >= 0) {
						mBoard[y + i][x - i] = myColor;
						i++;
					}
				}
			}
		}
	}
	//West
	if (x > 0){	//If the position is not on the border
		if (mBoard[y][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y][x - i] == iEnemy && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y][x - i] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y][x - i] == iEnemy && x - i >= 0) {
						mBoard[y][x - i] = myColor;
						i++;
					}
				}
			}
		}
	}
	//North West
	if (y > 0 && x > 0){	//If the position is not on the border
		if (mBoard[y - 1][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y - i][x - i] == iEnemy && y - i >= 0 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y - i][x - i] == mBoard[y][x]){
				result = true; 
				if (!bMode) {
					i = 0;
					while (mBoard[y - i][x - i] == iEnemy && y - i >= 0 && x - i >= 0) {
						mBoard[y - i][x - i] = myColor;
						i++;
					}
				}
			}
		}
	}
	bMode = true;
	return result;
}