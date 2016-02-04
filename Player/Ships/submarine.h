/************************************************************************************
 * submarine.h																		*
 * Contains the definition of the sub class submarien, which is a kind of ship		*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140501  MP  @all    Definition of the ship subclass submarine
  *
  *
  ***********************************************************************************/

#ifndef SUBMARINE_H
#define SUBMARINE_H

# include "my_headers.h"
# include "ship.h"


/**
 * @brief The Submarine class
 * The Submarine class is a subclass of ship with the same members and member
 * functions with a lenght of 2 squares.
 *
 * @author m-a-d
 * @version 0.1
 */
class Submarine : public virtual Ship {
private:    
    bool alive;                         /**< the alive flag indicates if the submarine
                                             has squares left that have not been hit yet*/
    bool set;                           /**< the set flag indicates if the submarine
                                             has been set on the board*/
    static Ship_Type const type = Submarine_t;   /**< the type is just an id that can be used
                                                   to get a ships type */
    static size_t const lenght = 2;     /**< the lenght of each ship is meassured in
                                             Squares it takes on the field*/
    Square* position[lenght];           /**< the position array holds pointer to the
                                             boards squares, the ship has been placed on*/

public:
    Submarine();
    ~Submarine();

    size_t get_lenght();
    size_t get_type();

    bool get_ship_set();
    bool get_ship_alive();

    void display_ship();
    void reset_ship();

    void check_ship_stat();
    void set_ship(Square* _sq1, Square* _sq2);

# ifndef GRAPHIC
    // help func for terminal testing purposes
    void print_ship();
# endif // GRAPHIC

};

#endif // SUBMARINE_H
