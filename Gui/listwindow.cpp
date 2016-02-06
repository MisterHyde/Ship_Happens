#include "listwindow.h"
#include "ui_listwindow.h"

/**
 * @brief ListWindow::ListWindow
 * @param s
 * @param parent
 * \nConstructor
 */
ListWindow::ListWindow(NetworkStuff *s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    socke = s;
    setWindowTitle("Server wahl");
    setWindowIcon(QPixmap("images/ship.png"));

    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(ui->CancleButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(setIP(QString)));
    connect(this, SIGNAL(connected()), parent, SLOT(listWindowClosed()));
}

/**
 * @brief ListWindow::~ListWindow
 * \nDeconstructor
 */
ListWindow::~ListWindow()
{
    delete ui;
}

/**
 * @brief ListWindow::startClicked
 * \nslot connected to the StartButton\n
 * opens a TcpSocket with the given ip adress of the server and prints an error if the connection failed
 */
void ListWindow::startClicked()
{
    ui->label_2->setText("Verbinden...");
    socke->startSocket(ip); // == QAbstractSocket::ConnectedState;
        emit connected();
        //socke->sendShot((quint16)8,(quint16)9);
    //}
    //else
    //    ui->label_2->setText("Socket konnte nicht gestartet werden.");
}

/**
 * @brief ListWindow::setIP
 * @param i
 * \nslot connected to the lineEdit\n
 * saves the in lineEdit entered ip adress in the attribute ip
 */
void ListWindow::setIP(QString i)
{
    ip = i;
}

