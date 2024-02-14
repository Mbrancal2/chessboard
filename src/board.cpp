#include "board.h"
#include "rules.h"
#include <iostream>
#include <string>
#include <cstdlib>


Board::Board(): chessboard {{-5,-2,-3,-6,-9,-3,-2,-5},
                            {-1,-1,-1,-1,-1,-1,-1,-1},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1, 1, 1, 1},
                            {5, 2, 3, 6, 9, 3, 2, 5}},
                            black_captured {}, white_captured{},
                            white_player_points{},
                            black_player_points{},
                            in_checkmate {false}
                            {}

//only for testing puroposes
Board::Board(int chessboard[SIZE_CHESS][SIZE_CHESS],
        int black_captured[NUM_PIECES],
        int white_captured[NUM_PIECES],
        int white_player_points,
        int black_player_points,
        bool in_checkamte){
            for(int i = 0; i < SIZE_CHESS; i++){
                for(int j = 0; j < SIZE_CHESS; j++){
                    this->chessboard[i][j] = chessboard[i][j];
                }
            }
            for(int i = 0; i < NUM_PIECES; i++){
                this->black_captured[i] = black_captured[i];
                this->white_captured[i] = white_captured[i];
                
            }
            this->white_player_points = white_player_points;
            this->black_player_points = black_player_points;
            this->in_checkmate = in_checkamte;
        }

//only for testing purposes
Board::Board(int chessboard[SIZE_CHESS][SIZE_CHESS]):
                            black_captured {}, white_captured{},
                            white_player_points{},
                            black_player_points{},
                            in_checkmate {false}{
    for(int i = 0; i < SIZE_CHESS; i++){
        for(int j = 0; j < SIZE_CHESS; j++){
            this->chessboard[i][j] = chessboard[i][j];
        }
    }
}

Board::~Board(){}

//sees if a move can be made and if so makes it. Else does not.
bool Board::make_move(int start_row, int start_col, int end_row, int end_col){
    Rule rule;
    bool success = rule.choose_rule(start_row, start_col, end_row, end_col, chessboard);
    if(success == false){
        std::cout << "MOVE FROM POSITION (" << start_row << ", " << start_col << ") "
        <<"TO POSITION (" << end_row << ", " << end_col << ") "
        <<" WAS NOT SUCCESSFUL PLEASE TRY AGAIN.\n"; 
        return false;
    }
    else{
        int to_go_piece = chessboard[end_row][end_col];
        //black is lost, update white_captured and white_player_points
        if(to_go_piece < 0){
            update_white_player_points(to_go_piece);
            update_white_captured(to_go_piece);
            if(abs(to_go_piece) == 6){
                update_checkmate(true);
            }

        }
        //else whith piece is lost, update black_captured and black_player_poins
        else{
            update_black_player_points(to_go_piece);
            update_black_captured(to_go_piece);
            if(abs(to_go_piece) == 6){
                update_checkmate(true);
            }
        }
        chessboard[end_row][end_col] = chessboard[start_row][start_col];
        chessboard[start_row][start_col] = 0;
        std::cout << "MOVE FROM POSITION (" << start_row << ", " << start_col << ") "
        <<"TO POSITION (" << end_row << ", " << end_col << ")"
        <<" WAS SUCCESSFUL.\n";
        return true;
    }
    return false;
}

//FOR TESTING, MAKES A MOVE IGNORING ANY RULES.
bool Board::make_move_ir(int start_row, int start_col, int end_row, int end_col){
    chessboard[end_row][end_col] = chessboard[start_row][start_col];
    chessboard[start_row][start_col] = 0;
    return true;

}

//gets white's players points.
const int Board::get_white_player_points() const{
    return white_player_points;
}

//gets black's players points.
const int Board::get_black_player_points() const{
    return black_player_points;
}

//updates the number of points that white player has
// by the number associated with piece.
void Board:: update_white_player_points(int piece){
    white_player_points += abs(piece);

}

//updates the number of points that black player has
// by the number associated with piece.
void Board::update_black_player_points(int piece){
    black_player_points += abs(piece);

}

//gets the black captured array
const int *Board::get_black_captured() const{
    return black_captured;

}

//gets the white captured array
const int* Board::get_white_captured() const{
    return white_captured;

}

//updates the array that contains the pieces
//the black side has captured.
void Board::update_black_captured(int piece){
    switch (abs(piece))
    {
    case 1:
        black_captured[5] += 1;
        break;
    case 5:
        black_captured[0] += 5;
        break;
    case 2: 
        black_captured[1] += 2;
        break;
    case 3:
        black_captured[2] += 3;
        break;
    case 6:
        black_captured[4] += 6;
        break;
    case 9:
        black_captured[3] += 9;

    }

}

//updates the array that contains the pieces
//the white side has captured.
void Board::update_white_captured(int piece){
    switch (abs(piece))
    {
    case 1:
        white_captured[5] += 1;
        break;
    case 5:
        white_captured[0] += 5;
        break;
    case 2: 
        white_captured[1] += 2;
        break;
    case 3:
        white_captured[2] += 3;
        break;
    case 6:
        white_captured[4] += 6;
        break;
    case 9:
        white_captured[3] += 9;

    }
}

//updates in_checkmate to the value of answer.
void Board::update_checkmate(bool anwser){
    in_checkmate = anwser;

}

//returns in_checkmate
const bool Board::get_in_checkmate() const{
    return in_checkmate;

}

//returns the value of tile of the board at position [row, col].
const int Board::get_value_at_position(int row, int col) const{
    return chessboard[row][col];
}
      

