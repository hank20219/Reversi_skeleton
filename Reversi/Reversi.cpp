#include "Reversi.h"
#include <iostream>
Reversi::Reversi(void)
{
	for (int i = 0; i < 8; i++) { //intializing board
		for (int j = 0; j < 8; j++) {
			mBoard[j][i] = eEMPTY;
			chkBoard[j][i] = 0;
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
	bool bPass = true;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			chkBoard[j][i] = 0;
			if (moveAnalyze(j, i)){
				bPass = false;
				chkBoard[j][i] = 1;
			}
		}
	}
	return bPass;
}

void Reversi::setBW(int x, int y){
	int iEnemy = eEMPTY; //Enemy's color
	int myColor = eEMPTY; //My color
	if (bBW){ 
		mBoard[y][x] = eBLACK;
		iEnemy = eWHITE;
		myColor = eBLACK;
	}
	else { 
		mBoard[y][x] = eWHITE; 
		iEnemy = eBLACK; 
		myColor = eWHITE;
	}
	//North
	if (mBoard[y - 1][x] == iEnemy) {
		int i = 1;
		while (mBoard[y - i][x] == iEnemy && y - i >= 0) {
			i++;
		}
		if (i != 0 && mBoard[y - i][x] == myColor) {
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
		if (i != 0 && mBoard[y - i][x + i] == myColor) {
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
		if (i != 0 && mBoard[y][x + i] == myColor) {
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
		if (i != 0 && mBoard[y + i][x + i] == myColor) {
			bMode = true;
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
		if (i != 0 && mBoard[y + i][x] == myColor) {
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
		if (i != 0 && mBoard[y + i][x - i] == myColor) {
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
		if (i != 0 && mBoard[y][x - i] == myColor) {
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
		if (i != 0 && mBoard[y - i][x - i] == myColor) {
			for (int j = 0; j < i; j++) {
				mBoard[y - j][x - j] = myColor;
			}
		}
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
	if (mBoard[y-1][x] == iEnemy){
			int i = 1;
			while (mBoard[y-i][x] == iEnemy && y - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y - i][x] == myColor){
				result = true; 
			}
	}
	//North East
	if (mBoard[y - 1][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y - i][x + i] == iEnemy && y - i >= 0 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y - i][x + i] == myColor){
				result = true; 
			}
	}
	//East
	if (mBoard[y][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y][x + i] == iEnemy && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y][x + i] == myColor){
				result = true;
			}
	}
	//South East
	if (mBoard[y + 1][x + 1] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x + i] == iEnemy && y + i <= 7 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y + i][x + i] == myColor){
				result = true; 
			}
	}
	//South
	if (mBoard[y + 1][x] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x] == iEnemy && y + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[y + i][x] == myColor){
				result = true; 
			}
	}
	//South West
	if (mBoard[y + 1][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y + i][x - i] == iEnemy && y + i <= 7 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y + i][x - i] == myColor){
				result = true; 
			}
	}
	//West
	if (mBoard[y][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y][x - i] == iEnemy && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y][x - i] == myColor){
				result = true; 
			}
	}
	//North West
	if (mBoard[y - 1][x - 1] == iEnemy){
			int i = 1;
			while (mBoard[y - i][x - i] == iEnemy && y - i >= 0 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[y - i][x - i] == myColor){
				result = true; 
			}
	}
	
	return result;
}