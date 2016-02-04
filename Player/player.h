/************************************************************************************
 * player.h v0.3																	*
 * Contains the definition of the player class 										*
 *                                                                                  *
 * Matthias Pfitzmayer		140415		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140415	MP	@all	Definition of the Board class
  *
  *
  ***********************************************************************************/

# ifndef PLAYER_H
# define PLAYER_H

# include "my_headers.h"
# include "board.h"
# include "Ships/submarine.h"
# include "Ships/destroyer.h"
# include "Ships/battleship.h"
# include "Ships/air_carrier.h"

/**
 * @brief The Player class
 * @author m-a-d
 * @version 0.1
 *
 * The player class implements the information and operations a player performs in the
 * game battleships. It also contains the possible ways of player interaction with the
 * Board and his enemy.
 */
class Player {
private:
    std::string name;                   /**< Player name */
    bool lost;                          /**< Bool lost. will be set true if all ships
                                             are destroyed */
    bool active;                        /**< Bool active. indicates if a player has
                                             finished his turn*/
    Board own_field;                    /**< Board own_field. a board object where the
                                             informations of the current field are stored*/
    static size_t const num_subm = 5;   /**< The number of Submarines*/
    static size_t const num_dest = 4;   /**< The number of Destoyer*/
    static size_t const num_bash = 3;   /**< The number of Battleships*/
    static size_t const num_airc = 1;   /**< The number of Air Carriers*/

    Submarine subm[num_subm];           /**< Array of submarines*/
    Destroyer dest[num_dest];           /**< Array of destroyer*/
    Battleship bash[num_bash];          /**< Array of battleships*/
    AirCarrier airc[num_airc];          /**< Array of air carrier*/

protected:
    void check_ships();
    bool check_lose();


public:

    Player ();                      // std. constructor
    Player (std::string _name);     // specific constructor using a given name
    ~Player ();                     // destructor

    // manipulation Player::name
    void set_name();
    void set_name(std::string _name);
    std::string get_name();

    size_t get_num_submarines();
    size_t get_num_destroyer();
    size_t get_num_battleships();
    size_t get_num_aircarrier();

    // basic player abilitie

    bool bomb_enemy_field(Board& _en_field, size_t _x, size_t _y);

    void change_activ_status();
    void set_active();
    void set_not_active();

    bool get_active();
    bool get_lost();

    bool place_ship(Square* _sq1, Square* _sq2, Square* _sq3 = NULL, Square* _sq4 = NULL, Square* _sq5 = NULL);


    // member func. that return references to the players member objects
    // to enable easy and direct interaction with the board and the ships
    Board& return_board_ref();
    Submarine& get_Submarine_ref(size_t _num);
    Destroyer& get_Destroyer_ref(size_t _num);
    Battleship& get_BattleShip_ref(size_t _num);
    AirCarrier& get_AirCarrier_ref(size_t _num);

# ifndef GRAPHIC
    // member func. for testing purposes
    void print_field();
    void print_enemy_field(Board& _en_field);
    void print_ships();
    bool place_ship(Ship_Type _type, size_t _num, size_t _x1, size_t _y1, size_t _x2, size_t _y2,
                    size_t _x3 = 0, size_t _y3 = 0, size_t _x4 = 0, size_t _y4 = 0, size_t _x5 = 0, size_t _y5 = 0);
# endif // GRAPHIC
};

# endif // PLAYER_H
