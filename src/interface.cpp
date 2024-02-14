#include "interface.h"
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>

Interface::Interface():board{},
piece_value{{0,5}, {1,2}, {2,3}, {3,9}, {4,6}, {5,1}}{}

//a constructor only used for testing purposes.
Interface::Interface(int chessboard[SIZE_CHESS][SIZE_CHESS]):
piece_value{{0,5}, {1,2}, {2,3}, {3,9}, {4,6}, {5,1}}, board(chessboard){};

Interface::~Interface(){}

void Interface::print_header(){
    std::cout <<"   0   1   2   3   4   5   6   7\n";
    std::cout <<"  --------------------------------\n";
}

void Interface::print_box_middle_end(int number){
    if(number < 0){
        std::cout << "\033[1;31m"<< abs(number) << "\033[0m|  ";
    }
    else{
        std::cout << number << "|  ";
    }
}
void Interface::print_captured_box_top(){

    std::cout<< "\033[1;31m   R    N    B    Q    K    P\033[0m    ";
    std::cout << "   R    N    B    Q    K    P\n";
    std::cout <<"B  ----------------------------  W  ----------------------------\n"; 
}


void Interface::print_captured_box_middle_end(){
    std::cout << piece_value[0];

    for(int i = 0; i < 6; i++){
        std::cout <<"  |" << abs(board.get_black_captured()[i])/piece_value[i] << "|";
    }
    std::cout <<"    ";
    for(int j = 0; j < 6; j++){
        std::cout <<"  |" << abs(board.get_white_captured()[j])/piece_value[j]<< "|";
    }
    std::cout << std::endl;
}


void Interface::print_box_start(int row, int number){
   if(number < 0){
     std::cout << row <<"| \033[1;31m"<< abs(number) << " \033[0m|  ";
   }
   else{
    std::cout << row <<"| " << number << " |  ";
   }
}


void Interface::print_line(){
    std::cout <<"\n  --------------------------------\n";
}

//prints out board.
void Interface::print_board_state(){
    print_score();
    print_header();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j==0){
                print_box_start(i,board.get_value_at_position(i,j));
            }
            else{
                print_box_middle_end(board.get_value_at_position(i,j));
            }
        }
        print_line();
    }
    print_captured_box_top();
    print_captured_box_middle_end();
}

//starts the process of making a move.
void Interface::make_move(){
    int srow, scol, erow, ecol;
    std::cout << "make move: enter start row, start col, end row, end col: ";
    std::cin >> srow >> scol >> erow >> ecol;
    board.make_move(srow,scol,erow,ecol);

}

//ONLY FOR TESTS -- FOR TESTING RULES
bool Interface::make_move(int start_row, int start_col, int end_row, int end_col){
    return board.make_move(start_row, start_col, end_row, end_col);
}

//ONLY FOR TESTS -- FOR PLACEING PICES IGNORING RULES
bool Interface::make_move_ir(int start_row, int start_col, int end_row, int end_col){
    return board.make_move_ir(start_row, start_col, end_row, end_col);

}

//prints out bothplayers scores.
void Interface::print_score(){
    std::cout <<"\033[1;31mBlack Player's Score\033[0m " << board.get_black_player_points()
    << "    White Player's Score " << board.get_white_player_points()<<std::endl <<std::endl;
}

//prints out a simple win screen.
void Interface::print_win_screen(){
    bool winning_color = false;
    if(board.get_white_captured()[4] == 1 ){
        winning_color = true;
    }
    if(!winning_color){
        std::cout << "\033[1;31mBLACK PLAYER HAS WON!!!! \033[0m\n";
    }
    else{
        std::cout << "WHITE PLAYER HAS WON!!!!\n";
    }

}

//is used to check if the game is over.
bool Interface::is_game_over(){
    return board.get_in_checkmate();
}