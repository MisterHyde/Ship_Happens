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
#include <QString>
#include <QDebug>

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
    
private:
    Ui::StartWindow *ui;

    QString name;
    QString enemyName;
    ListWindow *listW;
    SetWindow *setW;
    PlayWindow *playW;
    NetworkStuff *socket;
    bool host;
    bool gameStarted; // Flag to prevent multiple instances of the playWindow
    bool connected;
    int numb;

signals:
    void setStartActivity(bool);

private slots:
    void getUserName();

public slots:

    void openGame();
    void joinGame();
    void listWindowClosed();
    void startGame();
    void revenge();
    void showListWindow(); ///< A slot which shows the listWindows if the socket wants to reconnect to another ip
};

#endif //GRAPHIC
#endif // STARTWINDOW_H
