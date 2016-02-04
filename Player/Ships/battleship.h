/************************************************************************************
 * battleship.h                                                             		*
 * Contains the definition of the class battleship, which is a kind of ship     	*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140501  MP  @all    Definition of the ship sub class battleship
  * 140510  MP  @all    added comments
  *
  ***********************************************************************************/

# ifndef BATTLESHIP_H
# define BATTLESHIP_H

# include "my_headers.h"
# include "ship.h"


/**
 * @brief The Battleship class
 * The battleship class is a subclass of ship, which has the same member and member
 * functions it is the third type of ship with a lenght of 4 squares.
 *
 * @author m-a-d
 * @version 0.1
 */
class Battleship : public virtual Ship {
private:
    bool alive;                         /**< the alive flag indicates if the battleship
                                             has squares left that have not been hit yet*/
    bool set;                           /**< the set flag indicates if the battle ship
                                             has been set on the board*/
    static Ship_Type const type = Battleship_t; /**< the type is just an id that can be used
                                                  to get a ships type 3 = battleship*/
    static size_t const lenght = 4;     /**< the lenght of each ship is meassured in
                                             Squares it takes on the field*/
    Square* position[lenght];           /**< the position array holds pointer to the
                                             boards squares, the ship has been placed on*/
public:
    Battleship();
    ~Battleship();

    size_t get_lenght();
    size_t get_type();

    bool get_ship_set();
    bool get_ship_alive();

    void reset_ship();
    void check_ship_stat();

    void display_ship();
    void set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4);

# ifndef GRAPHIC
    // help func for terminal testing purposes
    void print_ship();
# endif // GRAPHIC

};

#endif // BATTLESHIP_H
