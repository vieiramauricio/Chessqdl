#include "movegen.hpp"
#include "bitboard.hpp"
#include "utils.hpp"

#include <cmath>


using namespace chessqdl;


/**
 * @details shifts bitboard northwest. E.g
 * 0 0 0	1 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthWest(U64 bitboard) {
	return (bitboard << noWe) & notHFile;
}


/**
 * @details shifts bitboard north. E.g
 * 0 0 0	0 1 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorth(U64 bitboard) {
	return bitboard << nort;
}


/**
 * @details shifts bitboard northeast. E.g
 * 0 0 0	0 0 1
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthEast(U64 bitboard) {
	return (bitboard << noEa) & notAFile;
}


/**
 * @details shifts bitboard east. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 1
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftEast(U64 bitboard) {
	return (bitboard << east) & notAFile;
}


/**
 * @details shifts bitboard southeast. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 1
 */
U64 MoveGenerator::shiftSouthEast(U64 bitboard) {
	return (bitboard >> -soEa) & notAFile;
}


/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 1 0
 */
U64 MoveGenerator::shiftSouth(U64 bitboard) {
	return bitboard >> -sout;
}


/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	1 0 0
 */
U64 MoveGenerator::shiftSouthWest(U64 bitboard) {
	return (bitboard >> -soWe) & notHFile;
}


/**
 * @details shifts bitboard west. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 1 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftWest(U64 bitboard) {
	return (bitboard >> -west) & notHFile;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soutOccl(U64 gen, U64 pro) {
	gen |= pro & (gen >> 8);
	pro &= (pro >> 8);
	gen |= pro & (gen >> 16);
	pro &= (pro >> 16);
	gen |= pro & (gen >> 32);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::nortOccl(U64 gen, U64 pro) {
	gen |= pro & (gen << 8);
	pro &= (pro << 8);
	gen |= pro & (gen << 16);
	pro &= (pro << 16);
	gen |= pro & (gen << 32);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::eastOccl(U64 gen, U64 pro) {
	pro &= notAFile;
	gen |= pro & (gen << 1);
	pro &= (pro << 1);
	gen |= pro & (gen << 2);
	pro &= (pro << 2);
	gen |= pro & (gen << 4);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::noEaOccl(U64 gen, U64 pro) {
	pro &= notAFile;
	gen |= pro & (gen << 9);
	pro &= (pro << 9);
	gen |= pro & (gen << 18);
	pro &= (pro << 18);
	gen |= pro & (gen << 36);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soEaOccl(U64 gen, U64 pro) {
	pro &= notAFile;
	gen |= pro & (gen >> 7);
	pro &= (pro >> 7);
	gen |= pro & (gen >> 14);
	pro &= (pro >> 14);
	gen |= pro & (gen >> 28);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::westOccl(U64 gen, U64 pro) {
	pro &= notHFile;
	gen |= pro & (gen >> 1);
	pro &= (pro >> 1);
	gen |= pro & (gen >> 2);
	pro &= (pro >> 2);
	gen |= pro & (gen >> 4);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soWeOccl(U64 gen, U64 pro) {
	pro &= notHFile;
	gen |= pro & (gen >> 9);
	pro &= (pro >> 9);
	gen |= pro & (gen >> 18);
	pro &= (pro >> 18);
	gen |= pro & (gen >> 36);
	return gen;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::noWeOccl(U64 gen, U64 pro) {
	pro &= notHFile;
	gen |= pro & (gen << 7);
	pro &= (pro << 7);
	gen |= pro & (gen << 14);
	pro &= (pro << 14);
	gen |= pro & (gen << 28);
	return gen;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for a given color of pawn pieces.
 */
