#include "typedefs.h"
int main() {
    piece board[8][8];
    defaultBoard(board);
    printBoard(board);
    cout << endl;
    for(int i = 0; i < 300; i++) {
        if(1==1) {
            pieceMove m;
            moveAndScore a;
            a.m = m;
            a.score = -100000000;
            moveAndScore b;
            b.m = m;
            b.score = 100000000;
            moveAndScore bestMove = minimax(board, m, 0, i%2==0 ? 1 : 0, a, b);
            mutateBoard(board, bestMove.m);
            printBoard(board);
            cout << endl;
        } else {
            pieceMove m;
            cin >> m.originX >> m.originY >> m.destX >> m.destY;
            mutateBoard(board, m);
            printBoard(board);
            cout << endl;
        }
    }
    return 0;
}

moveAndScore minimax(piece board[8][8], pieceMove last, int depth, int isMaximizing, moveAndScore alpha, moveAndScore beta) {
    if(depth == 6) {
        moveAndScore best;
        best.m = last;
        best.score = scorePosition(board);
        return best;
    }
    if(isMaximizing) {
        moveAndScore best;
        best.score = -1000000000;
        best.m = pieceMove{0,0,0,0};

        vector<pieceMove> moves;
        validMoves(board, 1, moves);
        if(moves.empty()) {
            return best;
        }
        best.m = moves[0];
        for(pieceMove m : moves) {
            piece newBoard[8][8];
            copyBoard(board, newBoard);
            mutateBoard(newBoard, m);
            if (inCheck(newBoard, 1)) continue;
            moveAndScore value = minimax(newBoard, m, depth + 1, 0, alpha, beta);
            if(value.score > best.score) {
                best.score = value.score;
                best.m = m;
            }
            alpha = (alpha.score > best.score ? alpha : best);
            if(beta.score <= alpha.score)
                break;
        }
        return best;

    } else {
        moveAndScore best;
        best.score = 1000000000;
        best.m = pieceMove{0,0,0,0};

        vector<pieceMove> moves;
        validMoves(board, 0, moves);
        if(moves.empty()) {
            return best;
        }
        best.m = moves[0];
        for(pieceMove m : moves) {
            piece newBoard[8][8];
            copyBoard(board, newBoard);
            mutateBoard(newBoard, m);
            if (inCheck(newBoard, 0)) continue;
            moveAndScore value = minimax(newBoard, m, depth + 1, 1, alpha, beta);
            if(value.score < best.score) {
                best.score = value.score;
                best.m = m;
            }
            beta = (beta.score <= best.score ? beta : best);
            if(beta.score <= alpha.score)
                break;
        }
        return best;
    }
}