#ifndef RULES_H
#define RULES_H
#include "board.h"
//#pragma once
class Rule {
    public:
        Rule();
        ~Rule();
        bool choose_rule(int start_row, int start_col, int end_row, int end_col, const Board &board);
    private:
        bool pawn_rule(int start_row, int start_col, int end_row, int end_col, const Board &board );
        bool knight_rule(int start_row, int start_col, int end_row, int end_col);
        bool rook_rule(int start_row, int start_col, int end_row, int end_col, const Board &board);
        bool bishop_rule(int start_row, int start_col, int end_row, int end_col, const Board &board);
        bool king_rule(int start_row, int start_col, int end_row, int end_col);
        bool queen_rule(int start_row, int start_col, int end_row, int end_col, const Board &board);
       
        bool out_of_bounds_rule(int start_row, int start_col, int end_row, int end_col);
        bool same_color_rule(int piece1, int piece2);
        bool is_not_zero(int piece1);
        bool is_piece_in_way_horizontal(int start_row, int start_col, int end_col, const Board &board);
        bool is_piece_in_way_vertical(int start_row, int start_col, int end_row, const Board &board);
        bool is_piece_in_way_diagonal(int start_row, int start_col, int end_row, int end_col, const Board &board);
    //maybe add something here later if it is needed.
        
};
#endif