U64 MoveGenerator::getPawnMoves(const BitbArray &bitboard, enumColor color) {
	if (color == nWhite) {
		U64 pawns = bitboard[nPawn] & bitboard[nWhite];        // every white pawn on the board

		U64 attacks = shiftNorthEast(pawns) | shiftNorthWest(pawns);                // theoretical possible attacks
		attacks &= bitboard[nBlack];                                    // real possible attacks (it's only possible to attack if there is a enemy piece)

		U64 moves = shiftNorth(pawns);
		moves &= ~bitboard[nColor];                                    // can't move if there is a piece blocking the way

		// If pawn is on its initial position, give the possibility to "move twice"
		U64 aux = moves;
		aux = aux << 40;
		aux = aux >> 56;
		aux = aux << 16;

		moves |= shiftNorth(aux);
		moves &= ~bitboard[nColor];

		return attacks | moves;														// pseudo-legal moves (capture and move)

	} else if (color == nBlack) {
		U64 pawns = bitboard[nPawn] & bitboard[nBlack];

		U64 attacks = shiftSouthWest(pawns) | shiftSouthEast(pawns);
		attacks &= bitboard[nWhite];

		U64 moves = shiftSouth(pawns);
		moves &= ~bitboard[nColor];

		// If pawn is on its initial position, give the possibility to "move twice"
		U64 aux = moves;
		aux = aux << 16;
		aux = aux >> 56;
		aux = aux << 40;

		moves |= shiftSouth(aux);
		moves &= ~bitboard[nColor];


		return attacks | moves;
	}
	else
		return getPawnMoves(bitboard, nBlack) | getPawnMoves(bitboard, nWhite);
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for a given king. "Moves" the king in every direction and checks for collisions. Return the moves that do not collide with pieces of the same color.
 * @todo Implement castle as a pseudo-legal move?
 */
U64 MoveGenerator::getKingMoves(const BitbArray &bitboard, enumColor color) {
	U64 king = bitboard[nKing] & bitboard[color];

	U64 moves = shiftNorth(king) | shiftNorthEast(king) | shiftEast(king) | shiftSouthEast(king) | shiftSouth(king) | shiftSouthWest(king) | shiftWest(king) | shiftNorthWest(king);
	U64 validSquares = ~bitboard[color];

	return moves & validSquares;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for knights of a given color.
 * Every possible theoretical move is accounted for, but only the ones that do not collide with allied pieces are returned.
 */
U64 MoveGenerator::getKnightMoves(const BitbArray &bitboard, chessqdl::enumColor color) {
	U64 knights = bitboard[nKnight] & bitboard[color];

	if (color == nColor)
		return getKnightMoves(bitboard, nBlack) | getKnightMoves(bitboard, nWhite);

	U64 WWN = shiftNorthWest(shiftWest(knights));            // west west north
	U64 WNN = shiftNorthWest(shiftNorth(knights));            // west north north
	U64 ENN = shiftNorthEast(shiftNorth(knights));        // east north north
	U64 EEN = shiftNorthEast(shiftEast(knights));            // east east north

	U64 EES = shiftSouthEast(shiftEast(knights));			// east east south
	U64 ESS = shiftSouthEast(shiftSouth(knights));			// east south south
	U64 WSS = shiftSouthWest(shiftSouth(knights));		    // west south south
	U64 WWS = shiftSouthWest(shiftWest(knights));			// west west south

	U64 moves =  WWN | WNN | ENN | EEN | EES | ESS | WSS | WWS;

    U64 notAlly = ~bitboard[color];

    return moves & notAlly;								// moves and every square that doesn't contain an piece of the same color
}

/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
U64 MoveGenerator::getBishopMoves(const BitbArray &bitboard, enumColor color, enumPiece piece) {
	U64 bishops = bitboard[piece] & bitboard[color];
	U64 empty = ~bitboard[nColor];

	if (color == nColor)
		return getBishopMoves(bitboard, nWhite, piece) | getBishopMoves(bitboard, nBlack, piece);

	U64 noEaOcc = noEaOccl(bishops, empty);
	U64 soEaOcc = soEaOccl(bishops, empty);
	U64 noWeOcc = noWeOccl(bishops, empty);
	U64 soWeOcc = soWeOccl(bishops, empty);

	U64 noEaAttacks = shiftNorthEast(noEaOcc);
	U64 soEaAttacks = shiftSouthEast(soEaOcc);
	U64 noWeAttacks = shiftNorthWest(noWeOcc);
	U64 soWeAttacks = shiftSouthWest(soWeOcc);

	U64 attacks = noEaAttacks | soEaAttacks | noWeAttacks | soWeAttacks;
	attacks &= ~bitboard[color]; // Attacks are only valid if the piece is an enemy piece
	U64 moves = noEaOcc | soEaOcc | noWeOcc | soWeOcc;
	moves &= ~bitboard[piece]; // "Moving" without leaving the square is invalid

	return moves | attacks;
}


/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
U64 MoveGenerator::getRookMoves(const BitbArray &bitboard, enumColor color, enumPiece piece) {
	U64 rooks = bitboard[piece] & bitboard[color];
	U64 empty = ~bitboard[nColor];

	if (color == nColor)
		return getRookMoves(bitboard, nWhite, piece) | getRookMoves(bitboard, nBlack, piece);

	U64 soutOcc = soutOccl(rooks, empty);
	U64 nortOcc = nortOccl(rooks, empty);
	U64 eastOcc = eastOccl(rooks, empty);
	U64 westOcc = westOccl(rooks, empty);

	U64 soutAttacks = shiftSouth(soutOcc);
	U64 nortAttacks = shiftNorth(nortOcc);
	U64 eastAttacks = shiftEast(eastOcc);
	U64 westAttacks = shiftWest(westOcc);

	U64 attacks = soutAttacks | nortAttacks | eastAttacks | westAttacks;
	attacks &= ~bitboard[color]; // Attacks are only valid if the piece is an enemy piece
	U64 moves = soutOcc | nortOcc | eastOcc | westOcc;
	moves &= ~bitboard[piece]; // "Moving" without leaving the square is invalid

	return moves | attacks;
}


/**
 * @details Makes use of the implementation of bishop and rooks move generation.
 */
U64 MoveGenerator::getQueenMoves(const BitbArray &bitboard, enumColor color) {
	if (color == nColor)
		return getQueenMoves(bitboard, nWhite) | getQueenMoves(bitboard, nBlack);

	return getBishopMoves(bitboard, color, nQueen) | getRookMoves(bitboard, color, nQueen);
}


/**
 * @details Identifies all pawns that can promote on next move and generates a list with all possible promotions. Also removes the option to just move without promoting
 */
std::vector<std::string> MoveGenerator::getPawnPromotions(U64 &pawnMoves, uint64_t fromPos) {
	U64 whitePromotions = pawnMoves & U64(0xffL << 56); // White pawn moves that are promotions
	U64 blackPromotions = pawnMoves & U64(0xffL); // Black pawn moves that are promotions

	// Removes the promoting pawns from standard moves
	pawnMoves ^= whitePromotions;
	pawnMoves ^= blackPromotions;

	// Promotions as uint64_t
	uint64_t uWhitePromotions = whitePromotions.to_ullong();
	uint64_t uBlackPromotions = blackPromotions.to_ullong();

	int i;
	uint64_t toPos;
	std::string move;
	std::vector<std::string> promotions;

	while (uWhitePromotions) {
		i = leastSignificantSetBit(uWhitePromotions);
		toPos = 1L << i;
		uWhitePromotions ^= toPos;
		move = moveName(fromPos, toPos);
		promotions.push_back(move + "n"); // Promote to Knight
		promotions.push_back(move + "b"); // Promote to Bishop
		promotions.push_back(move + "r"); // Promote to Rook
		promotions.push_back(move + "q"); // Promote to Queen
	}

	while (uBlackPromotions) {
		i = leastSignificantSetBit(uBlackPromotions);
		toPos = 1l << i;
		uBlackPromotions ^= toPos;
		move = moveName(fromPos, toPos);
		promotions.push_back(move + "n"); // Promote to Knight
		promotions.push_back(move + "b"); // Promote to Bishop
		promotions.push_back(move + "r"); // Promote to Rook
		promotions.push_back(move + "q"); // Promote to Queen
	}

	return promotions;
}


/**
 * @details Iterates through all bitboards (from nPawn to nKing) generating moves for pieces one at a time. If there are 16 pawns on the board, this method will generate pawn moves 16 times, one for each individual pawn.
 * It does so for every type of piece on the board, and then returns a list with strings of all possible moves it has found.
 */
std::vector<std::string> MoveGenerator::getPseudoLegalMoves(const BitbArray &bitboard, enumColor color) {
	if (color == nColor) {
		std::vector<std::string> white = getPseudoLegalMoves(bitboard, nWhite);
		std::vector<std::string> black = getPseudoLegalMoves(bitboard, nBlack);

		// Concatenates both lists (inserts the black list on the end of white list)
		white.insert(white.end(), black.begin(), black.end());

		return white;
	}

	uint64_t fromPos, toPos;
	std::vector<std::string> moves;
	std::vector<std::string> promotions;

	BitbArray bitboardCopy = bitboard;

	for (int k = nPawn; k <= nKing; k++) {


		U64 pieces = bitboard[k];
		pieces &= bitboard[color];

		U64 pieceMoves;

		uint64_t upieces = pieces.to_ullong();

		int i, j;

		while (upieces) {
			// Get index of least significant set bit
			i = leastSignificantSetBit(upieces);
			upieces ^= (1L << i); // Reset bit

			bitboardCopy[k].reset();
			bitboardCopy[k].set(i);

			fromPos = 1L << i; // Original position

			switch (k) {
				case nPawn:
					pieceMoves = getPawnMoves(bitboardCopy, color);
					promotions = getPawnPromotions(pieceMoves, fromPos);
					if (!promotions.empty()) {
						moves.insert(moves.end(), promotions.begin(), promotions.end());
					}
					break;

				case nKnight:
					pieceMoves = getKnightMoves(bitboardCopy, color);
					break;

				case nBishop:
					pieceMoves = getBishopMoves(bitboardCopy, color);
					break;

				case nRook:
					pieceMoves = getRookMoves(bitboardCopy, color);
					break;

				case nQueen:
					pieceMoves = getQueenMoves(bitboardCopy, color);
					break;

				case nKing:
					pieceMoves = getKingMoves(bitboardCopy, color);
					break;
			}

			uint64_t umoves = pieceMoves.to_ullong();

			// Loops through all possible moves that the piece of type k at the i position can make and adds it to the list of moves
			while (umoves) {
				j = leastSignificantSetBit(umoves);
				umoves ^= (1L << j); // Reset bit
				toPos = 1L << j; // Target position

				moves.push_back(moveName(fromPos, toPos));
			}
		}
	}

	return moves;
}
