#include "interface.h"
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>

Interface::Interface():board{},
piece_value{{0,5}, {1,2}, {2,3}, {3,6}, {4,9}, {5,1}}{}

//only for testing purposes.
Interface::Interface(int chessboard[SIZE_CHESS][SIZE_CHESS]):
piece_value{{0,5}, {1,2}, {2,3}, {3,6}, {4,9}, {5,1}}, board(chessboard){};

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
void Interface::print_lost_box_top(int color){

    std::cout<< "\033[1;31m   R    N    B    Q    K    P\033[0m    ";
    std::cout << "   R    N    B    Q    K    P\n";
    std::cout <<"B  ----------------------------  W  ----------------------------\n"; 
}


void Interface::print_lost_box_middle_end(){

    //const int * temp_array_black = board.get_black_lost();
    //const int * temp_array_white = board.get_white_lost();
    for(int i = 0; i < 6; i++){
        std::cout <<"  |" << abs(board.get_black_lost()[i])/piece_value[i]<< "|";
    }
    std::cout <<"    ";
    for(int j = 0; j < 6; j++){
        std::cout <<"  |" << abs(board.get_white_lost()[j])/piece_value[j]<< "|";
    }
    std::cout << std::endl;
}


void Interface::print_box_start(int row, int number){
   if(number < 0){
     //std::string number_temp = std::to_string(abs(number));
     std::cout << row <<"| \033[1;31m"<< abs(number) << " \033[0m|  ";
   }
   else{
    std::cout << row <<"| " << number << " |  ";
   }
}


void Interface::print_line(){
    std::cout <<"\n  --------------------------------\n";
}

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
    print_lost_box_top(0);
    print_lost_box_middle_end();
}

//TODO:IMPLIMENT
void Interface::make_move(){
    int srow, scol, erow, ecol;
    std::cout << "make move: enter start row, start col, end row, end col: ";
    std::cin >> srow >> scol >> erow >> ecol;
    board.make_move(srow,scol,erow,ecol);

}
//ONLY FOR TESTS
void Interface::make_move(int start_row, int start_col, int end_row, int end_col){
    board.make_move(start_row, start_col, end_row, end_col);
}

//TODO:IMPLIMENT
void Interface::print_lost_pieces(){

}

void Interface::print_score(){
    std::cout <<"\033[1;31mBlack Player's Score\033[0m " << board.get_black_player_points()
    << "    White Player's Score " << board.get_white_player_points()<<std::endl <<std::endl;
}
//TODO:IMPLIMENT
void Interface::print_win_screen(){

}
//TODO:IMPLIMENT
void Interface::checkmate(){

}