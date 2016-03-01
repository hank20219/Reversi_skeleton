#pragma once
class Reversi{
	private:
		
		//bool bMode; // Check mode:true, Set Mode:false;
		
		
	public:
		enum {eEMPTY, eBLACK, eWHITE};
		int numWhite, numBlack;	//Count point
		int mBoard[8][8];
		/*//////////////Board Form//////////////////////////
		1 2 3 4 5 6 7 8   Y
		A 0 0 0 0 0 0 0 0 | 0
		B 0 0 0 0 0 0 0 0 | 1
		C 0 0 0 0 0 0 0 0 | 2
		D 0 0 0 1 2 0 0 0 | 3
		E 0 0 0 2 1 0 0 0 | 4
		F 0 0 0 0 0 0 0 0 | 5
		G 0 0 0 0 0 0 0 0 | 6
		H 0 0 0 0 0 0 0 0 | 7
		- - - - - - - - -
		X 0 1 2 3 4 5 6 7
		//////////////////////////////////////////////////*/
		int numRecord = 0; // The number of records
		int curRecord = 0; // The index of current record
		int stepRecord[64][8][8]; //Remeber All steps
		char mArry[64];//Check whose turn in record
		bool bBW; // B:true, W:false (Check whose turn now)
		bool isPassed;  //Check if passed twice 
		void init();	//Initializing the game(include restart)
		bool isEnd();	//Check if game is end 
		bool isBW();	//Check whose turn now
		bool isPass();	//Check if player needs to pass the turn (use moveAnalyze, bMode = true)
		void setBW(int x, int y);	//Set chess on the board
		int getBW(int x, int y);	//Get chess from the board
		bool moveAnalyze(int x, int y); //Analyzes the move
		int chkBoard[8][8];
		void Undo(void);
		void Redo(void);
		
		////Function usage(in order):
		//1.Game start: init()
		//2.Check whose turn(Black first): isBW()
		//3.Check if the game is end: isEnd()
		//4.Check if player needs to pass the turn: isPass()
		//5.Set chess: setBW()
		//Loop 2-5

		Reversi(void);
		~Reversi(void);
};