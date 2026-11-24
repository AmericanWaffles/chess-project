#include <string>
#include <iostream>
#include <vector>
#pragma once
using namespace std;
constexpr struct {int pawn = 1; int knight = 2; int bishop = 3; int rook = 4; int queen = 5; int king = 6; int empty = 7;} pieceTypes;
struct piece {int type; int color;};
struct pieceMove {int originX; int originY; int destX; int destY;};
int validMoves(piece* board[8][8], int turn, vector<pieceMove> &soFar);
void defaultBoard(piece* board[8][8]);
void mutateBoard(piece* board[8][8], pieceMove m);
void printBoard(piece* board[8][8]);
void copyBoard(piece* board[8][8], piece* newBoard[8][8]);
int scorePosition(piece* board[8][8]);
struct moveAndScore {
    pieceMove m;
    int score;
};
moveAndScore minimax(piece* board[8][8], pieceMove last, int depth, int isMaximizing, moveAndScore alpha, moveAndScore beta);