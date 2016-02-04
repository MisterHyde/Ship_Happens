/************************************************************************************
 * board.h 	v0.2																	*
 * Contains the definition of the class board 										*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140404	MP	@all	Definition of the Board class
  * 140501  MP  @get_Square added func.
  *
  ***********************************************************************************/

# ifndef BOARD_H
# define BOARD_H

# include "my_headers.h"
# include "square.h"

/**
 * @brief The Board class
 * a Board consists of a two dimensional array of Squares, the Squares will be adressed
 * using two parameters x for the horizontal (lines) and y for the vertical (collumn) axis
 * the board starts with Sq_1(1,1) in the top left corner and ends with the
 * Sq_n(lenght, widht) in the bottom right corner. That means a board consists of x * y
 * Squares that represent all the possible points to set a players ships on or the
 * points of the enemies board that one could bomb.
 *
 * @author m-a-d
 * @version 0.1
 */
class Board {
private:
    static const size_t lenght = 10;      /**< the number of collumns of a board*/
    static const size_t widht = 10;       /**< the number of lines of a board*/
    static  int const len = lenght + 2;
    static  int const wid = widht + 2;
    Square field[len][wid];               /**< two dimensional array of Squares
                                               [number of collumns][number of lines]*/

protected:
    Square* get_next(Square* _sq);
    Square* get_prev(Square* _sq);
    Square* get_next_collumn(Square* _sq);
    Square* get_prev_collumn(Square* _sq);
    bool get_neighbours_empty(Square* _sq);

public:
    Board ();
    Board (size_t _x, size_t _y);
    ~Board ();

    void clear_board();
    bool hit_square(Square* _sq);

    void disable_square(size_t _x, size_t _y);
    bool get_squares_empty(Square* _sq1, Square* _sq2, Square* _sq3 = NULL, Square* _sq4 = NULL,
                          Square* _sq5 = NULL);

    Square* get_Square_ptr(size_t _x, size_t _y);
    size_t get_lenght();
    size_t get_widht();

    /*
     * differnt functions for different ship_lenghts
     */

    void set_ship(Square* _sq1, Square* _sq2);
    void set_ship(Square* _sq1, Square* _sq2, Square* _sq3);
    void set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4);
    void set_ship(Square* _sq1, Square* _sq2, Square* _sq3 = NULL,
                  Square* _sq4 = NULL, Square* _sq5 = NULL);

    /*
     * Network
     */

    char* send_set_squares(char *squares);
    void  receive_set_squares(char* squares);


# ifndef GRAPHIC
    // help and test functions for console debugging
    bool hit_square(size_t _x, size_t _y);
    void print_own_board();
    void print_enemy_board();

    // differnt functions for different ship_lenghts
    void set_ship(size_t _x1, size_t _y1, size_t _x2, size_t _y2);
    void set_ship(size_t _x1, size_t _y1, size_t _x2, size_t _y2, size_t _x3, size_t _y3);
    void set_ship(size_t _x1, size_t _y1, size_t _x2, size_t _y2, size_t _x3, size_t _y3,
                  size_t _x4, size_t _y4);
    void set_ship(size_t _x1, size_t _y1, size_t _x2, size_t _y2, size_t _x3, size_t _y3,
                  size_t _x4, size_t _y4, size_t _x5, size_t _y5);

# endif // GRAPHIC

};

# endif // BOARD_H
