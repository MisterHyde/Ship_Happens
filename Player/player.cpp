/************************************************************************************
 * player.cpp	v0.1																*
 * Contains the definition of the member and member functions of the player class.	*
 * A Player should be able to set and change his name, set ships and bomb the 		*
 * enemies field 																	*
 * A Player should know if he stil has ships left, where to find his board and how	*
 * to bomb his oponents field.														*
 * Matthias Pfitzmayer		140415		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140415	MP	@all	Definition of the Player class
  * 140416	MP	@all	Implementing Memberfunc of th Player class
  * 140527  MP  @all    Add doxygen comments, cleanup the file
  *
  ***********************************************************************************/

 /***********************************************************************************
  * to do:
  *
  *
  *
  ***********************************************************************************/

# include "my_headers.h"
# include "player.h"


/**
 * @brief Player::Player
 * std constructor
 * @param Player::name
 * @param Player::lost = false
 * @param Player::ready = false
 * @param Player::own_field
 */
Player::Player() {
    Player::name = "Spieler_1";
    Player::lost = false;
    Player::active = false;
    Player::own_field.clear_board();
}


/**
 * @brief Player::Player
 * special constructor using a given name
 * @param std::string _name
 */
Player::Player(std::string _name) {
    Player::name = _name;
    Player::lost = false;
    Player::active = false;
}


/**
 * @brief Player::~Player
 * destructor
 */
Player::~Player() {

}


/**
 * @brief Player::set_name
 * @param std::string _name
 * simple set function replaces player.name with the string _name
 */
void Player::set_name(std::string _name) {
    Player::name = _name;
}


/**
 * @brief Player::get_name
 * a simple getter function that returns the players name
 * @return std::string Player::name
 */
std::string Player::get_name() {
    return Player::name;
}


/**
 * @brief Player::check_lose
 * this function counts the ships that have been destroyed, by itteration over
 * all ship arrays by calling the Ship::get_alive() function. Afterwards the
 * number will be compared with the number of ships a player have. If it is
 * equal there is no ship left and the Player::lost will be set true.
 * @return bool Player::lost
 */
bool Player::check_lose() {

    size_t dest_ship_counter = 0;

    /**
     * itterate over the submarine array
     */
    for(size_t count = 0; count < Player::num_subm; count ++) {
        Submarine &subm_ref = Player::subm[count];

        if(!(subm_ref.get_ship_alive())) {
            dest_ship_counter++;
        }
    }

    /**
     * itterate over the destroyer array and
     */
    for(size_t count = 0; count < Player::num_dest; count ++) {
        Destroyer& dest_ref = Player::dest[count];
        if(!(dest_ref.get_ship_alive())) {
            dest_ship_counter ++;
        }
    }

    /**
     * itterate over the battleship array
     */
    for(size_t count = 0; count < Player::num_bash; count ++) {
        Battleship& bash_ref = Player::bash[count];

        if(!(bash_ref.get_ship_alive())) {
            dest_ship_counter ++;
        }
    }

    /**
     * itterate over the air carrier array
     */
    for(size_t count = 0; count < Player::get_num_aircarrier(); count++) {
        AirCarrier& airc_ref = Player::airc[count];

        if(!(airc_ref.get_ship_alive())) {
            dest_ship_counter ++;
        }
    }

    /**
     * compare the counter variable with the nuber of ships if it is equal
     * the bool Player::lost will be set true and the game should end
     */
    if(dest_ship_counter == (Player::num_subm + Player::num_dest + Player::num_bash + Player::num_airc)) {
        Player::lost = true;
        std::cout << "All ships were destroyed" << std::endl;
    }

    return Player::lost;
}


/**
 * Get a reference of a players board.
 * To avoid copying the whole Board into the enemies data, and to enable direct "bombing" of the enemies
 * filed we return a reference to the board
 * @return Board& _field
 */
Board& Player::return_board_ref() {
    Board& _field = Player::own_field;
    return _field;
}


/**
 * @brief Player::get_Submarine_ref
 * Returns a reference to a Submarine from the players submarine array Player::subm[_num - 1]
 * @param _num
 * @return Submarine& _subm
 */
Submarine& Player::get_Submarine_ref(size_t _num) {
    Submarine& _subm = Player::subm[_num - 1];
    return _subm;
}


/**
 * @brief Player::get_num_submarines
 * @return size_t Player::num_subm
 */
size_t Player::get_num_submarines() {
    return Player::num_subm;
}


/**
 * @brief Player::get_Destroyer_ref
 * Returns a reference to a destroyer from the players destroyer array Player::dest[_num - 1];
 * @param _num
 * @return Destroyer& _dest
 */
Destroyer& Player::get_Destroyer_ref(size_t _num) {
    Destroyer& _dest = Player::dest[_num - 1];
    return _dest;
}


