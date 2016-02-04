/************************************************************************************
 * square.h 																		*
 * Contains the definition of the square class 										*
 * Matthias Pfitzmayer		140404		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140404	MP	@all	Definition of the Square class
  *
  *
  ***********************************************************************************/

# ifndef SQUARE_H
# define SQUARE_H

# include "my_headers.h"

/**
 * @brief The Square class
 * a single pice of a board, it mainly consists of flags, that indicate it's current
 * status e.g. set, hit or disabled
 *
 * @author m-a-d
 * @version 0.1
 * @date 30. Mai 2014
 */
class Square{
private:
    bool set;       /**< the set flag. this flag indicates if something is set on this square*/
    bool hit;       /**< the hit flag. this flag signals the system if a square has already been bombed*/
    bool disabled;  /**< the disabled flag. this flag shows if interaktion with this square is possible or not*/

public:
    Square ();											// std constructor
    Square (bool _set, bool _hit, bool _disabled);		// constructor with params
    ~Square ();											// destructor

    // setting ships
    bool set_square ();
    void un_set_square ();
    bool get_square_set ();

    // hitting squares
    void set_hit ();
    void un_set_hit ();
    bool get_square_hit ();

    // disable squares so that they can't be hit or set anymore
    void set_disabled ();
    void un_set_disabled ();
    bool get_square_disabled ();
};

# endif // SQUARE_H
