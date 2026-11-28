#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#pragma once
using namespace std;
constexpr struct {uint8_t pawn = 1; uint8_t knight = 2; uint8_t bishop = 3; uint8_t rook = 4; uint8_t queen = 5; uint8_t king = 6; uint8_t empty = 7;} pieceTypes;
struct piece {uint8_t type; uint8_t color;};
struct pieceMove {uint8_t originX; uint8_t originY; uint8_t destX; uint8_t destY;};
int validMoves(piece board[8][8], int turn, vector<pieceMove> &soFar);
void defaultBoard(piece board[8][8]);
void mutateBoard(piece board[8][8], pieceMove m);
void printBoard(piece board[8][8]);
void copyBoard(piece board[8][8], piece newBoard[8][8]);
int scorePosition(piece board[8][8]);
struct moveAndScore {
    pieceMove m;
    int score;
};
moveAndScore minimax(piece board[8][8], pieceMove last, int depth, int isMaximizing, moveAndScore alpha, moveAndScore beta);
bool inCheck(piece board[8][8], int turn);