/**
 * @brief Player::get_num_destroyer
 * @return size_t Player::num_dest
 * simple geter function returning the amount of destroyer
 */
size_t Player::get_num_destroyer() {
    return Player::num_dest;
}


/**
 * @brief Player::get_BattleShip_ref
 * Returns a reference to a battleship from the players battleship array Player::bash[_num - 1]
 * @param _num
 * @return Battleship& _bash
 */
Battleship& Player::get_BattleShip_ref(size_t _num) {
    Battleship& _bash = Player::bash[_num - 1];
    return _bash;
}


/**
 * @brief Player::get_num_battleships
 * @return size_t Player::num_bash
 * simple geter function returning the amount of battleships
 */
size_t Player::get_num_battleships() {
    return Player::num_bash;
}


/**
 * @brief Player::get_AirCarrier_ref
 * Returns a reference to the players air carrier from the air carrier array Player::airc[_num - 1]
 * this function should be quiet valueable for the following game class
 * @param _num
 * @return AirCarrier& _airc
 */
AirCarrier& Player::get_AirCarrier_ref(size_t _num) {
    AirCarrier& _airc = Player::airc[_num - 1];
    return _airc;
}


/**
 * @brief Player::get_num_aircarrier
 * @return size_t Player::num_airc
 * simple geter function returning the number of air carriers
 */
size_t Player::get_num_aircarrier() {
    return Player::num_airc;
}


/**
 * @brief Player::place_ship
 * @param _sq1
 * @param _sq2
 * @param _sq3
 * @param _sq4
 * @param _sq5
 * @return
 */
bool Player::place_ship(Square *_sq1, Square *_sq2, Square *_sq3, Square *_sq4, Square *_sq5) {
    bool empty;

    empty = Player::own_field.get_squares_empty(_sq1, _sq2, _sq3, _sq4, _sq5);

    if(empty) {
        Player::own_field.set_ship(_sq1, _sq2, _sq3, _sq4, _sq5);
    }
    return empty;
}


/**
 * @brief Player::bomb_enemy_field
 * enables the player to bomb the enemies field directly using the koordinates x and y
 * @param _en_field
 * @param _x
 * @param _y
 */
bool Player::bomb_enemy_field(Board& _en_field, size_t _x, size_t _y) {
    Square* _sq = _en_field.get_Square_ptr(_x, _y);
    bool free = false;

    if(!(_sq->get_square_hit())) {
        free = true;
        _sq->set_hit();
    }
    return free;
}


/**
 * @brief Player::change_activ_status
 * @see Player::check_ships
 * @see Player::check_lose
 * OBSOLETE!!!
 *
 * If a player is active he will be set not_active and the other way round
 */
void Player::change_activ_status() {
    Player::check_ships();
    Player::check_lose();
    Player::active = !(Player::active);
}


/**
 * @brief Player::set_active
 * change a players active flag to true
 */
void Player::set_active() {
    Player::check_ships();
    Player::check_lose();
    Player::active = true;
}


/**
 * @brief Player::set_not_active
 * change a players active flag to false
 */
void Player::set_not_active() {
    Player::active = false;
}


/**
 * @brief Player::get_active
 * @return Player::active
 * simple getter, returns the players active flag
 */
bool Player::get_active() {
    return Player::active;
}


/**
 * @brief Player::get_lost
 * @return Player::lost
 * a simple geter function returning the players "lost" flag if true is returned
 * the game should end.
 */
bool Player::get_lost() {
    return Player::lost;
}


/**
 * @brief Player::check_ships
 * get ships "alive" status right
 */
void Player::check_ships() {

    /**
     * check all submarines from Player::subm[]
     */
    for(size_t count = 0; count < Player::num_subm; count++) {
        if((Player::subm[count].get_ship_alive())&(Player::subm[count].get_ship_set())) {
            Player::subm[count].check_ship_stat();
        }
    }

    /**
     * check all destroyer form Player::dest[]
     */
    for(size_t count = 0; count < Player::num_dest; count++) {
        if((Player::dest[count].get_ship_alive()) & (Player::dest[count].get_ship_set())) {
            Player::dest[count].check_ship_stat();
        }
    }

    /**
     * check all battleships from Player::bash[]
     */
    for(size_t count = 0; count < Player::num_bash; count++) {
        if((Player::bash[count].get_ship_alive()) & (Player::bash[count].get_ship_set())) {
            Player::bash[count].check_ship_stat();
        }
    }

    /**
     * check all the air carrier from Player::airc[]
     */
    for(size_t count = 0; count < Player::num_airc; count ++) {
        if((Player::airc[count].get_ship_alive()) & (Player::airc[count].get_ship_set())) {
            Player::airc[count].check_ship_stat();
        }
    }
}


// help functions for console debugging purposes

/**
 * @brief Player::print_field
 * print the players field in the terminal
 */
void Player::print_field() {
    //Player::own_field.print_own_board();
}


