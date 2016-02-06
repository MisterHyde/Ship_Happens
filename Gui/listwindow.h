#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>
#include "networkstuff.h"

namespace Ui {
class ListWindow;
}

/**
 * @brief The ListWindow class
 * \nprovide a window to enter the ip of the server\n
 * after that it connects to the server
 */
class ListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ListWindow(NetworkStuff *s, QWidget *parent);
    ~ListWindow();
    //QString getIP();
    
private:
    Ui::ListWindow *ui;
    QString ip;
    NetworkStuff *socke;

signals:
    void connected();

private slots:
    void startClicked();
    void setIP(QString i);

};

#endif // LISTWINDOW_H
