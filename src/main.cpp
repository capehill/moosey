/*
 ---------------------------------
	~Moosey Chess Engine~
	   By Chris Moutsos
	      main.cpp
 ---------------------------------
*/
/*
 *	Verify that en passants are on moveList
 * 	Promotions
 *	SDL
 *	FEN parsing
 *	Vectors for various member data of Board,
 *	in anticipation of the bot making multiple moves.
 *	Similarly, add vector of all moves made
 */

#include <iostream>
#include "board.h"
#include "display.h"
#include "input.h"

using namespace std;

int main() {
	bool exit = false;
	int mF = 0, mT = 0;
	Board board;
	displayBoard(board);

	while (!exit) {
		userInput(board, mF, mT);
		board.setMove(mF, mT);
		board.movePiece();
		board.changeTurn();
		displayBoard(board);
		board.moveInfo();
		board.generateMoveLists();

		if (board.checkCheck(board.getSide())) 
			exit = true;
	}

	return 0;
}
