#include "Gui/startwindow.h"
#include "ui_startwindow.h"


/**
 * @brief StartWindow::StartWindow
 * @param parent
 * \nConstructor of the StartWindow-class\n
 * connects the signals of the Buttons and the LineEdit
 */
StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setW = new SetWindow(this);
    numb = 0;
    gameStarted = false;

    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(getName()));
    connect(ui->startGameButton, SIGNAL(clicked()), this, SLOT(openGame()));
    connect(ui->joinGameButton, SIGNAL(clicked()), this, SLOT(joinGame()));
}

/**
 * @brief StartWindow::~StartWindow
 * \nDeconstructor
 */
StartWindow::~StartWindow()
{
    delete ui;
}

/**
 * @brief StartWindow::getName
 * @param n
 * \nsaves the name if the user entered it in the lineEdit
 */
void StartWindow::getName()
{
    name = ui->lineEdit->text();
}

/**
 * @brief StartWindow::openGame
 * \nslot connected to the StartGame-Button\n
 * show the SetWindow and hides the StartWindow
 */
void StartWindow::openGame()
{
    socket = new NetworkStuff("server",this);
    numb += 1;
    ui->statusBar->showMessage(tr("Wait for network stuff."));
    host = true;
    if(numb == 1)

    setW->setWindowTitle("Ship Happens!");
    setW->setPlayerName(name);
    setW->setHost(socket);
    setW->show();
    hide();
}

/**
 * @brief StartWindow::joinGame
 * \nslot connected to the join-Button\n
 * creats and shows a ListWindow and hide the StartWindow
 */
void StartWindow::joinGame()
{
    socket = new NetworkStuff("client",this);
    numb += 1;
    listW = new ListWindow(socket,this);
    host = false;
    listW->show();
    hide();
}

/**
 * @brief StartWindow::listWindowClosed
 * \nslot connected to the Verbinden-Button in the ListWindow\n
 * close and delete the ListWindow\n
 * shows the SetWindow
 */
void StartWindow::listWindowClosed()
{
    listW->close();
    delete listW;
    setW->setWindowTitle("Ship Happens!");
    setW->setClient(socket);
    setW->show();
}

/**
 * @brief StartWindow::startGame
 * \nslot connected to the Start-Button in the SetWindow of the Host\n
 * close the SetWindow\n
 * creat and show the PlayWindow
 */
void StartWindow::startGame()
{
    if(!gameStarted){
        playW = new PlayWindow(host, setW->getGameRef(), socket, this);
        setW->close();
        playW->show();
        gameStarted = true;
    }
}

/**
 * @brief StartWindow::revenge
 * \nslot connected to the quitSignal of the revenge() slot in PlayWindow\n
 * close the PlayWindow\n
 * delete the PlayWindow and the SetWindow\n
 * creat and show a new SetWindow
 */
void StartWindow::revenge()
{
    if(1){  //Abfrage ob beide Spieler revange wollen
        playW->close();
        delete playW;
        delete setW;
        setW = new SetWindow(this);
        if(host)
            setW->setHost(socket);
        else
            setW->setClient(socket);
        setW->show();
    }
}

