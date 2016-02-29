#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "game.h"
#include <QPainter>
#include "enddialog.h"
#include "networkstuff.h"

namespace Ui {
class PlayWindow;
}

/**
 * @brief The PlayWindow class
 * \nthis is the class for the Window where the game acctually happens\n
 * it contains two QTableWidgets which are use as boards the left is the board of the player\n
 * and on the left the enemy board is displayed to get bombed by the player
 */
class PlayWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayWindow(bool h, Game _game, NetworkStuff *pSocket, QWidget *parent);
    ~PlayWindow();
    

private:
    Ui::PlayWindow *ui;
    //Player player;
    //Player enemy;
    Game game;
    Board &playerBoard;
    Board &enemyBoard;
    int sqSize;
    int width;
    int height;
    QTableWidget *playerTmp;
    QColor black, red;
    QPen pen;
    QPainter painter;
    EndDialog *endD;
    bool host;
    QImage templatBlue;
    QImage templatBlack;
    int countOwn;   /// the amount of not bombed with own ships occupied squares
    int countOther; /// the amount of not bombed with enemy ships occupied squares
    NetworkStuff *socket;

    void tableManagement();
    void setShips();
    void countSet();

signals:
    void quitSignal();

private slots:
    void setBomb(int row, int column);
    void getBombed(int row, int column);
    void boardReceived(char *board);

public slots:
    //void setGameRef(Game &_game);
    //void getStartActivity(bool);
    void revenge();
    //void quitGame();
};

#endif // PLAYWINDOW_H
