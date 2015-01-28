/*
----------------------------------
	~Moosey Chess Engine~
	      board.h
----------------------------------
*/


/*
 * null square = 0
 * empty square = -1
 * invalid square = -99
 */

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <vector>

void emptyBoard();
void placePiecesDefault();		//Places all pieces default
void initializePieces(std::string FEN);	//Names & values all pieces
					//if FEN=="0", will placePiecesDefault
int to64(int x); 			//Converts x from 120 to 64 index
int from64(int x);			//Converts x from 64 to 120 index
//int from64(int x);			//Converts x from 64 to 120 index
std::string intToSquare(int square);	//Returns 'a1' for 1, ..., 'h8' for 64

void placePiece(int pieceNumber, int square);   //Puts piece at square,
						//and updates the boards

enum square_t { empty = -1, null = 0, invalid = -99,
                A1 = 1, B1, C1, D1, E1, F1, G1, H1,
                A2 = 9, B2, C2, D2, E2, F2, G2, H2,
                A3 = 17, B3, C3, D3, E3, F3, G3, H3,
                A4 = 25, B4, C4, D4, E4, F4, G4, H4,
                A5 = 33, B5, C5, D5, E5, F5, G5, H5,
                A6 = 41, B6, C6, D6, E6, F6, G6, H6,
                A7 = 49, B7, C7, D7, E7, F7, G7, H7,
                A8 = 57, B8, C8, D8, E8, F8, G8, H8
};
enum square2_t { _A1 = 21, _B1, _C1, _D1, _E1, _F1, _G1, _H1,
                 _A2 = 31, _B2, _C2, _D2, _E2, _F2, _G2, _H2,
                 _A3 = 41, _B3, _C3, _D3, _E3, _F3, _G3, _H3,
                 _A4 = 51, _B4, _C4, _D4, _E4, _F4, _G4, _H4,
                 _A5 = 61, _B5, _C5, _D5, _E5, _F5, _G5, _H5,
                 _A6 = 71, _B6, _C6, _D6, _E6, _F6, _G6, _H6,
                 _A7 = 81, _B7, _C7, _D7, _E7, _F7, _G7, _H7,
                 _A8 = 91, _B8, _C8, _D8, _E8, _F8, _G8, _H8
};

enum side_t { BLACK, WHITE, BOTH };

extern int ply, board120[120], board64[65];
extern std::vector<int> whiteMoveList, blackMoveList; 

#endif