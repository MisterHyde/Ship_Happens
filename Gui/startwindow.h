/*******************************************************************************
 * Window where you can choose your username and if you're the host or client  *
 * Author: Felix Fischer                                                       *
 *******************************************************************************/
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

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
    
private:
    Ui::StartWindow *ui;

    QString name;
    ListWindow *listW;
    SetWindow *setW;
    PlayWindow *playW;
    NetworkStuff *socket;
    //NetworkStuff *server;
    bool host;
    bool gameStarted; // Flag to prevent multiple instances of the playWindow
    int numb;

signals:
    void setStartActivity(bool);

private slots:
    void getName();

public slots:

    void openGame();
    void joinGame();
    void listWindowClosed();
    void startGame();
    void revenge();
};

#endif // STARTWINDOW_H
