/************************************************************************************
 * ship.cpp     v0.5																*
 * Contains the members and memberfunctions of the ship class, a superclass that    *
 * also implements a lot of it's subclasses functions e.g. "ship.set_ship()"        *
 *                                                                                  *
 *                                                                                  *
 * Matthias Pfitzmayer		140401		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140501  MP  @all    Created std. logic and func.
  *
  *
  *
  ***********************************************************************************/

 # include "ship.h"


/**
 * @brief Ship::Ship
 * std constructor
 * a ship will be createt, which is still unharmed and not set to a specific position
 * @param Ship::alive = true
 * @param Ship::set = false
 */
Ship::Ship() {
    Ship::alive = true;
    Ship::set = false;
}


/**
 * @brief Ship::~Ship
 * destructor
 */
Ship::~Ship() {

}


/**
 * @brief Ship::reset_ship
 * Set ship back to normal.
 * Ship::alive = true
 * Ship::set = false
 * Ship::position[0] -> Ship::position[lenght] = NULL
 */
void Ship::reset_ship() {
     Ship::alive = true;
     Ship::set = false;

     // delete the saved positions of the ship
     for(size_t count = 0; count < Ship::lenght; count++){
         Ship::position[count] = NULL;
     }
}


/**
 * @brief Ship::set_ship
 * for a ship of the lenght of 2 squares, the ship knows the Squares
 * it sits on, a simple way to check a ships status, without using
 * another object (submarine)
 * @param _sq1
 * @param _sq2
 */
void Ship::set_ship(Square* _sq1, Square* _sq2) {
    Ship::position[0] = _sq1;
    Ship::position[1] = _sq2;
    Ship::set = true;
}


/**
 * @brief Ship::set_ship
 * for a ship of the lenght of 3 squares, in this case the ship gets connected
 * to the Squares it sits on as well and same goes for the following versions
 * of this function (destroyer)
 * @param _sq1
 * @param _sq2
 * @param _sq3
 */
void Ship::set_ship(Square *_sq1, Square *_sq2, Square *_sq3) {
    Ship::position[0] = _sq1;
    Ship::position[1] = _sq2;
    Ship::position[2] = _sq3;
    Ship::set = true;
}


/**
 * @brief Ship::set_ship
 * for a ship of the lenght of 4 squares (battleship)
 * @param _sq1
 * @param _sq2
 * @param _sq3
 * @param _sq4
 */
void Ship::set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4) {
    Ship::position[0] = _sq1;
    Ship::position[1] = _sq2;
    Ship::position[2] = _sq3;
    Ship::position[3] = _sq4;
    Ship::set = true;
}


/**
 * @brief Ship::set_ship
 *
 * @param _sq1
 * @param _sq2
 * @param _sq3
 * @param _sq4
 * @param _sq5
 */
void Ship::set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4, Square* _sq5) {
    Ship::position[0] = _sq1;
    Ship::position[1] = _sq2;
    Ship::position[2] = _sq3;
    Ship::position[3] = _sq4;
    Ship::position[4] = _sq5;
    Ship::set = true;
}


/**
 * @brief Ship::check_ship_stat
 * Checks the status of a ship using the Square* array position to check if a ship
 * is still alive, if the number of hits is equal to the ships lenght the alive flag
 * will be toggled and the player loses his ship
 */
void Ship::check_ship_stat() {
    size_t comp = 0;

    /**
     * count the squares that already got hit
     */
    for(size_t count = 0; count < Ship::lenght; count++) {
        if (Ship::position[count]->get_square_hit()) {
            comp++; // increase the number of hits
        }
    }

    /**
     * compair the ammount of squares that already got hit with the lenght of the
     * ship, if they are equal the ship has been destroyed, the flag Ship::alive
     * will be set to false
     */
     if (comp == (Ship::lenght)) {
         Ship::alive = false;
     }
}


/**
 * @brief Ship::get_ship_set
 * @return
 */
bool Ship::get_ship_set() {
    return Ship::set;
}


/**
 * @brief Ship::get_ship_stat
 * @return
 */
bool Ship::get_ship_stat() {
    return Ship::alive;
}


/**
 * ship.display_ship() is another function for console testing purposes
 * each square of a ship, that has already been hit will be displayed as
 * "X" the unharmed ones as "o"
 */
void Ship::print_ship() {
    for(size_t count = 0; count < (Ship::lenght); count++) {
        if (Ship::position[count]->get_square_hit()) {
            std::cout << "X";
        }
        else {
            std::cout << "o";
        }
    }
    std::cout << std::endl;
}


/**
 * Get the lenght of a ship in squares.
 * ship.get_lenght() is a simple getter function that returns a ships
 * lenght from it's definition
 * @see Ship::Ship()
 * @return: size_t Ship::lenght
 */
size_t Ship::get_lenght() {
    return Ship::lenght;
}
