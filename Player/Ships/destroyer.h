/************************************************************************************
 * destroyer.h																		*
 * Contains the definition of the sub class destroyer, which is a kind of ship		*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140501  MP  @all    Definition of the ship subclass Destroyer
  * 140510  MP  @all    added comments
  *
  ***********************************************************************************/

# ifndef DESTROYER_H
# define DESTROYER_H

# include "my_headers.h"
# include "ship.h"


/**
 * @brief The Destroyer class
 * The Destroyer class is a subclass of ship with the same members and member
 * functions with the lenght of 3 squares.
 *
 * @author m-a-d
 * @version 0.1
 */
class Destroyer : public virtual Ship {
private:
    bool alive;                         /**< the alive flag indicates if the destroyer
                                             has squares left that have not been hit yet*/
    bool set;                           /**< the set flag indicates if the destroyer
                                             has been set on the board*/
    static Ship_Type const type = Destroyer_t;   /**< the type is just an id that can be used
                                                   to get a ships type 2 = destroyer*/
    static size_t const lenght = 3;     /**< the lenght of each ship is meassured in
                                             Squares it takes on the field*/
    Square* position[lenght];           /**< the position array holds pointer to the
                                             boards squares, the ship has been placed on*/

public:
    Destroyer();
    ~Destroyer();

    size_t get_lenght();
    size_t get_type();

    bool get_ship_set();
    bool get_ship_alive();

    void display_ship();
    void check_ship_stat();

    void set_ship(Square* _sq1, Square* _sq2, Square* _sq3);
    void reset_ship();

# ifndef GRAPHIC
    // help func for terminal testing purposes
    void print_ship();
# endif // GRAPHIC

};

#endif // DESTROYER_H
