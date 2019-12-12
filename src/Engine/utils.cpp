#include "utils.h"
#include "movegen.h"

#include <cmath>

using namespace chessqdl;

/**
 * @details The method only takes into account the LSB of \p position. Thus, if there is more than 1 bit set (or even 0) the return value will not be accurate.
 */
std::string chessqdl::posToStr(uint64_t pos) {

	// Least significant set bit
	pos &= -pos;

	// log2(pos) is the index of the bit that is set
	return mapPositions[log2(pos)];
}


/**
 * @details Performs an evaluation that takes into account the material balance and number of available moves.
 *
 * Piece value is as follows:
 * King   - 200
 * Queen  - 9
 * Rook   - 5
 * Bishop - 3
 * Knight - 3
 * Pawn   - 1
 *
 * @todo Count only legal moves
 */
int chessqdl::evaluateBoard(const U64 *board, enumColor color) {
	// King count
	int k = (board[nKing] & board[color]).count();
	int kPrime = board[nKing].count() - k;

	// Queen count
	int q = (board[nQueen] & board[color]).count();
	int qPrime = board[nQueen].count() - q;

	// Rook count
	int r = (board[nRook] & board[color]).count();
	int rPrime = board[nRook].count() - r;

	// Knight count
	int n = (board[nKnight] & board[color]).count();
	int nPrime = board[nKnight].count() - n;

	// Bishop count
	int b = (board[nBishop] & board[color]).count();
	int bPrime = board[nBishop].count() - b;

	// Pawn count
	int p = (board[nPawn] & board[color]).count();
	int pPrime = board[nPawn].count() - p;

	MoveGenerator gen;
	enumColor enemyColor = color == nWhite ? nBlack : nWhite;

	// Move count
	int m = gen.getPseudoLegalMoves(board, color).size();
	int mPrime = gen.getPseudoLegalMoves(board, enemyColor).size();

	int score = 200 * (k - kPrime) + 9 * (q - qPrime) + 5 * (r - rPrime) + 3 * (n - nPrime + b - bPrime) + (p - pPrime);
	score += 0.1 * (m - mPrime);

	//if (color == nBlack) score *= -1;

	return score;
}
