/************************************************************************************
 * submarine.cpp     v0.1															*
 * Contains the members and memberfunctions of the submarine class, a subclass of   *
 * the ship class. The main difference between each kind of ship in this game is    *
 * the lenght and a submarine is a ship with 2 squares lenght.                      *
 *                                                                                  *
 *                                                                                  *
 * Matthias Pfitzmayer		140501		madmayer@gmx.net							*
 ************************************************************************************/

/***********************************************************************************
 * Changelog:
 * 140501  MP  @all    Created constructor an destructor
 * 140510  MP  @const  Reworked the constructor now using the ship.reset_ship for
 *                     params and settings
 *
 *
 *
 ***********************************************************************************/

# include "submarine.h"

/**
 * @brief Submarine::Submarine
 * std constructor
 * in this case the constructor calls the ship.reset_ship() member func. to get each
 * ship in a defined state, which is ship.alive = true, ship.set = false and
 * ship.position[0] = NULL till ship.position[ship.lenght] = NULL
 */
Submarine::Submarine() {
    Submarine::reset_ship();
}

/**
 * @brief Submarine::~Submarine
 * destructor
 */
Submarine::~Submarine() {

}


/**
 * @brief Submarine::get_lenght
 *
 * @return size_t Submarine::lenght
 */
size_t Submarine::get_lenght() {
    return Submarine::lenght;
}



size_t Submarine::get_type() {
    return Submarine::type;
}


/**
 * @brief Submarine::get_ship_set
 * @return
 */
bool Submarine::get_ship_set() {
    return Submarine::set;
}


/**
 * @brief Submarine::get_ship_alive
 * @return
 */
bool Submarine::get_ship_alive() {
    return Submarine::alive;
}


/**
 * @brief Submarine::check_ship_stat
 * @return Submarine::alive
 */
void Submarine::check_ship_stat() {
    size_t comp = 0;
    for(size_t count = 0; count < Submarine::lenght; count++) {
        if (Submarine::position[count]->get_square_hit()) {
            comp++; // increase the number of hits
        }
    }

    /**
     * compair the ammount of squares that already got hit with the
     * lenght of the ship, if they are equal the ship has been
     * destroyed, the flag Ship::alive will be set to false
     */
     if (comp == (Submarine::lenght)) {
         std::cout << "submarine has been destroyed" << std::endl;
         Submarine::alive = false;
     }
}


/**
 * @brief Submarine::set_ship
 * @param _sq1
 * @param _sq2
 */
void Submarine::set_ship(Square* _sq1, Square* _sq2) {
    Submarine::position[0] = _sq1;
    Submarine::position[1] = _sq2;
    Submarine::set = true;
}


/**
 * @brief Submarine::reset_ship
 */
void Submarine::reset_ship() {
    Submarine::alive = true;
    Submarine::set = false;

    // delete the saved positions of the submarine
    for(size_t count = 0; count < Submarine::lenght; count++){
        Submarine::position[count] = NULL;
    }
}


/**
 * @brief Submarine::print_ship
 */
void Submarine::print_ship() {
    for(size_t count = 0; count < (Submarine::lenght); count++) {

        if (Submarine::position[count]->get_square_hit()) {
            std::cout << "X";
        }
        else {
            std::cout << "o";
        }
    }
    std::cout << std::endl;
}
