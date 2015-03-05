/*
----------------------------------
	~Moosey Chess Engine~
	      search.cpp
----------------------------------
*/

#include <ctime>
#include "search.h"
#include "board.h"
#include <iostream>
#include "display.h"

int nodes;
std::vector<int> finalPV;

int search(Board& b, int depth) {
	using std::vector;
	
	nodes = 0;
	const clock_t begin_time = clock();
	int bestMove = 0, bestScore = -99999, score;
	int mF, mT;
	int alpha = -99999, beta = 99999;
	vector<int> moveList;
	finalPV.clear();

	std::cout << "Current eval: " << b.eval() << '\n';
//	std::cout << "\n\n\n\nNEWSEARCH, BOT SEARCHING FOR: " << b.getSide() << "\n\n";
	b.generateMoveListFor(b.getSide(), moveList);
	b.checkCheckForBot(b.getSide(), moveList);
	b.orderMoveList(b.getSide(), moveList);

	for (int i = 0; i < (int)moveList.size(); i++) {
		//alpha = -99999;
		//beta = -alpha;
		//displayBoard(b);
		//SDL_Delay(100);
	
		mF = moveList[i]/100;
		mT = moveList[i]%100;
//		std::cout << "Searching ROOT " << i << " mF: " << mF << " mT: " << mT << '\n';
		b.setMove(mF, mT);
		b.movePiece();

		score = -alphaBeta(b, alpha, beta, depth-1, finalPV);

		if (score > bestScore) {
			bestScore = score;
			bestMove = mF*100 + mT;
			
//			std::cout << "NEW BEST SCORE IN ROOT: " << bestScore << '\n';;
		}
//		std::cout << "ROOT " << i << " score was " << score << '\n';


		b.unmovePiece();
		b.changeTurn();
		nodes++;
	}

	std::cout << "Best score : " << bestScore << " Best move : " << bestMove << '\n';
	std::cout << "Time elapsed: " << float(clock()-begin_time) / CLOCKS_PER_SEC << '\n';
	std::cout << "Nodes searched: " << nodes << '\n';
	std::cout << "Nodes/sec: " << nodes / (float(clock()-begin_time) / CLOCKS_PER_SEC) << '\n';

	std::cout << "Principal variation: \n";
	std::cout << intToSquare(bestMove/100) << " to " << intToSquare(bestMove%100) << '\n';
	for (int i = 0; i < (int)finalPV.size(); i++) {
		mF = finalPV[i]/100;
		mT = finalPV[i]%100;
		std::cout << intToSquare(mF) << " to " << intToSquare(mT) << '\n';
	}
	
	if (bestScore < -9999) std::cout << "BESTSCORE < -9999\n";
	if (bestMove == 0) std::cout << "BESTMOVE: 0\n";
	if (bestMove == 0) std::cout << "bestmove: 0\n";
	if (bestScore < -9999) bestMove = 0;
	return bestMove;
}

int alphaBeta(Board& b, int alpha, int beta, int depthLeft, std::vector<int> & PV) {
	using std::vector;

	int score;
	int mF, mT;
	vector<int> moveList;

	b.changeTurn();
	if (depthLeft) {
		b.generateMoveListFor(b.getSide(), moveList);
		b.checkCheckForBot(b.getSide(), moveList);
		b.orderMoveList(b.getSide(), moveList);
	}

	if (depthLeft == 0) {
//		std::cout << "Scoring... " << b.eval() << '\n';
		return b.eval();
	}

	for (int i = 0; i < (int)moveList.size(); i++) {
		vector<int> localPV;
		nodes++;

		mF = moveList[i]/100;
		mT = moveList[i]%100;
		//for (int i = 0; i <= depthLeft; i++) std::cout << '\t';
//		std::cout << "AB depth: " << depthLeft << " mF: " << mF << " mT: " << mT << '\n';
		b.setMove(mF, mT);
		b.movePiece();
		
		score = -alphaBeta(b, -beta, -alpha, depthLeft - 1, localPV);
		b.changeTurn();

		//for (int i = 0; i <= depthLeft; i++) std::cout << '\t';
//		std::cout << "score: " << score << '\n';
		if (score >= beta) {
			b.unmovePiece();
			return beta;
		}
		if (score > alpha) {
			alpha = score;
			PV.clear();
			PV.push_back(moveList[i]);
			std::copy(localPV.begin(), localPV.end(), back_inserter(PV));
		}

		b.unmovePiece();

	}
	
	return alpha;
}
