#include "rules.h"
#include <cstdlib>
#include <iostream>

Rule::Rule(){};
Rule::~Rule(){};

//TODO IMPLIMENT AND TEST
//TODO IMPLIMENT EN PASSANT RULE.
bool Rule::pawn_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    //must be pawns first move.
    if((start_row +2 == end_row && start_col == end_col) || (start_row -2 == end_row && start_col == end_col)){
        //determine if the pawn is white or black.
        bool pawn_color = board.get_value_at_position(start_row, start_col);
        //determine if it is the first time the pawn is moving.
        if((start_row == 1 && pawn_color == true) || (start_row == 6 && pawn_color == false)){
            return true;
        }
        return false;
    }
    // pawn can only move one space up and it can't attack straight on.
    else if((start_row +1 == end_row && start_col == end_col) || (start_row -1 == end_row && start_col == end_col)){
        //determine if pawn is white of black
        bool pawn_color = board.get_value_at_position(start_row, start_col);
        //see if tile to move to is empty.
        if(board.get_value_at_position(end_row,end_col) == 0){
            return true;
        }
        return false;
    }
    //is a black pawn attacking
    //TODO IMPLIMENT BELOW SUGGESTION
    //maybe change to start_row +1 == end row && (start_col +1 == end_col || start_col-1 == end_col)
    else if((start_row +1 == end_row && start_col +1 == end_col) || (start_row +1 == end_row && start_col -1 == end_col)){
        if(board.get_value_at_position(end_row, end_col) != 0 ){
            return true;
        }
        return false;
    }
    //is a white pawn attacking
    else if((start_row -1 == end_row && start_col +1 == end_col) || (start_row -1 == end_row && start_col -1 == end_col)){
        if(board.get_value_at_position(end_row, end_col) != 0){
            return true;
        }
        return false;
    }
    return false;
}
//TODO IMPLIMENT AND TEST
bool Rule::knight_rule(int start_row, int start_col, int end_row, int end_col){
    //already checked things like if tile to go to has piece with same color. or if tile to go to is out of bounds.
    if(start_row + 2 == end_row){
        if(start_col + 1 == end_col){
            return true;
        }
        else if(start_col - 1 == end_col){
            return true;
        }

    }
    else if(start_row - 2 == end_row){
        if(start_col + 1 == end_col){
            return true;
        }
        else if(start_col - 1 == end_col){
            return true;
        }

    }
    return false;
}
//TODO IMPLIMENT AND TEST
//A ROOCK CAN MOVE HORIZONTALLY OR VERTICALLY.
bool Rule::rook_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    if(start_row == end_row){
        return is_piece_in_way_horizontal(start_row, start_col, end_col, board);
    }
    else if(start_col == end_col){
        return is_piece_in_way_vertical(start_row, start_col, end_row, board);
    }
    return false;
}
//TODO IMPLIMENT AND TEST
// A BISHOP CAN ONLY MOVE DIAGONALLY.
bool Rule::bishop_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    if(abs(start_row - end_row) == abs(start_col - end_col)){
        return is_piece_in_way_diagonal(start_row, start_row, end_row, end_col, board);
    }
    return false;
}
//TODO IMPLIMENT AND TEST
bool Rule::king_rule(int start_row, int start_col, int end_row, int end_col){
    //alredy checked if move is out of bounds with out_of_bounds() in choose_rule()
    //alredy checked if move is to tile that has piece with same tile, with same_color_rule
    //so that means that the king must be able to make a move. so always return true.
    return true;
}
//TODO IMPLIMENT AND TEST
//the queen has the moveset of the king, rook, and bishop
bool Rule::queen_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){

    //means the move is diagonal.
    if(abs(start_row - end_row) == abs(start_col - end_col)){
        return is_piece_in_way_diagonal(start_row, start_row, end_row, end_col, board);
    }
    //means the move is horizontal
    else if(start_row == end_row){
        return is_piece_in_way_horizontal(start_row, start_col, end_col, board);
    }
    //means the move is vertical
    else if(start_col == end_col){
        return is_piece_in_way_vertical(start_row, start_col, end_row, board);
    }
    //means that it is moving to a tile withing a one block radius of
    //its current tile issues like an out of bounds move
    //and a move that would mean capturing a piece of the same color
    //have alredy been checked in choose_rule(). So return true.
    return true;
}

