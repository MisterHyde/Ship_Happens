/**********************************************************************************
 * Main Player including testing v0.5											  *
 * 																				  *
 * Matthias Pfitzmayer		PM SoSe 2014							  15.05.2014  *
 **********************************************************************************/

/***********************************************************************************
  * Changelog:
  * 140511  MP  @all        started using doxygen documentation functions
  * 140511  MP  @player.h   tried to work around the player.set_ship problem didn't
  *                         work so well...
  * 140515  MP  @player.h   player.set_ship works finally...
  *
  **********************************************************************************/

/***********************************************************************************
 * to do:
 * 140515   @player.h   rework the player.set_ship() for the use of Square* and Ship&
 *
 *
 *
 **********************************************************************************/

# include "my_headers.h"
# include "game.h"
#include "setwindow.h"
#include "startwindow.h"
#include <QApplication>

using namespace std;

int main (int argc, char *argv[]) {

   QApplication a(argc, argv);

   StartWindow startW;

   startW.setWindowTitle("Ship Happens");
   startW.setWindowIcon(QPixmap("images/ship.png"));
   startW.show();

   return a.exec();
    /*
    Game game;

    game.change_player_names();

    //game.player_set_ship_routine();

    //game.enemy_set_ship_routine();

    // use test ot routine
    // the test set ships to specified squares

    game.player_set_ship_test();

    game.enemy_set_ship_test();

    game.bomb_field_routine();

    return 0;
    */
}
