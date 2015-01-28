/*
----------------------------------
	~Moosey Chess Engine~
	      movegen.cpp
----------------------------------
*/

#include "movegen.h"
#include "board.h"
#include "pieces.h"
#include "legal.h"

void generateCompleteMoveLists() {	
	for (int i = wqR; i <= bPh; i++)
		generateMoveListFor(i);
	whiteMoveList.clear();
	blackMoveList.clear();
	for (int i = wqR; i <= wPh; i++) {
		for (int j = 0; j < piece[i].moveListSize; j++) 
			if (piece[i].moveList[j] != null)
				whiteMoveList.push_back(piece[i].moveList[j]);
	}
	for (int i = bqR; i <= bPh; i++) {
		for (int j = 0; j < piece[i].moveListSize; j++) 
			if (piece[i].moveList[j] != null)
				blackMoveList.push_back(piece[i].moveList[j]);
	}
}

void generateMoveListFor(int p) {
	int counter = 0;
	
	if (piece[p].value == R_VAL)		generateHozMoves(p, counter);
	else if (piece[p].value == B_VAL)	generateDiagMoves(p, counter);
	else if (piece[p].value == N_VAL)	generateKnightMoves(p, counter);
	else if (piece[p].value == Q_VAL) { 
		generateHozMoves(p, counter);
		generateDiagMoves(p, counter);
	}
	else if (piece[p].value == K_VAL)	generateKingMoves(p, counter);
	else if (piece[p].value == P_VAL)	generatePawnMoves(p, counter);
	for (int i = counter; i < piece[p].moveListSize; i++) //Empty the rest of the moveList
		piece[p].moveList[i] = 0;
}

void generateHozMoves(int p, int& counter) {
	bool side = (p <= wPh);
	int d, i, posIndex;
	int startPiece = 0+(15*!side), endPiece = 31-(15*side), enemyStartPiece = 0+(16*side), enemyEndPiece = 15+(16*side);

	for (int c = 1; c <= 4; c++) {
		d = (c==1) ? -1 : (c==2) ? 1 : (c==3) ? -8 : 8;
		i = 1;
		posIndex = piece[p].pos+d*i;
		
		while (((posIndex-1)/8 == (piece[p].pos-1)/8) || ((posIndex)%8 == (piece[p].pos)%8)) { 
                        if (posIndex < 1 || posIndex > 64 || (board64[posIndex] >= startPiece && board64[posIndex] <= endPiece)) break;
                        
			if (legalMove(piece[p].pos, posIndex, side)) {
				//cout << "Moving from " << piece[p].pos << " to " << posIndex << " is legal as " << side << endl;
				piece[p].moveList[counter] = posIndex;
                        	counter++;
			}
			i++;
                        if (board64[posIndex] >= enemyStartPiece && board64[posIndex] <= enemyEndPiece) break;
                        posIndex = piece[p].pos+d*i;
                }
	}

}


void generateDiagMoves(int p, int& counter) {
	bool side = (p <= wPh);
	int d, i, posIndex;
	int startPiece = 0+(15*!side), endPiece = 31-(15*side), enemyStartPiece = 0+(16*side), enemyEndPiece = 15+(16*side);

	for (int c = 1; c <= 4; c++) {
		d = (c==1) ? -9 : (c==2) ? -7 : (c==3) ? 9 : 7;
		i = 1;
		posIndex = piece[p].pos+d*i;
		
		while (((from64(posIndex) - from64(piece[p].pos))%11 == 0 || (from64(posIndex) - from64(piece[p].pos))%9 == 0)) { 
                        if (posIndex < 1 || posIndex > 64 || (board64[posIndex] >= startPiece && board64[posIndex] <= endPiece)) break;
                        if (legalMove(piece[p].pos, posIndex, side)) {
				piece[p].moveList[counter] = posIndex;
                        	counter++;
			}
			i++;
                        if (board64[posIndex] >= enemyStartPiece && board64[posIndex] <= enemyEndPiece) break;
                        posIndex = piece[p].pos+d*i;
                }
	}
}

void generateKnightMoves(int p, int& counter) {
	bool side = (p <= wPh);
	int extra;
	for (int i = 1; i <= 8; i++) {
		extra = i==1 ? 8 : (i==2 ? -8 : (i==3 ? 12 : (i==4 ? -12 : (i==5 ? 19 : (i==6 ? -19 : (i==7 ? 21 : -21))))));
		if (legalMove(piece[p].pos, to64(from64(piece[p].pos) + extra), side)) {
			piece[p].moveList[counter] = to64(from64(piece[p].pos) + extra);
			counter++;
		}
	}
}

void generateKingMoves(int p, int& counter) {
	bool side = (p <= wPh);
	int extra;
        for (int i = 1; i <= 8; i++) {
                extra = i==1 ? 1 : (i==2 ? -1 : (i==3 ? 10 : (i==4 ? -10 : (i==5 ? 11 : (i==6 ? -11 : (i==7 ? 9 : -9))))));
                if (legalMove(piece[p].pos, to64(from64(piece[p].pos)+extra), side)) {
                        piece[p].moveList[counter] = to64(from64(piece[p].pos) + extra);
                        counter++;
                }
        }

}

void generatePawnMoves(int p, int& counter) {
	bool side = (p <= wPh);
	int extra;
        for (int i = 1; i <= 4; i++) {
                extra = i==1 ? 8 : (i==2 ? 16 : (i==3 ? 7 : 9));
                if (legalMove(piece[p].pos, piece[p].pos+extra, side)) {
                        piece[p].moveList[counter] = piece[p].pos + extra;
                        counter++;
                }
        }
}