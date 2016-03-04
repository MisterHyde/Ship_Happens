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

    waitForRevenge = false;
    revengeRequested = false;

    setW = new SetWindow(this);
    numb = 0;
    gameStarted = false;

    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(getUserName()));
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
void StartWindow::getUserName()
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
    setW->setEnemyName(enemyName);
    setW->setNetwork(socket, true);
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
    connect(socket, SIGNAL(connectingToHost()), this, SLOT(showListWindow()));
    numb += 1;
    listW = new ListWindow(socket,this);
    host = false;
    listW->show();
    hide();
}

/**
 * @brief StartWindow::showListWindow
 * \nslot which shows the listWindows if the socket wants to reconnect to another ip
 */
void StartWindow::showListWindow()
{
    listW = new ListWindow(socket, this);
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
    setW->setNetwork(socket, false);
    socket->requestName(name);
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

        connect(playW, SIGNAL(gameEnded(bool)), this, SLOT(gameEnded(bool)));
        connect(socket, SIGNAL(revengeReceived(bool)), this, SLOT(revengeReceived(bool)));
    }
}

/**
 * @brief StartWindow::revenge
 * @param pRev
 * \nslot connected to the quitSignal of the revenge() slot in PlayWindow\n
 * close the PlayWindow\n
 * delete the PlayWindow and the SetWindow\n
 * creat and show a new SetWindow
 */
void StartWindow::revenge(QAbstractButton* button)
{
    gameStarted = false;

    bool rev;
    if(button->text() == "&Yes"){
        waitForRevenge = true;
        rev = true;
    }
    else
        rev = false;

    socket->sendRevenge(rev);

    if(rev && revengeRequested){
        disconnect(playW, SIGNAL(gameEnded(bool)), this, SLOT(gameEnded(bool)));
        delete playW;
        delete setW;
        delete endD;
        setW = new SetWindow(this);
        setW->setNetwork(socket, host);
        setW->setWindowTitle("Ship Happens!");
        socket->nameRequest(name);//        setW->setPlayerName(name);
//        setW->setEnemyName(enemyName);
        setW->show();
        waitForRevenge = false;
        revengeRequested = false;
    }
    else if(!rev){
        delete socket;
        delete playW;
        delete setW;
        delete endD;
        this->deleteLater();
    }
}

/**
 * @brief StartWindow::revengeReceived
 * @param pRev
 * \nDoes the same as the revenge() slot except that this slot is called when a REVENGE message is received
 */
void StartWindow::revengeReceived(bool pRev)
{
    if(pRev && waitForRevenge){
        disconnect(playW, SIGNAL(gameEnded(bool)), this, SLOT(gameEnded(bool)));
        delete playW;
        delete setW;
        delete endD;
        setW = new SetWindow(this);
        setW->setNetwork(socket, host);
        setW->setWindowTitle("Ship Happens!");
        setW->setPlayerName(name);
        setW->setEnemyName(enemyName);
        setW->show();
        waitForRevenge = false;
        revengeRequested = false;
    }
    else if(pRev){
        revengeRequested = true;
    }
    else if(!pRev){
        delete socket;
        delete playW;
        delete setW;
        delete endD;
        this->deleteLater();
    }
}

void StartWindow::gameEnded(bool pWin){
    endD = new EndDialog(name, pWin, this);
    endD->show();
}
