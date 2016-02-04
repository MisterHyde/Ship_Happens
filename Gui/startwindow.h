#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "Gui/setwindow.h"
#include "Gui/listwindow.h"
#include "playwindow.h"
#include "myserver.h"
#include "mysocket.h"
#include <QMainWindow>
#include <QString>
#include <QDebug>

namespace Ui {
class StartWindow;
}

/**
 * @brief The StartWindow class
 * the StartWindow-class provides all the objects of the other windows and
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
    MyServer *server;
    MySocket *socket;
    bool host;
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
