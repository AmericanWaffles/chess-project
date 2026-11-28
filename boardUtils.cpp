#include "typedefs.h"
#include <cstring>
void mutateBoard(piece board[8][8], pieceMove m) {
    board[m.destY][m.destX].type = board[m.originY][m.originX].type;
    board[m.destY][m.destX].color = board[m.originY][m.originX].color;
    board[m.originY][m.originX].type = pieceTypes.empty;
    board[m.originY][m.originX].color = 2;
    if((m.destY == 0 || m.destY == 7) && board[m.destY][m.destX].type == pieceTypes.pawn)
        board[m.destY][m.destX].type = pieceTypes.queen;
}
void defaultBoard(piece board[8][8]) { //resets the board back to the starting position
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == 0) {
                if(j == 0 || j == 7) {
                    board[i][j].type = pieceTypes.rook;
                    board[i][j].color = 0;
                }
                if(j == 1 || j == 6) {
                    board[i][j].color = 0;
                    board[i][j].type = pieceTypes.knight;;
                }
                if(j == 2 || j == 5) {
                    board[i][j].type = pieceTypes.bishop;
                    board[i][j].color = 0;
                }
                if(j == 3) {
                    piece* queen = new piece();
                    board[i][j].type = pieceTypes.queen;
                    board[i][j].color = 0;
                }
                if(j == 4) {
                    board[i][j].type = pieceTypes.king;
                    board[i][j].color = 0;
                }
            }
            if(i == 1) {
                board[i][j].type = pieceTypes.pawn;
                board[i][j].color = 0;
            }
            if(i>1 && i < 6) {
                board[i][j].type = pieceTypes.empty;
                board[i][j].color = 2;
            }
            if(i == 7) {
                if(j == 0 || j == 7) {
                    board[i][j].type = pieceTypes.rook;
                    board[i][j].color = 1;
                }
                if(j == 1 || j == 6) {
                    board[i][j].type = pieceTypes.knight;
                    board[i][j].color = 1;
                }
                if(j == 2 || j == 5) {
                    board[i][j].type = pieceTypes.bishop;
                    board[i][j].color = 1;
                }
                if(j == 3) {
                    board[i][j].type = pieceTypes.queen;
                    board[i][j].color = 1;
                }
                if(j == 4) {
                    board[i][j].type = pieceTypes.king;
                    board[i][j].color = 1;
                }
            }
            if(i == 6) {
                board[i][j].type = pieceTypes.pawn;
                    board[i][j].color = 1;
            }
        }
    }
}
void printBoard(piece board[8][8]) {
    string pieceNames[8] = {" ", "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654", " "};
    for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                cout << ((i+j)%2 == 0 ? "\x1b[107m" : "\x1b[100m" ); //background color for the squares.
                cout << (board[i][j].color == 0 ? "\x1b[91m" : "\x1b[94m");
                cout << pieceNames[board[i][j].type];
                cout << " "; //height > char width, so print two spaces.
            }
            cout << "\x1b[0m" << endl;
        }
}
void copyBoard(piece board[8][8], piece newBoard[8][8]) {
    memcpy(newBoard, board, sizeof(piece) * 64);
}

