/************************************************************************************
 * square.cpp																		*
 * Contains the members and member functions of the square class 					*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140424	MP	@all		Created std. get-er and set-er func.
  * 140404	MP	@all		Tested std. func.
  * 140408	MP	@set_ship	a few smal adjustments
  *
  ***********************************************************************************/

# include "square.h"


/**
 * @brief Square::Square
 * std constructor.
 * a new square which has nothing set, which was not hit and is not disabled will be created
 * @param Square::set = false
 * @param Square::hit = false
 * @param Square::disabled = false
 */
Square::Square() {
    Square::set = false;
    Square::hit = false;
    Square::disabled = false;
}


/**
 * @brief Square::Square
 * Constructor for specific purposes (testing).
 * a new square with given flags will be created
 * @param bool _set         -> Square::set
 * @param bool _hit         -> Square::hit
 * @param bool _disabled    -> Square::disabled
 */
Square::Square(bool _set,bool _hit,bool _disabled) {
    Square::set = _set;
    Square::hit = _hit;
    Square::disabled = _disabled;
}


/**
 * @brief Square::~Square
 * destructor
 */
Square::~Square() {

}


/**
 * @brief Square::set_square
 * Set a ship onto a sqare.
 * If a ship is placed onto a square the Member Square::set will be set true
 * @return true if set flag has been toggled to true
 */
bool Square::set_square() {
    if (!(Square::disabled)) {
        Square::set = true;
        return true;
    }
    // exeption for repeated try needed
    else if (Square::set == true) {
        std::cout << "this square already is in use!" << std::endl;
        return false;
    }

    // exeption for disabled square needed
    return false;
}


/**
 * @brief Square::un_set_square
 * removes set flag from the square.
 * if the set flag has been removed Square::set will set back to false
 * this can be of use in a cleanup routine or to re-start a game.
 */
void Square::un_set_square() {
    Square::set = false;
}


/**
 * @brief Square::get_square_set
 * checks if square is set.
 * this member function will be used to get to know if there is something
 * set on this square or not, it returns the value of the Square::set flag
 * @return Square::set
 */
bool Square::get_square_set() {
    return Square::set;
}


/**
 * @brief Square::set_hit
 * square got hit.
 * if a square got thit the member Square::hit will be set true
 */
void Square::set_hit() {
    if(!(Square::disabled)) {
            Square::hit = true;
    }
}


/**
 * @brief Square::un_set_hit
 * removes the hit flag from the square.
 * if the hit flag has been removed the hit square will set back to false
 * this can be of use in a cleanup routine or to re-start a game.
 */
void Square::un_set_hit() {
    Square::hit = false;
}


/**
 * @brief Square::get_square_hit
 * checks if square is hit, basically returns the value of the Square::hit flag
 * @return bool Square::hit
 */
bool Square::get_square_hit() {
    return Square::hit;
}


/**
 * @brief Square::set_disabled
 * disable square.
 * this member function will disable a square, by setting the Square::disabled flag true,
 * this can be used later on to manipulate the field e.g. put islands (a number of disabled squares)
 * on a field and make the game more difficult
 */
void Square::set_disabled () {
    Square::disabled = true;
}


/**
 * @brief Square::un_set_disabled
 * Enables square.
 * if the disable flag has been removed you are allowed to use a Square again
 * this can be of use in a cleanup routine or to re-start a game.
 */
void Square::un_set_disabled() {
    Square::disabled = false;
}


/**
 * @brief Square::get_square_disabled
 * Checks if square is disabled.
 * if the square is disabled this member func. will return true, otherwise it will return false
 * @return bool Square::disabled
 */
bool Square::get_square_disabled() {
    return Square::disabled;
}
