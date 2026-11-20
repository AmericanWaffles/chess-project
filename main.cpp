#include "typedefs.h"
int main() {
    piece* board[8][8];
    defaultBoard(board);
    printBoard(board);
    cout << endl;
    vector<pieceMove> whiteMoves;
    validMoves(board, 1, whiteMoves);
    for(pieceMove m : whiteMoves) {
        piece* newBoard[8][8];
        copyBoard(board, newBoard);
        cout << m.originX << "," << m.originY << "->" << m.destX << "," << m.destY << endl;
        mutateBoard(newBoard, m);
        printBoard(newBoard);
    }
    return 0;
}

pieceMove bestMove(piece* board[8][8], int turnColor, int depth, int alpha, int beta) {
    pieceMove best;
    int bestFoundMoveScore = turnColor == 0 ? 1000000 : -1000000;
    vector<pieceMove> moves;
    validMoves(board, turnColor, moves);
    for(pieceMove m : moves) {
        piece* newBoard[8][8];
        copyBoard(board, newBoard);
        mutateBoard(newBoard, m);
        int score = scorePosition(newBoard);
        if(turnColor == 1) { //white to move, maximizer
            if(score > bestFoundMoveScore) {
                best = m;
                bestFoundMoveScore = score;
            }
        } else { //black to move, minimizer
            if(score < bestFoundMoveScore) {
                best = m;
                bestFoundMoveScore = score;
            }
        }
    }
    if(depth == 4) {
        return best;
    }

}