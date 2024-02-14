#include "rules.h"
#include <cstdlib>
#include <iostream>

Rule::Rule(){};
Rule::~Rule(){};

//checks if a pawn piece is able to make given move
bool Rule::pawn_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    //must be pawns first move.
    if((start_row +2 == end_row && start_col == end_col) || (start_row -2 == end_row && start_col == end_col)){

        if(start_row +2 == end_row && start_col == end_col){
            if(board.get_value_at_position(start_row + 1, start_col) != 0){
                return false;
            }
        }
        else if(start_row -2 == end_row && start_col == end_col){
            if(board.get_value_at_position(start_row - 1, start_col) != 0){
                return false;
            }
        }

        //determine if the pawn is white or black.
        bool pawn_color = board.get_value_at_position(start_row, start_col);
        //determine if it is the first time the pawn is moving.
        if((start_row == 1 && pawn_color == true ) || (start_row == 6 && pawn_color == false)){
            return true;
        }
        return false;
    }

    //checks if a king piece is able to make given move
    else if((start_row +1 == end_row && start_col == end_col) || (start_row -1 == end_row && start_col == end_col)){
        //determine if pawn is white of black
        int pawn_color = board.get_value_at_position(start_row, start_col);
        //make sure black pawns cant go backwards.
        if(pawn_color < 0){
            if(end_row < start_row){
                return false;
            }
        }
        else if(pawn_color > 0){
            if(end_row > start_row){
                return false;
            }
        }
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

//checks if a knight piece is able to make given move
bool Rule::knight_rule(int start_row, int start_col, int end_row, int end_col){
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
    else if(start_row + 1 == end_row){
        if(start_col +2 == end_col){
            return true;
        }
        else if(start_col -2 == end_col){
            return true;
        }
    }
    else if(start_row -1 == end_row){
        if(start_col +2 == end_col){
            return true;
        }
        else if(start_col -2 == end_col){
            return true;
        }
    }
    return false;
}

//checks if a rook piece is able to make given move
bool Rule::rook_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    if(start_row == end_row){
        return is_piece_in_way_horizontal(start_row, start_col, end_col, board);
    }
    else if(start_col == end_col){
        return is_piece_in_way_vertical(start_row, start_col, end_row, board);
    }
    return false;
}

//checks if a bishop piece is able to make given move
bool Rule::bishop_rule(int start_row, int start_col, int end_row, int end_col, const Board &board){
    if(abs(start_row - end_row) == abs(start_col - end_col)){
        return is_piece_in_way_diagonal(start_row, start_row, end_row, end_col, board);
    }
    return false;
}

//checks if a king piece is able to make given move
bool Rule::king_rule(int start_row, int start_col, int end_row, int end_col){
    if(start_row + 1 == end_row){
        if(start_col == end_col){
            return true;
        }
        else if(start_col - 1 == end_col){
            return true;
        }
        else if(start_col + 1 == end_col){
            return true;
        }
    }
    else if(start_row == end_row){
        if(start_col - 1 == end_col){
            return true;
        }
        else if(start_col + 1 == end_col){
            return true;
        }
    }
    else if(start_row -1 == end_row){
        if(start_col == end_col){
            return true;
        }
        else if(start_col - 1 == end_col){
            return true;
        }
        else if(start_col + 1 == end_col){
            return true;
        }
    }
    return false;
}

//checks if a queen piece is able to make given move.
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
    return true;
}

//determines if a move can be made through evaluating different chess rules and movesets for a given piece.
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

    return answer;

}

//checks if a selected move is out of the 7 by 7 board.
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

//checks if a move from one piece will not be to another piece of the same color
bool Rule::same_color_rule(int piece1, int piece2){
    if(piece1 < 0 && piece2 < 0){
        return false;
    }
    if(piece1 > 0 && piece2 > 0){
        return false;
    }
    return true;
}

//checks if the given tile is not empty by checking if the value of that tile is 0 or not.
//if piece on given tile is 0 that means tile is empty and return false. Else return true.
bool Rule::is_not_zero(int piece1){
    if(piece1 == 0){
        return false;
    }
    return true;

}

//checks if a piece ia able to make a horizontal move.
//checks if a piece is in the way of a horizontal move.
bool Rule::is_piece_in_way_horizontal(int start_row, int start_col, int end_col, const Board &board){
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

//checks if a piece ia able to make a vertical move.
//checks if a piece is in the way of a vertical move.
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
//checks if a piece ia able to make a diagonal move.
//checks if a piece is in the way of a diagonal move.
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