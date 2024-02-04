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
                            black_lost {}, white_lost{},
                            white_player_points{},
                            black_player_points{},
                            in_checkmate {false}
                            {std::cout << "CHESSBOARD INITILIZED\n";}

//only for testing puroposes
Board::Board(int chessboard[SIZE_CHESS][SIZE_CHESS],
        int black_lost[NUM_PIECES],
        int white_lost[NUM_PIECES],
        int white_player_points,
        int black_player_points,
        bool in_checkamte){
            for(int i = 0; i < SIZE_CHESS; i++){
                for(int j = 0; j < SIZE_CHESS; j++){
                    this->chessboard[i][j] = chessboard[i][j];
                }
            }
            for(int i = 0; i < NUM_PIECES; i++){
                this->black_lost[i] = black_lost[i];
                this->white_lost[i] = white_lost[i];
                
            }
            this->white_player_points = white_player_points;
            this->black_player_points = black_player_points;
            this->in_checkmate = in_checkamte;
            std::cout << "CHESSBOARD INITILIZED\n";
        }

//only for testing purposes

Board::Board(int chessboard[SIZE_CHESS][SIZE_CHESS]):
                            black_lost {}, white_lost{},
                            white_player_points{},
                            black_player_points{},
                            in_checkmate {false}{
    for(int i = 0; i < SIZE_CHESS; i++){
        for(int j = 0; j < SIZE_CHESS; j++){
            this->chessboard[i][j] = chessboard[i][j];
        }
    }
}

Board::~Board(){
    std::cout << "CHESSBOARD DECONSTRUCTED\n";

}

//TODO IMPLIMENT THE ABILITY TO CAPTURE A PIECE;
//TODO:impliment
bool Board::make_move(int start_row, int start_col, int end_row, int end_col){
    Rule rule;
    bool success = rule.choose_rule(start_row, start_col, end_row, end_col, chessboard);
    if(success == false){
        std::cout << "MOVE FROM POSITION (" << start_row << ", " << start_col << ") "
        << "WAS NOT SUCCESSFUL PLEASE TRY AGAIN.\n"; 
    }
    else{
        chessboard[end_row][end_col] = chessboard[start_row][start_col];
        std::cout << "MOVE FROM POSITION (" << start_row << ", " << start_col << ") "
        << "WAS SUCCESSFUL.\n"; 
    }
    //int temp_start = chessboard[start_row][start_col];
    //int temp_end = chessboard[end_row][end_col];
    //chessboard[start_row][start_col]=0;
    //chessboard[end_row][end_col]= temp_start;
    return false;
}

const int Board::get_white_player_points() const{
    return white_player_points;
}

const int Board::get_black_player_points() const{
    return black_player_points;
}

void Board:: update_white_player_points(int piece){
    white_player_points += abs(piece);

}

void Board::update_black_player_points(int piece){
    black_player_points += abs(piece);

}

const int *Board::get_black_lost() const{
    return black_lost;

}

const int* Board::get_white_lost() const{
    return white_lost;

}
//TODO:impliment -- change 
void Board::update_black_lost(int piece){
    switch (abs(piece))
    {
    case 1:
        black_lost[0] += 1;
        break;
    case 5:
        black_lost[1] += 5;
        break;
    case 2: 
        black_lost[2] += 2;
        break;
    case 3:
        black_lost[3] += 3;
        break;
    case 6:
        black_lost[4] += 4;
        break;
    case 9:
        black_lost[5] += 9;

    }

}
//TODO:impliment --change
void Board::update_white_lost(int piece){
    switch (abs(piece))
    {
    case 1:
        white_lost[0] += 1;
        break;
    case 5:
        white_lost[1] += 5;
        break;
    case 2: 
        white_lost[2] += 2;
        break;
    case 3:
        white_lost[3] += 3;
        break;
    case 6:
        white_lost[4] += 4;
        break;
    case 9:
        white_lost[5] += 9;

    }
}

void Board::update_checkmate(bool anwser){
    in_checkmate = anwser;

}

const bool Board::get_in_checkmate() const{
    return in_checkmate;

}

const int Board::get_value_at_position(int row, int col) const{
    return chessboard[row][col];
}
      

