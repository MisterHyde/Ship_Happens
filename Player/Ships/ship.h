/************************************************************************************
 * ship.h 																			*
 * Contains the definition of the class ship, it's members and member-functions		*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

/***********************************************************************************
 * Changelog:
 * 140501  MP  @all    Definition of the Ship Class
 *
 *
 ***********************************************************************************/

# ifndef SHIP_H
# define SHIP_H

# include "my_headers.h"
# include "Player/square.h"

# ifndef SHIP_TYPE
# define SHIP_TYPE


typedef
/**
 * @brief The Enum Ship_Type
 * The enum Ship_Type holds all possible Types of Ships, and equals them to a unique
 * integer. This prevents a user from abusing the cernel by calling not existant ships.
 */
enum {

    Ship_t = 0,
    Submarine_t  = 1,
    Destroyer_t  = 2,
    Battleship_t = 3,
    AirCarrier_t = 4
} Ship_Type;

# endif //SHIP_TYPE

/**
 * @brief The Ship class
 * This class inherits all the basic data and functions a battleships ship has,
 * each ship has a alive flag that will be set false if the ship has been destroyed
 * a set flag that will be set true if the ship has successfully been placed on the
 * field each ship has a defined lenght meassured in squaress, a type e.g. Submarine,
 * destroyer, battleship, air carrier and so on. Each Ship also has a Square* array
 * that connects the ship with the Squares it has been set on.
 *
 * @author m-a-d
 * @version 0.1
 */
 class Ship {
 private:
     bool alive;                     /**< the alive flag indicates if the ship has
                                          squares left that have not been hit yet*/
     bool set;                       /**< the set flag indicates if the ship
                                          has been set on the board*/
     static size_t const type = Ship_t;   /**< the type is just an id that can be used
                                          to get a ships type 0 = ship*/
     static size_t const lenght = 2; /**< the lenght of each ship is meassured in
                                          Squares it takes on the field*/
     Square* position[lenght];       /**< the position array holds pointer to the
                                          boards squares, the ship has been placed on*/

 public:
     Ship();
     ~Ship();
     void reset_ship();

     // a member function for every Ship_lenght

     void set_ship(Square* _sq1, Square* _sq2);
     void set_ship(Square* _sq1, Square* _sq2, Square* _sq3);
     void set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4);
     void set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4, Square* _sq5);
     void check_ship_stat();
     void display_ship();

     bool get_ship_stat();
     bool get_ship_set();


     virtual size_t get_lenght();

# ifndef GRAPHIC
     // help func for terminal testing purposes
     void print_ship();
# endif // GRAPHIC
 };

 # endif // SHIP_H
