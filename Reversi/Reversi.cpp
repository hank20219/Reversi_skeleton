#include "Reversi.h"

Reversi::Reversi(void)
{
	init();
}


Reversi::~Reversi(void)
{
}

void Reversi::init(void){
	for (int i = 0; i < 8; i++){ //intializing board
		for (int j = 0; j < 8; j++){
			switch (i)
			{
			case 3:
				if ( j = 3 )
				{
					mBoard[i][j] = eBLACK;
				}
				else if( j = 4 )
				{
					mBoard[i][j] = eWHITE;
				}
				
			case 4:
				if (j = 3)
				{
					mBoard[i][j] = eWHITE;
				}
				else if (j = 4)
				{
					mBoard[i][j] = eBLACK;
				}
			default:
				mBoard[i][j] = eEMPTY;
				break;
			}
		}
	}
}

bool Reversi::isBW(void){
	if (isPass()){ bBW = !bBW; }
	return bBW;
}

bool Reversi::isEnd(void){
	int countSlots = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (mBoard[i][j] == eEMPTY){ countSlots++; }
		}
	}
	if (countSlots == 0){ return true; }
	else { return false; }
}

bool Reversi::isPass(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (moveAnalyze(i, j)){
				return true;
			}
		}
	}
	return false;
}

void Reversi::setBW(int x, int y){
	if (bBW){ mBoard[x][y] = eBLACK; }
	else { mBoard[x][y] = eWHITE; }
}

int Reversi::getBW(int x, int y){
	return mBoard[x][y];
}

bool Reversi::moveAnalyze(int x, int y){
	bool result = false; //Legal = true; Illegal = false; 
	int iEnemy = eEMPTY; //Enemy's color
	if (bBW){ iEnemy = eWHITE; }
	else { iEnemy = eBLACK; }
	//Check 8 directions if the set can be set on the coordinate
	//North
	if (y > 0){	//If the position is not on the border
		if (mBoard[x][y-1] == iEnemy){
			int i = 1;
			while (mBoard[x][y-i] == iEnemy && y - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[x][y - i] == mBoard[x][y]){ result = true; }
		}
	}
	//North East
	if (y > 0 && x < 7){	//If the position is not on the border
		if (mBoard[x + 1][y - 1] == iEnemy){
			int i = 1;
			while (mBoard[x + i][y - i] == iEnemy && y - i >= 0 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[x + i][y - i] == mBoard[x][y]){ result = true; }
		}
	}
	//East
	if (x < 7){	//If the position is not on the border
		if (mBoard[x + 1][y] == iEnemy){
			int i = 1;
			while (mBoard[x + i][y] == iEnemy && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[x + i][y] == mBoard[x][y]){ result = true; }
		}
	}
	//South East
	if (y < 7 && x < 7){	//If the position is not on the border
		if (mBoard[x + 1][y + 1] == iEnemy){
			int i = 1;
			while (mBoard[x + i][y + i] == iEnemy && y + i <= 7 && x + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[x + i][y + i] == mBoard[x][y]){ result = true; }
		}
	}
	//South
	if (y < 7){	//If the position is not on the border
		if (mBoard[x][y + 1] == iEnemy){
			int i = 1;
			while (mBoard[x][y + i] == iEnemy && y + i <= 7){
				i++;
			}
			if (i != 0 && mBoard[x][y + i] == mBoard[x][y]){ result = true; }
		}
	}
	//South West
	if (y < 7 && x > 0){	//If the position is not on the border
		if (mBoard[x - 1][y + 1] == iEnemy){
			int i = 1;
			while (mBoard[x - i][y + i] == iEnemy && y + i <= 7 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[x - i][y + i] == mBoard[x][y]){ result = true; }
		}
	}
	//West
	if (x > 0){	//If the position is not on the border
		if (mBoard[x - 1][y] == iEnemy){
			int i = 1;
			while (mBoard[x - i][y] == iEnemy && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[x - i][y] == mBoard[x][y]){ result = true; }
		}
	}
	//North West
	if (y > 0 && x > 0){	//If the position is not on the border
		if (mBoard[x - 1][y - 1] == iEnemy){
			int i = 1;
			while (mBoard[x - i][y - i] == iEnemy && y - i >= 0 && x - i >= 0){
				i++;
			}
			if (i != 0 && mBoard[x - i][y - i] == mBoard[x][y]){ result = true; }
		}
	}
	return result;
}