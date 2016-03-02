/*******************************************************************************
 * Window where you can choose your username and if you're the host or client  *
 * Author: Felix Fischer                                                       *
 *******************************************************************************/
#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#ifndef GRAPHIC
#define GRAPHIC

#include "Gui/setwindow.h"
#include "Gui/listwindow.h"
#include "playwindow.h"
//#include "myserver.h"
//#include "mysocket.h"
#include "networkstuff.h"
#include "enddialog.h"
#include <QString>
#include <QDebug>
#include <execinfo.h>

namespace Ui {
class StartWindow;
}

/**
 * @brief The StartWindow class
 * \nhe StartWindow-class provides all the objects of the other windows and
 */
class StartWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();
    void setName(QString pName){name = pName;}
    QString getName(){return name;}
    void setEnemyName(QString pName){enemyName = pName;}
    QString getEnemyName(){return enemyName;}
    void setConnected(bool pConnected){connected = pConnected;}
    bool getConnected(){return connected;}
    void printTrace(void);
    
private:
    Ui::StartWindow *ui;

    QString name;
    QString enemyName;
    ListWindow *listW;
    SetWindow *setW;
    PlayWindow *playW;
    NetworkStuff *socket;
    EndDialog *endD;
    bool host;
    bool gameStarted; // Flag to prevent multiple instances of the playWindow
    bool connected;
    int numb;

    bool waitForRevenge;    ///< Flag which indicates that you sent your opponent a revenge request
    bool revengeRequested;  ///< Flag which says if the other players requested a revenge game

signals:
    void setStartActivity(bool);

private slots:
    void getUserName();
    void revengeReceived(bool pRev);

public slots:
    void openGame();
    void joinGame();
    void listWindowClosed();
    void startGame();
    //void revenge(bool pRev);
    void showListWindow(); ///< A slot which shows the listWindows if the socket wants to reconnect to another ip
    void gameEnded(bool pWin);
    void revenge(QAbstractButton *button);
};

#endif //GRAPHIC
#endif // STARTWINDOW_H