//TODO IMPLIMENT AND TEST
bool Rule::choose_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){

    bool answer = out_of_bounds_rule(start_row, start_col, end_row, end_col);
    if(answer == false){
        std::cout << " YOU TRIED TO MOVE A PIECE OUT OF BOUNDS.\n";
        return false;
    }

    answer = is_not_zero(board.get_value_at_position(start_row,start_col));
    if(answer == false){
        std::cout << " THE PIECE YOU CHOOSE TO MOVE DOES NOT EXIST.\n";
        return false;
    }

    answer = same_color_rule(board.get_value_at_position(start_row,start_col), board.get_value_at_position(end_row,end_col));
    if(answer == false){
        std::cout << " CAN'T MOVE A PICE ONTO A TILE WITH ANOTHER PIECE OF THE SAME COLOR.\n";
        return false;
    }

    int starting_value = board.get_value_at_position(start_row, start_col);
    
    switch (abs(starting_value))
    {
    case 1:
        answer = pawn_rule(start_row, start_col, end_row, end_col, board);
        break;
    case 5:
        answer = rook_rule(start_row, start_col, end_row, end_col, board);
        break;
    case 2:
        answer = knight_rule(start_row, start_col, end_row, end_col);
        break;
    case 3:
        answer = bishop_rule(start_row, start_col, end_row, end_col, board);
        break;
    case 6:
        answer = queen_rule(start_row, start_col, end_row, end_col, board);
        break;
    case 9:
        answer = king_rule(start_row, start_col, end_row, end_col);
        break;
    }

    return false;

}

bool Rule::out_of_bounds_rule(int start_row, int start_col, int end_row, int end_col){
    if(start_row < 0 || start_row > 7){
        return false;
    }
    if(start_col < 0 || start_col > 7){
        return false;
    }
    if(end_row < 0 || end_row > 7){
        return false;
    }
    if(end_col < 0 || end_col > 7){
        return false;
    }
    return true;
}

bool Rule::same_color_rule(int piece1, int piece2){
    if(piece1 < 0 && piece2 < 0){
        return false;
    }
    if(piece1 > 0 && piece2 > 0){
        return false;
    }
    return true;
}

bool Rule::is_not_zero(int piece1){
    if(piece1 == 0){
        return false;
    }
    return true;

}

//TODO: add a rule that makse it return false if a user picks the same end and start position
//check this function.
bool Rule::is_piece_in_way_horizontal(int start_row, int start_col, int end_col, const Board &board){
    //int temp_row = start_row;
    //int temp_col = start_col;

    if(start_col < end_col){
        start_col++;
        while(start_col < end_col){
            //start_col++;
            if(board.get_value_at_position(start_row, start_col) != 0){
                std::cout << "THERE IS A PIECE IN THE WAY\n";
                return false;
            }
            start_col++;
        }

        return true;
    }
    else{
        start_col--;
        while(start_col > end_col){
            //start_col--;
            if(board.get_value_at_position(start_row, start_col) != 0){
                std::cout << "THERE IS A PIECE IN THE WAY\n";
                return false;
            }
            start_col--;
        }
        return true;
    }
    return false;
}

//TODO: add a rule that makse it return false if a user picks the same end and start position
//check this function.
bool Rule::is_piece_in_way_vertical(int start_row, int start_col, int end_row, const Board &board){

    if(start_row < end_row){
        start_row++;
        while(start_row < end_row){
            //start_row++;
            if(board.get_value_at_position(start_row, start_col) != 0){
                std::cout << "THERE IS A PIECE IN THE WAY\n";
                return false;
            }
            start_row++;
        }

        return true;
    }
    else{
        start_row--;
        while(start_row > end_row){
            //start_row--;
            if(board.get_value_at_position(start_row, start_col) != 0){
                std::cout << "THERE IS A PIECE IN THE WAY\n";
                return false;
            }
            start_row--;
        }
        return true;
    }
    return false;
}
//TODO: add a rule that makse it return false if a user picks the same end and start position
//check this function.
//TODO: YOU REALLY NEED TO CHECK THIS ONE USING TESTS.
bool Rule::is_piece_in_way_diagonal(int start_row, int start_col, int end_row, int end_col, const Board &board){

    if(start_row > end_row && start_col < end_col){
        //   *
        //  /
        // /
        start_row--;
        start_col++;
        while(start_row != end_row && start_col != end_col){
            if(board.get_value_at_position(start_row,start_col) != 0){
                return false;
            }
            start_row--;
            start_col++;
        }
        return true;
    }
    else if(start_row > end_row && start_col > end_col){
        //  *
        // " \"
        //  " \"
        start_row--;
        start_col--;
        while(start_row != end_row && start_col != end_col){
            if(board.get_value_at_position(start_row,start_col) != 0){
                return false;
            }
            start_row--;
            start_col--;
        }
        return true;
    }
    else if(start_row < end_row && start_col < end_col){
        // " \"
        //  " \"
        //     *
        start_row++;
        start_col++;
        while(start_row != end_row && start_col != end_col){
            if(board.get_value_at_position(start_row,start_col) != 0){
                return false;
            }
            start_row++;
            start_col++;
        }
        return true;
    }
    else{
        // /
       // /
      // *
      start_row++;
      start_col--;
      while (start_row != end_row && start_col != end_col){
        if(board.get_value_at_position(start_row,start_col) != 0){
            return false;
        }
        start_row++;
        start_col--;
      }
      return true;
    }

    return false;
}