/**
 * @brief Player::show_enemy_field
 * print the enemies field in the terminal
 * @param _en_field
 */
void Player::print_enemy_field(Board &_en_field) {
    _en_field.print_enemy_board();
}


/**
 * @brief Player::show_ships
 * prints a players ships in the terminal, 'o' means this part of a ship has not
 * been hit so far 'X' signals that this part is already destroyed
 */
void Player::print_ships() {
    for(size_t count = 0; count < Player::num_subm; count++) {
        std::cout << count + 1 << "  ";
        Player::subm[count].print_ship();
    }

    for(size_t count = 0; count < Player::num_dest; count++) {
        std::cout << count +1 << "  ";
        Player::dest[count].print_ship();
    }

    for(size_t count = 0; count < Player::num_bash; count++) {
        std::cout << count + 1 << "  ";
        Player::bash[count].print_ship();
    }

    for(size_t count = 0; count < Player::num_airc; count++) {
        std::cout << count + 1 << "  ";
       Player::airc[count].print_ship();
    }
}


/**
 * @brief Player::place_ship
 * this function may be used for all kind of ships, thats why x3 to x5 and y3 to y5 are
 * pinned to zero, because a ship needs at least two Squares of space (Submarine),
 * for each Square more another kind of ship needs to be set. Later if we work with
 * a graphic surface we will be able to replace this func. with a version working directly
 * with Squares, instead of coordinates.
 * @param _type
 * @param _num
 * @param _x1
 * @param _y1
 * @param _x2
 * @param _y2
 * @param _x3
 * @param _y3
 * @param _x4
 * @param _y4
 * @param _x5
 * @param _y5
 * @return
 */
bool Player::place_ship(Ship_Type _type, size_t _num, size_t _x1, size_t _y1, size_t _x2, size_t _y2,
                   size_t _x3, size_t _y3, size_t _x4, size_t _y4, size_t _x5, size_t _y5) {
    bool _set = false;
    Square* _sq1 = Player::own_field.get_Square_ptr(_x1, _y1);
    Square* _sq2 = Player::own_field.get_Square_ptr(_x2, _y2);
    Square* _sq3 = Player::own_field.get_Square_ptr(_x3, _y3);
    Square* _sq4 = Player::own_field.get_Square_ptr(_x4, _y4);
    Square* _sq5 = Player::own_field.get_Square_ptr(_x5, _y5);

    switch (_type) {

    // type Submarine -> lenght = 2
    case Submarine_t:
        if(Player::own_field.get_squares_empty(_sq1, _sq2)) {
            Player::own_field.set_ship(_x1, _y1, _x2, _y2);
            Player::subm[_num - 1].set_ship(Player::own_field.get_Square_ptr(_x1, _y1),
                                            Player::own_field.get_Square_ptr(_x2, _y2));
        }

        break;

    // type Destroyer -> lenght = 3
    case Destroyer_t:
        if(Player::own_field.get_squares_empty(_sq1, _sq2, _sq3)) {
            Player::dest[_num - 1].set_ship(Player::own_field.get_Square_ptr(_x1, _y1),
                                            Player::own_field.get_Square_ptr(_x2, _y2),
                                            Player::own_field.get_Square_ptr(_x3, _y3));
            Player::own_field.set_ship(_x1, _y1, _x2, _y2, _x3, _y3);
        }

        break;

     // type Battleship -> lenght = 4
     case Battleship_t:
        if(Player::own_field.get_squares_empty(_sq1, _sq2, _sq3, _sq4)) {
            Player::bash[_num -1].set_ship(Player::own_field.get_Square_ptr(_x1, _y1),
                                           Player::own_field.get_Square_ptr(_x2, _y2),
                                           Player::own_field.get_Square_ptr(_x3, _y3),
                                           Player::own_field.get_Square_ptr(_x4, _y4));
            Player::own_field.set_ship(_x1, _y1, _x2, _y2, _x3, _y3, _x4, _y4);
        }

        break;

    // type Air carrier -> lenght = 5
    case AirCarrier_t:
        if(Player::own_field.get_squares_empty(_sq1, _sq2, _sq3, _sq4, _sq5)) {
            Player::airc[_num - 1].set_ship(Player::own_field.get_Square_ptr(_x1, _y1),
                                            Player::own_field.get_Square_ptr(_x2, _y2),
                                            Player::own_field.get_Square_ptr(_x3, _y3),
                                            Player::own_field.get_Square_ptr(_x4, _y4),
                                            Player::own_field.get_Square_ptr(_x5, _y5));
            Player::own_field.set_ship(_x1, _y1, _x2, _y2, _x3, _y3, _x4, _y4, _x5, _y5);
        }

        break;
    // default for wrong ship type
    default:
        std::cout << _type << " is not a ship type" << std::endl;
    }
    return _set;
}


