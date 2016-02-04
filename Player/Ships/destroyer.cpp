/************************************************************************************
 * destroyer.cpp        v0.1    													*
 * The destroyer class is a subclass of ship, with a lenght of 3                    *
 *                                                                                  *
 * Matthias Pfitzmayer		140401		madmayer@gmx.net							*
 ************************************************************************************/

/************************************************************************************
 * Changelog:
 * 140501  MP  @all    Created constructor an destructor
 *
 *
 *
 ************************************************************************************/

#include "destroyer.h"


/**
 * @brief Destroyer::Destroyer
 * std constuctor
 * @param bool Destroyer::alive = true
 * @param bool Destroyer::set = false
 */
Destroyer::Destroyer() {
    Destroyer::reset_ship();
}


/**
 * @brief Destroyer::~Destroyer
 * destructor
 */
Destroyer::~Destroyer() {

}


/**
 * @brief Destroyer::get_lenght
 * @return size_t Destroyer::lenght
 * simple geter functioin returning the battleships lenght measured in squares
 * destroyer.lenght = 3
 */
size_t Destroyer::get_lenght() {
    return Destroyer::lenght;
}


/**
 * @brief Destroyer::get_type
 * simple geter function returning a ships type Destroyer = 2
 * @return
 */
size_t Destroyer::get_type() {
    return Destroyer::type;
}


/**
 * @brief Destroyer::get_ship_set
 * @return Destroyer::set
 * simple geter function that returns the set flag of a destroyer
 */
bool Destroyer::get_ship_set() {
    return Destroyer::set;
}


/**
 * @brief Destroyer::check_ship_stat
 * this member function itterates over all of the Squares of the position
 * array, and checks if the ship has been hit by calling the
 * @see Square::get_square_hit
 */
void Destroyer::check_ship_stat() {
    size_t comp = 0;

    /**
     * count the squares that already got hit
     */
    for(size_t count = 0; count < Destroyer::lenght; count++) {
        if (Destroyer::position[count]->get_square_hit()) {
            comp++; // increase the number of hits
        }
    }

    /**
     * compair the ammount of squares that already got hit with the
     * lenght of the ship, if they are equal the ship has been
     * destroyed, the flag Ship::alive will be set to false
     */
     if (comp == (Destroyer::lenght)) {
         std::cout << "Destroyer has been destroyed" << std::endl;
         Destroyer::alive = false;
     }
}


/**
 * @brief Destroyer::get_ship_alive
 * @return Destroyer::alive
 * simple geter function that returns the alive flag of a destroyer
 */
bool Destroyer::get_ship_alive() {
    return Destroyer::alive;
}


/**
 * @brief Destroyer::set_ship
 * @param _sq1
 * @param _sq2
 * @param _sq3
 */
void Destroyer::set_ship(Square* _sq1, Square* _sq2, Square* _sq3) {
    Destroyer::position[0] = _sq1;
    Destroyer::position[1] = _sq2;
    Destroyer::position[2] = _sq3;
    Destroyer::set = true;
}


/**
 * @brief Destroyer::reset_ship
 * a function that is called to put a destroyer in a defined status
 * Destroyer::alive = ture  <- the destroyer has not been destroyed
 * Destroyer::set   = false <- the destroyer has not been set yet
 * set all the Square pointers of the position array NULL
 * Destroyer::position[0] -> Destroyer::position[lenght] = NULL
 */
void Destroyer::reset_ship() {
     Destroyer::alive = true;
     Destroyer::set = false;

     // delete the saved positions of the ship
     for(size_t count = 0; count < Destroyer::lenght; count++){
         Destroyer::position[count] = NULL;
     }
}

/**
 * @brief Destroyer::print_ship
 * help function for terminal debuging
 * prints the ship in the terminal, using 'X' for destroyed parts and 'o' for the others, each
 * char represents a square the ship is placed on.
 */
void Destroyer::print_ship() {
    for(size_t count = 0; count < (Destroyer::lenght); count++) {
        if (Destroyer::position[count]->get_square_hit()) {
            std::cout << "X";
        }
        else {
            std::cout << "o";
        }
    }
    std::cout << std::endl;
}
