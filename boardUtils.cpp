#include "typedefs.h"
void mutateBoard(piece* board[8][8], pieceMove m) {
    delete board[m.destY][m.destX];
    board[m.destY][m.destX] = board[m.originY][m.originX];
    piece* blank = new piece();
    blank->type = pieceTypes.empty;
    blank->color = 2; 
    board[m.originY][m.originX] = blank;
}
void defaultBoard(piece* board[8][8]) { //resets the board back to the starting position
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == 0) {
                if(j == 0 || j == 7) {
                    piece* rook = new piece();
                    rook->type = pieceTypes.rook;
                    rook->color = 0;
                    board[i][j] = rook;
                }
                if(j == 1 || j == 6) {
                    piece* knight = new piece();
                    knight->type = pieceTypes.knight;
                    knight->color = 0;
                    board[i][j] = knight;
                }
                if(j == 2 || j == 5) {
                    piece* bishop = new piece();
                    bishop->type = pieceTypes.bishop;
                    bishop->color = 0;
                    board[i][j] = bishop;
                }
                if(j == 3) {
                    piece* queen = new piece();
                    queen->type = pieceTypes.queen;
                    queen->color = 0;
                    board[i][j] = queen;
                }
                if(j == 4) {
                    piece* king = new piece();
                    king->type = pieceTypes.king;
                    king->color = 0;
                    board[i][j] = king;
                }
            }
            if(i == 1) {
                piece* pawn = new piece();
                pawn->type = pieceTypes.pawn;
                pawn->color = 0;
                board[i][j] = pawn;
            }
            if(i>1 && i < 6) {
                piece* blank = new piece();
                blank->type = pieceTypes.empty;
                blank->color = 2;
                board[i][j] = blank;  
            }
            if(i == 7) {
                if(j == 0 || j == 7) {
                    piece* rook = new piece();
                    rook->type = pieceTypes.rook;
                    rook->color = 1;
                    board[i][j] = rook;
                }
                if(j == 1 || j == 6) {
                    piece* knight = new piece();
                    knight->type = pieceTypes.knight;
                    knight->color = 1;
                    board[i][j] = knight;
                }
                if(j == 2 || j == 5) {
                    piece* bishop = new piece();
                    bishop->type = pieceTypes.bishop;
                    bishop->color = 1;
                    board[i][j] = bishop;
                }
                if(j == 3) {
                    piece* queen = new piece();
                    queen->type = pieceTypes.queen;
                    queen->color = 1;
                    board[i][j] = queen;
                }
                if(j == 4) {
                    piece* king = new piece();
                    king->type = pieceTypes.king;
                    king->color = 1;
                    board[i][j] = king;
                }
            }
            if(i == 6) {
                piece* pawn = new piece();
                pawn->type = pieceTypes.pawn;
                pawn->color = 1;
                board[i][j] = pawn;
            }
        }
    }
}
void printBoard(piece* board[8][8]) {
    string pieceNames[8] = {" ", "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654", " "};
    for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                cout << ((i+j)%2 == 0 ? "\x1b[107m" : "\x1b[100m" ); //background color for the squares.
                cout << (board[i][j]-> color == 0 ? "\x1b[91m" : "\x1b[94m");
                cout << pieceNames[board[i][j]->type];
                cout << " "; //height > char width, so print two spaces.
            }
            cout << "\x1b[0m" << endl;
        }
}
void copyBoard(piece* board[8][8], piece* newBoard[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            piece* tmp = new piece();
            tmp->type = board[i][j]->type;
            tmp->color = board[i][j]->color;
            newBoard[i][j] = tmp;
        }
    }
}

int scorePosition(piece* board[8][8]) {
    int score = 0;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {
            if (board[i][j]->color == 0) {
                // score += sqrt(pow((i-whiteKingPos.originY), 2) + pow((j-whiteKingPos.originX), 2));
                score -= i;
                switch(board[i][j]->type) {
                    case pieceTypes.pawn:
                        score -= 10;
                        break;
                    case pieceTypes.knight:
                        score -= 30;
                        break;
                    case pieceTypes.bishop:
                        score -= 30;
                        break;
                    case pieceTypes.rook:
                        score -= 50;
                        break;
                    case pieceTypes.queen:
                        score -= 90;
                        break;
                    case pieceTypes.king:
                        score -= 9000000;
                        score += 90*i;
                        break;
                }
            } else if (board[i][j]->color == 1) {
                // score -= sqrt(pow((i-blackKingPos.originY), 2) + pow((j-blackKingPos.originX), 2));
                score += (7-i);
                switch(board[i][j]->type) {
                    case pieceTypes.pawn:
                        score += 10;
                        break;
                    case pieceTypes.knight:
                        score += 30;
                        break;
                    case pieceTypes.bishop:
                        score += 30;
                        break;
                    case pieceTypes.rook:
                        score += 50;
                        break;
                    case pieceTypes.queen:
                        score += 90;
                        break;
                    case pieceTypes.king:
                        score += 9000000;
                        score -= 90*(7-i);
                        break;
                }
            }
        }
    return score;
}