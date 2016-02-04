/************************************************************************************
 * battleship.cpp       v0.1														*
 * the battleship class, a subclass of ship with a lenght of 4 squares.             *                                                            *
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

# include "battleship.h"


/**
 * @brief Battleship::Battleship
 * std constructor
 * @param bool Battleship::alive = true
 * @param bool Battleship::set = false
 */
Battleship::Battleship() {
    Battleship::reset_ship();
}


/**
 * @brief Battleship::~Battleship
 * destructor
 */
Battleship::~Battleship() {

}


/**
 * @brief Battleship::get_lenght
 * @return size_t Battleship::lenght
 * simple geter functioin returning the battleships lenght measured in squares
 * battleship.lenght = 4
 */
size_t Battleship::get_lenght() {
    return Battleship::lenght;
}


/**
 * @brief Battleship::get_type
 * @return size_t type
 * simple geter function returning a ships type battleship = 3
 */
size_t Battleship::get_type() {
    return Battleship::type;
}


/**
 * @brief Battleship::get_ship_set
 * @return bool Battleship::set
 * simple geter function that returns the set flag of a battleship
 */
bool Battleship::get_ship_set() {
    return Battleship::set;
}


/**
 * @brief Battleship::get_ship_alive
 * @return bool Battleship::alive
 * simple geter function that returns the alive flag of a battleship
 */
bool Battleship::get_ship_alive() {
    return Battleship::alive;
}


/**
 * @brief Battleship::check_ship_stat
 * this member function itterates over all of the Squares of the position
 * array, and checks if the ship has been hit by calling the
 * @see Board::get_square_hit
 */
void Battleship::check_ship_stat() {
    size_t comp = 0;

    /**
     * count the squares that already got hit
     */
    for(size_t count = 0; count < Battleship::lenght; count++) {
        if (Battleship::position[count]->get_square_hit()) {
            comp++; // increase the number of hits
        }
    }

    /**
     * compair the ammount of squares that already got hit with the
     * lenght of the ship, if they are equal the ship has been
     * destroyed, the flag Ship::alive will be set to false
     */
     if (comp == (Battleship::lenght)) {
         std::cout << "Battleship has been destroyed" << std::endl;
         Battleship::alive = false;
     }
}


/**
 * @brief Battleship::reset_ship
 * a function that is called to put a battleship in a defined status
 * Battleship::alive = ture  <- the battleship has not been destroyed
 * Battleship::set   = false <- the battleship has not been set yet
 * set all the Square pointers of the position array NULL
 * Battleship::position[0] -> Battleship::position[lenght] = NULL
 */
void Battleship::reset_ship() {
    Battleship::alive = true;
    Battleship::set = false;

    // delete the saved positions of the ship
    for(size_t count = 0; count < Battleship::lenght; count++){
        Battleship::position[count] = NULL;
    }
}


/**
 * @brief Battleship::set_ship
 * @param _sq1
 * @param _sq2
 * @param _sq3
 * @param _sq4
 * This function should only be called if you already checked if the Squares are empty!
 * @see Board::get_squares_empty
 * Each position pointer of the battleship get its own value and now you are able to check
 * the air carriers condition by calling the Battleship::check_ship_stat
 */
void  Battleship::set_ship(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4) {
  Battleship::position[0] = _sq1;
  Battleship::position[1] = _sq2;
  Battleship::position[2] = _sq3;
  Battleship::position[3] = _sq4;
  Battleship::set = true;
}


/**
 * @brief Battleship::print_ship
 * Help function for terminal debugging
 * prints the ship in the terminal, using 'X' for destroyed parts and 'o' for the others, each
 * char represents a square the ship is placed on.
 */
void Battleship::print_ship() {
    if(Battleship::set) {
        for(size_t count = 0; count < (Battleship::lenght); count++) {
            if (Battleship::position[count]->get_square_hit()) {
                std::cout << "X";
            }
            else {
                std::cout << "o";
            }
        }
        std::cout << std::endl;
    }
}
