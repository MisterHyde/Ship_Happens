#include "listwindow.h"
#include "ui_listwindow.h"

/**
 * @brief ListWindow::ListWindow
 * @param s
 * @param parent
 * Constructor
 */
ListWindow::ListWindow(MySocket *s, QWidget *parent) :
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
 * Deconstructor
 */
ListWindow::~ListWindow()
{
    delete ui;
}

/**
 * @brief ListWindow::startClicked
 * slot connected to the StartButton
 * opens a TcpSocket with the given ip adress of the server and prints an error if the connection failed
 */
void ListWindow::startClicked()
{
    ui->label_2->setText("Verbinden...");
    if(socke->Start_Socket(ip)){
        emit connected();
    }
    else
        ui->label_2->setText("Socket konnte nicht gestartet werden.");
}

/**
 * @brief ListWindow::setIP
 * @param i
 * slot connected to the lineEdit
 * saves the in lineEdit entered ip adress in the attribute ip
 */
void ListWindow::setIP(QString i)
{
    ip = i;
}

