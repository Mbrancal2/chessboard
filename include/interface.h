#ifndef INTERFACE_H
#define INTERFACE_H
#include<unordered_map>
#include "board.h"

class Interface{
    
    private:
        Board board;
        std::unordered_map<int,int> piece_value;
        void print_header();
        void print_box_middle_end(int number);
        void print_box_start(int row, int number);
        void print_line();
        void print_captured_box_top();
        void print_captured_box_middle_end();

    public:
        static const int SIZE_CHESS = 8;
        Interface();
        Interface(int chessboard[SIZE_CHESS][SIZE_CHESS]);
        ~Interface();
        //for printing out a board and information like lost pieces.
        void print_board_state();
        //gets and prints lost white and black pieces.
        
        //prints a win screen for which ever side won.
        void print_win_screen();
        //prints out current score.
        void print_score();
        //prints out move to be made and
        //if that move was successful.
        void make_move();
        //only for testing
        bool make_move(int start_row, int start_col, int end_row, int end_col);
        bool make_move_ir(int start_row, int start_col, int end_row, int end_col);
        //prints out if a user is in checkmate.
        //void checkmate(); -- add in future update
        //check if game is over. //--for testing purposes will always return false as of right now.
        bool is_game_over();


};
#endif