int scorePosition(piece board[8][8]) {
    int score = 0;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {
            if (board[i][j].color == 0) {
                // score += sqrt(pow((i-whiteKingPos.originY), 2) + pow((j-whiteKingPos.originX), 2));
                score -= i;
                switch(board[i][j].type) {
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
            } else if (board[i][j].color == 1) {
                // score -= sqrt(pow((i-blackKingPos.originY), 2) + pow((j-blackKingPos.originX), 2));
                score += (7-i);
                switch(board[i][j].type) {
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
bool inCheck(piece board[8][8], int turn) {
    int kingPosX = -1;
    int kingPosY = -1;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(board[i][j].type == pieceTypes.king && board[i][j].color == turn) {
                kingPosX = j;
                kingPosY = i;
            }
    if(kingPosX == -1 && kingPosY == -1)
        return true;
    int i;
    for(i = kingPosY - 1; i > -1 && board[i][kingPosX].type == pieceTypes.empty; i--)
        continue;
    if( i > -1 && board[i][kingPosX].color != turn && (board[i][kingPosX].type == pieceTypes.rook || board[i][kingPosX].type == pieceTypes.queen))
        return true;
    for(i = kingPosY + 1; i < 8 && board[i][kingPosX].type == pieceTypes.empty; i++)
        continue;
    if(i < 8 && board[i][kingPosX].color != turn && (board[i][kingPosX].type == pieceTypes.rook || board[i][kingPosX].type == pieceTypes.queen))
        return true;
    int j;
    for(j = kingPosX - 1; j > -1 && board[kingPosY][j].type == pieceTypes.empty; j--)
        continue;
    if(j > -1 && board[kingPosY][j].color != turn && (board[kingPosY][j].type == pieceTypes.rook || board[kingPosY][j].type == pieceTypes.queen))
        return true;
    for(j = kingPosX + 1; j < 8 && board[kingPosY][j].type == pieceTypes.empty; j++)
        continue;
    if(j < 8 && board[kingPosY][j].color != turn && (board[kingPosY][j].type == pieceTypes.rook || board[kingPosY][j].type == pieceTypes.queen))
        return true;
    int k;
    for(k = 1; kingPosY - k > -1 && kingPosX - k > -1 && board[kingPosY - k][kingPosX - k].type == pieceTypes.empty; k++)
        continue;
    if(kingPosY - k > -1 && kingPosX - k > -1 && board[kingPosY - k][kingPosX - k].color != turn && (board[kingPosY - k][kingPosX - k].type == pieceTypes.bishop || board[kingPosY - k][kingPosX - k].type == pieceTypes.queen))
        return true;
    for(k = 1; kingPosY + k < 8 && kingPosX + k < 8 && board[kingPosY + k][kingPosX + k].type == pieceTypes.empty; k++)
        continue;
    if(kingPosY + k < 8 && kingPosX + k < 8 && board[kingPosY + k][kingPosX + k].color != turn && (board[kingPosY + k][kingPosX + k].type == pieceTypes.bishop || board[kingPosY + k][kingPosX + k].type == pieceTypes.queen))
        return true;
    for(k = 1; kingPosY - k > -1 && kingPosX + k < 8 && board[kingPosY - k][kingPosX + k].type == pieceTypes.empty; k++)
        continue;
    if(kingPosY - k > -1 && kingPosX + k < 8 && board[kingPosY - k][kingPosX + k].color != turn && (board[kingPosY - k][kingPosX + k].type == pieceTypes.bishop || board[kingPosY - k][kingPosX + k].type == pieceTypes.queen))
        return true;
    for(k = 1; kingPosY + k < 8 && kingPosX - k > -1 && board[kingPosY + k][kingPosX - k].type == pieceTypes.empty; k++)
        continue;
    if(kingPosY + k < 8 && kingPosX - k > -1 && board[kingPosY + k][kingPosX - k].color != turn && (board[kingPosY + k][kingPosX - k].type == pieceTypes.bishop || board[kingPosY + k][kingPosX - k].type == pieceTypes.queen))
        return true;

    //knights
    int t = kingPosY + 1;
    int u = kingPosX + 2;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY + 2;
    u = kingPosX + 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY - 1;
    u = kingPosX + 2;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY - 2;
    u = kingPosX + 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY + 1;
    u = kingPosX - 2;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY + 2;
    u = kingPosX - 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY - 1;
    u = kingPosX - 2;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;
    t = kingPosY - 2;
    u = kingPosX - 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.knight && board[t][u].color != turn))
        return true;

    //king vs king
    t = kingPosY - 1;
    u = kingPosX - 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY - 1;
    u = kingPosX + 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY + 1;
    u = kingPosX - 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY + 1;
    u = kingPosX + 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY - 1;
    u = kingPosX;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY + 1;
    u = kingPosX;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY;
    u = kingPosX - 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    t = kingPosY;
    u = kingPosX + 1;
    if(t > -1 && t < 8 && u > -1 && u < 8 && (board[t][u].type == pieceTypes.king && board[t][u].color != turn))
        return true;
    return false;
}