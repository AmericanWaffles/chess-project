#include "typedefs.h"

int validMoves(piece* board[8][8], int turn, vector<pieceMove> &soFar) { //calculates valid moves for a player
    vector<pieceMove> moves;
    vector<pieceMove> captures;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) { //each square, left to right top to bottom
            if(board[i][j]->type != pieceTypes.empty && board[i][j]->color == turn) { //this piece is the current player's
                // cout << board[i][j]->type << endl;
                if(board[i][j]->type == pieceTypes.pawn && i > 0 && i < 7) { //piece is a pawn and it's not on the end rank
                    if(turn == 0) {
                        if(board[i+1][j]->type == pieceTypes.empty) { //pawn can advance
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j;
                            thisMove.destY = i + 1;
                            moves.push_back(thisMove);
                        }
                        if(j > 0 && board[i+1][j-1]->type != pieceTypes.empty) { //pawn can take to the left
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j - 1;
                            thisMove.destY = i + 1;
                            captures.push_back(thisMove);
                        }
                        if(j < 7 && board[i+1][j + 1]->type != pieceTypes.empty) { //pawn can take to the right
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j + 1;
                            thisMove.destY = i + 1;
                            captures.push_back(thisMove);
                        }
                    } else {
                        if(board[i-1][j]->type == pieceTypes.empty) { //pawn can advance
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j;
                            thisMove.destY = i - 1;
                            moves.push_back(thisMove);
                        }
                        if(j > 0 && board[i-1][j-1]->type != pieceTypes.empty) { //pawn can take to the left
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j - 1;
                            thisMove.destY = i - 1;
                            captures.push_back(thisMove);
                        }
                        if(j < 7 && board[i-1][j + 1]->type != pieceTypes.empty) { //pawn can take to the right
                            pieceMove thisMove;
                            thisMove.originX = j;
                            thisMove.originY = i;
                            thisMove.destX = j + 1;
                            thisMove.destY = i - 1;
                            captures.push_back(thisMove);
                        }
                    }
                } //end of the pawn moves. TODO: en passant and pawns that can move two squares
                else if(board[i][j]->type == pieceTypes.rook) { //rook moves
                    for (int k = 1; i + k < 8 && (board[i+k][j]->type==pieceTypes.empty || board[i+k][j]->color != turn); k++) {//rook moves down
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i + k;
                        if(board[i+k][j]->type!=pieceTypes.empty) {
                            captures.push_back(thisMove);
                            break;
                        } else {
                            moves.push_back(thisMove);
                        }
                    }
                    for (int k = 1; i - k >= 0 && (board[i-k][j]->type==pieceTypes.empty || board[i-k][j]->color != turn); k++) {//rook moves up
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i - k;
                        
                        if(board[i-k][j]->type!=pieceTypes.empty && board[i-k][j]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        } else {
                            moves.push_back(thisMove);
                        }
                    }
                    for (int k = 1; j + k < 8 && (board[i][j+k]->type==pieceTypes.empty || board[i][j+k]->color != turn); k++) {//rook moves right
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+k;
                        thisMove.destY = i;
                         
                        if(board[i][j+k]->type!=pieceTypes.empty && board[i][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        } else moves.push_back(thisMove);
                    }
                    for (int k = 1; j - k >= 0 && (board[i][j-k]->type==pieceTypes.empty || board[i][j-k]->color != turn); k++) {//rook moves left
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-k;
                        thisMove.destY = i;
                         
                        if(board[i][j-k]->type!=pieceTypes.empty && board[i][j-k]->color != turn) { //take move
                             captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                } //done with rook moves
                else if(board[i][j]->type == pieceTypes.knight) { //knight moves
                    if(i-1 >= 0 && j-2 >= 0 && board[i-1][j-2]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-2;
                        thisMove.destY = i-1;
                        soFar.push_back(thisMove);
                    }
                    if(i+1 < 8 && j-2 >= 0 && board[i+1][j-2]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-2;
                        thisMove.destY = i+1;
                        soFar.push_back(thisMove);
                    }
                    if(i-1 >= 0 && j+2 < 8 && board[i-1][j+2]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+2;
                        thisMove.destY = i-1;
                        soFar.push_back(thisMove);
                    }
                    if(i+1 < 8 && j+2 < 8 && board[i+1][j+2]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+2;
                        thisMove.destY = i+1;
                        soFar.push_back(thisMove);
                    }
                    if(i-2 >= 0 && j-1 >= 0 && board[i-2][j-1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-1;
                        thisMove.destY = i-2;
                        soFar.push_back(thisMove);
                    }
                    if(i+2 < 8 && j-1 >= 0 && board[i+2][j-1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-1;
                        thisMove.destY = i+2;
                        soFar.push_back(thisMove);
                    }
                    if(i-2 >= 0 && j+1 < 8 && board[i-2][j+1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+1;
                        thisMove.destY = i-2;
                        soFar.push_back(thisMove);
                    }
                    if(i+2 < 8 && j+1 < 8 && board[i+2][j+1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+1;
                        thisMove.destY = i+2;
                        soFar.push_back(thisMove);
                    }
                } //done with knight moves
                else if(board[i][j]->type == pieceTypes.bishop) { //bishop moves
                    for (int k = 1; i + k < 8 && j + k < 8 && (board[i+k][j+k]->type==pieceTypes.empty || board[i+k][j+k]->color != turn); k++) {//bishop moves diagonally down and right
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j + k;
                        thisMove.destY = i + k;
                         
                        if(board[i+k][j+k]->type!=pieceTypes.empty && board[i+k][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; i - k >= 0 && j - k >= 0 && (board[i-k][j-k]->type==pieceTypes.empty || board[i-k][j-k]->color != turn); k++) {//bishop moves up and left
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j - k;
                        thisMove.destY = i - k;
                         
                        if(board[i-k][j-k]->type!=pieceTypes.empty && board[i-k][j-k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j + k < 8 && i - k >= 0 && (board[i-k][j+k]->type==pieceTypes.empty || board[i-k][j+k]->color != turn); k++) { //bishop makes another move
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+k;
                        thisMove.destY = i-k;
                         
                        if(board[i-k][j+k]->type!=pieceTypes.empty && board[i-k][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j - k >= 0 && i + k < 8 && (board[i+k][j-k]->type==pieceTypes.empty || board[i+k][j-k]->color != turn); k++) { //bishop makes another move
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-k;
                        thisMove.destY = i+k;
                         
                        if(board[i+k][j-k]->type!=pieceTypes.empty && board[i+k][j-k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                } //done with bishop moves
                else if(board[i][j]->type == pieceTypes.king) { //king moves
                    if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-1;
                        thisMove.destY = i-1;
                        soFar.push_back(thisMove);
                    }
                    if(i+1 < 8 && j-1 >= 0 && board[i+1][j-1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-1;
                        thisMove.destY = i+1;
                        soFar.push_back(thisMove);
                    }
                    if(i-1 >= 0 && j+1 < 8 && board[i-1][j+1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+1;
                        thisMove.destY = i-1;
                        soFar.push_back(thisMove);
                    }
                    if(i+1 < 8 && j+1 < 8 && board[i+1][j+1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+1;
                        thisMove.destY = i+1;
                        soFar.push_back(thisMove);
                    }
                    if(i >= 0 && j-1 >= 0 && board[i][j-1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j - 1;
                        thisMove.destY = i;
                        soFar.push_back(thisMove);
                    }
                    if(i < 8 && j+1 < 8 && board[i][j+1]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+1;
                        thisMove.destY = i;
                        soFar.push_back(thisMove);
                    }
                    if(i-1 >= 0 && j < 8 && board[i-1][j]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i-1;
                        soFar.push_back(thisMove);
                    }
                    if(i+1 < 8 && j >= 0 && board[i+1][j]->color!=turn) {
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i+1;
                        soFar.push_back(thisMove);
                    }
                } //done with king moves
                else if(board[i][j]->type == pieceTypes.queen) { //queen moves
                    for (int k = 1; i + k < 8 && (board[i+k][j]->type==pieceTypes.empty || board[i+k][j]->color != turn); k++) {//rook moves down
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i + k;
                         
                        if(board[i+k][j]->type!=pieceTypes.empty && board[i+k][j]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; i - k >= 0 && (board[i-k][j]->type==pieceTypes.empty || board[i-k][j]->color != turn); k++) {//rook moves up
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j;
                        thisMove.destY = i - k;
                         
                        if(board[i-k][j]->type!=pieceTypes.empty && board[i-k][j]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j + k < 8 && (board[i][j+k]->type==pieceTypes.empty || board[i][j+k]->color != turn); k++) {//rook moves right
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+k;
                        thisMove.destY = i;
                         
                        if(board[i][j+k]->type!=pieceTypes.empty && board[i][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j - k >= 0 && (board[i][j-k]->type==pieceTypes.empty || board[i][j-k]->color != turn); k++) {//rook moves left
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-k;
                        thisMove.destY = i;
                         
                        if(board[i][j-k]->type!=pieceTypes.empty && board[i][j-k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; i + k < 8 && j + k < 8 && (board[i+k][j+k]->type==pieceTypes.empty || board[i+k][j+k]->color != turn); k++) {//bishop moves diagonally down and right
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j + k;
                        thisMove.destY = i + k;
                         
                        if(board[i+k][j+k]->type!=pieceTypes.empty && board[i+k][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; i - k >= 0 && j - k >= 0 && (board[i-k][j-k]->type==pieceTypes.empty || board[i-k][j-k]->color != turn); k++) {//bishop moves up and left
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j - k;
                        thisMove.destY = i - k;
                         
                        if(board[i-k][j-k]->type!=pieceTypes.empty && board[i-k][j-k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j + k < 8 && i - k >= 0 && (board[i-k][j+k]->type==pieceTypes.empty || board[i-k][j+k]->color != turn); k++) { //bishop makes another move
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j+k;
                        thisMove.destY = i-k;
                         
                        if(board[i-k][j+k]->type!=pieceTypes.empty && board[i-k][j+k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                    for (int k = 1; j - k >= 0 && i + k < 8 && (board[i+k][j-k]->type==pieceTypes.empty || board[i+k][j-k]->color != turn); k++) { //bishop makes another move
                        pieceMove thisMove;
                        thisMove.originX = j;
                        thisMove.originY = i;
                        thisMove.destX = j-k;
                        thisMove.destY = i+k;
                         
                        if(board[i+k][j-k]->type!=pieceTypes.empty && board[i+k][j-k]->color != turn) { //take move
                            captures.push_back(thisMove);
                            break; //can't continue after capturing
                        }  else moves.push_back(thisMove);
                    }
                } //done with queen moves

            }
        }
    }
    for(pieceMove m : captures)
        soFar.push_back(m);
    for(pieceMove m : moves)
        soFar.push_back(m);
    return 0;
}