#include "Gui/setwindow.h"
#include "ui_setwindow.h"
#include "my_headers.h"

// Replace this with the current ini. list to get real ships
//    left("images/left.png"), hmiddle("images/hmiddle.png"),right("images/right.png"),
//    top("images/top.png"), vmiddle("images/vmiddle.png"), bottom("images/bottom.png")

/**
 * @brief SetWindow::SetWindow
 * @param parent
 * Constructor of the SetWindow-class
 */
SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    uii(new Ui::SetWindow),
    left("images/white.png"), hmiddle("images/white.png"),right("images/white.png"),
    top("images/white.png"), vmiddle("images/white.png"), bottom("images/white.png")
{
    sub=5;
    dest=4;
    batt=3;
    air=1;
    horizontal = true;
    width = 10;
    height = 10;
    sqSize = 47;
    occupied = false;
    board = new char[100];

    uii->setupUi(this);
    uii->shipTable->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    uii->statusbar->showMessage("Plazieren Sie Ihre Schiffe.");
    uii->submarineButton->setText("U-Boot " + QString::number(sub) + "x");
    uii->destroyerButton->setText("Zerstoerer " + QString::number(dest) + "x");
    uii->battleButton->setText("Schlachtschiff " + QString::number(batt) + "x");
    uii->airCarrierButton->setText("Flugzeugtraeger " + QString::number(air) + "x");
    uii->fieldTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    uii->fieldTable->setDragDropOverwriteMode(true);
    uii->fieldTable->setDragDropMode(QAbstractItemView::DropOnly);
    uii->shipTable->setDragEnabled(true);
    setWindowIcon(QPixmap("images/ship.png"));
    setWindowTitle("Ship Happens");

    std::string enemyN = "Ganzer Peter";
    game.change_enemy_name(enemyN);
    tableManagement();
    if(host)
        uii->startButton->setText("Start");
    else
        uii->startButton->setText("Bereit");

    connect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
    connect(uii->destroyerButton, SIGNAL(clicked()), this, SLOT(selectDestroyer()));
    connect(uii->submarineButton, SIGNAL(pressed()), this, SLOT(selectSubmarine()));
    connect(uii->battleButton, SIGNAL(clicked()), this, SLOT(selectBattleship()));
    connect(uii->directionButton, SIGNAL(clicked()), this, SLOT(changeDirection()));
    connect(uii->startButton, SIGNAL(clicked()), this, SLOT(checkSet()));
    connect(this, SIGNAL(startGame()), parent, SLOT(startGame()));
    connect(uii->airCarrierButton, SIGNAL(clicked()), this, SLOT(selectAirCarrier()));
    connect(uii->shipTable, SIGNAL(itemSelectionChanged()), uii->shipTable, SLOT(selectAll()));
}

/**
 * @brief SetWindow::~SetWindow
 * Deconstructor
 */
SetWindow::~SetWindow()
{
    delete uii;
    delete board;

}

void SetWindow::getBoard(){
    if(host){
        game.receive_enemy_board_from_network(server->Receive_Board());
    }
}

/**
 * @brief SetWindow::checkSet
 * Slot that checks if all ships are set
 * sends the board to the network
 * emits the startGame() to start the PlayWindow
 */
void SetWindow::checkSet()
{
    if((sub == -1) && (dest == -1) && (batt == -1) && (air == -1)){
        if(host){
            game.receive_enemy_board_from_network(game.send_board_to_network(board));
            //server->Send_Board(game.send_board_to_network(board));

        }
        else{
            socket->Send_Board(game.send_board_to_network(board));
        }
        emit startGame();
    }
    else
        uii->statusbar->showMessage("Es muessen erst alle Schiffe plaziert werden.",5000);
}

/**
 * @brief SetWindow::getItems
 * @param item
 * Saves the items witch are changed trough the dropEvent in a QList
 */
void SetWindow::getItems(QTableWidgetItem *item)
{
    squareList.append(game.getBoardRef().get_Square_ptr((size_t)item->column()+1,(size_t)item->row()+1));
    itemList << item;
    int row = item->row();
    int column = item->column();
    if(itemList.size() == zaehler){
        for(int i=squareList.size();i<5;i++){
            squareList.append(NULL);
        }
            setPlayerShip();
    }
}

void SetWindow::oneStepBack(){
    disconnect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
    for(int i=0;i<zaehler;i++){
        if(squareList[i]->get_square_set()){
            itemList[i]->setBackgroundColor(Qt::black);
            int row = itemList[i]->row();
            int column = itemList[i]->column();
        }
        else{
            itemList[i]->setBackgroundColor(Qt::blue);
            int row = itemList[i]->row();
            int column = itemList[i]->row();
        }
    }
    connect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
    squareList.clear();
}

/**
 * @brief SetWindow::setPlayerShip
 * calls the place_ships function of the game-class (logic)
 */
void SetWindow::setPlayerShip()
{
    Square *sq1 = squareList[0];
    Square *sq2 = squareList[1];
    Square *sq3 = squareList[2];
    Square *sq4 = squareList[3];
    Square *sq5 = squareList[4];
    switch(zaehler){
        case 2:
            if(!game.place_ships(sq1,sq2)){
                uii->statusbar->showMessage("Hier kann kein Schiff gesetzt werden.",3000);
                oneStepBack();
            }
            else{
                game.getPlayer().get_Submarine_ref(sub).set_ship(sq1,sq2);
                squareList.clear();
                sub -= 1;
                uii->submarineButton->setText("Submarine " + QString::number(sub) + "x");
            }
            break;
        case 3:

            if(!game.place_ships(sq1,sq2,sq3)){
                oneStepBack();
                uii->statusbar->showMessage("Hier kann kein Schiff gesetzt werden.",3000);
            }
            else{
                game.getPlayer().get_Destroyer_ref((size_t)dest).set_ship(sq1,sq2,sq3);
                squareList.clear();
                dest -= 1;
                uii->destroyerButton->setText("Zerstoerer " + QString::number(dest) + "x");
            }

            break;
        case 4:
            if(!game.place_ships(sq1,sq2,sq3,sq4)){
                uii->statusbar->showMessage("Hier kann kein Schiff gesetzt werden.",3000);
                oneStepBack();
            }
            else{
                game.getPlayer().get_BattleShip_ref(batt).set_ship(sq1,sq2,sq3,sq4);
                squareList.clear();
                batt -= 1;
                uii->battleButton->setText("Schlachtschiff " + QString::number(batt) + "x");
            }
            break;
        case 5:
            if(!game.place_ships(sq1,sq2,sq3,sq4,sq5)){
                uii->statusbar->showMessage("Hier kann kein Schiff gesetzt werden.",3000);
                oneStepBack();
            }
            else{
                game.getPlayer().get_AirCarrier_ref(air).set_ship(sq1,sq2,sq3,sq4,sq5);
                squareList.clear();
                air -= 1;
                uii->airCarrierButton->setText("Flugzeugtraeger " + QString::number(air) + "x");
            }
            break;
    }
    //23.06 BEGIN
    if(sub <= 0){
        uii->submarineButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        sub = -1;
    }
    if(dest <= 0){
        uii->destroyerButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        dest = -1;
    }
    if(batt <= 0){
        uii->battleButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        batt = -1;
    }
    if(air <= 0){
        uii->airCarrierButton->setEnabled(false);
        disconnect(this, SLOT(selectAirCarrier()));
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        air = -1;
    }
    //23.06 END
    itemList.clear();
}

/**
 * @brief SetWindow::getEnemyName
 * @param n
 * Slot to get the name of the player from the startWindow
 */
void SetWindow::setPlayerName(QString n)
{
    name = n;
    std::string hmmm = name.toStdString();
    game.change_player_name(hmmm);
    setWindowTitle("Ship Happens");
}

/**
 * @brief SetWindow::changeDirection
 * change the direction how the ships are displayed and the string of the directionButton
 */
void SetWindow::changeDirection()
{
    if(uii->directionButton->text() == "Horizontal"){
        uii->directionButton->setText("Vertikal");
        horizontal = false;
    }
    else{
        uii->directionButton->setText("Horizontal");
        horizontal = true;
    }
    switch(zaehler){
        case 2: if(sub>0) selectSubmarine();
        break;
        case 3: if(dest>0) selectDestroyer();
        break;
        case 4: if(batt>0) selectBattleship();
        break;
        case 5: if(air>0) selectAirCarrier();
        break;
    }
}

/**
 * @brief SetWindow::selectSubmarine
 * set the shipTable with two items for draging it to the fieldTable
 */
void SetWindow::selectSubmarine()
{
    zaehler = 2;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,1,itemR);
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);
        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(1,0,itemR);
    }
    uii->shipTable->selectAll();
}

/**
 * @brief SetWindow::selectDestroyer
 * Set the shipTable with three items for draging it to the fieldTable
 */
void SetWindow::selectDestroyer()
{
    zaehler = 3;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);
        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,2,itemR);
        uii->shipTable->selectAll();
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);
        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,2,itemR);
        uii->shipTable->selectAll();
    }
}

/**
 * @brief SetWindow::selectBattleship
 * Set the shipTable with four items for draging it to the fieldTable
 */
void SetWindow::selectBattleship()
{
    zaehler = 4;
    int fieldSize = sqSize;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,fieldSize);
        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,fieldSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM2 = new QTableWidgetItem();
        itemM2->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);
        uii->shipTable->selectAll();
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,fieldSize);
        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,fieldSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM2 = new QTableWidgetItem();
        itemM2->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);
        uii->shipTable->selectAll();
    }
}

/**
 * @brief SetWindow::selectAirCarrier
 * Set the shipTable with five items for draging it to the fieldTable
 */
void SetWindow::selectAirCarrier()
{
    zaehler = 5;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);
        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM2 = new QTableWidgetItem();
        itemM2->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM3 = new QTableWidgetItem();
        itemM3->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemM3);
        uii->shipTable->setItem(0,4,itemR);
        uii->shipTable->selectAll();
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);
        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem();
        itemL->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM = new QTableWidgetItem();
        itemM->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM2 = new QTableWidgetItem();
        itemM2->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemM3 = new QTableWidgetItem();
        itemM3->setBackgroundColor(Qt::black);
        QTableWidgetItem *itemR = new QTableWidgetItem();
        itemR->setBackgroundColor(Qt::black);
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemM3);
        uii->shipTable->setItem(0,4,itemR);
        uii->shipTable->selectAll();
    }
}

/**
 * @brief SetWindow::tableManagement
 * set the size, headernames of the rows and columns and fills the fieldTable with items with blue background
 */
void SetWindow::tableManagement()
{
    uii->fieldTable->setAcceptDrops(true);
    uii->fieldTable->setRowCount(width);
    uii->fieldTable->setColumnCount(height);
    // set the headernames of the rows and columns
    QStringList hlist, vlist;
    vlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"
        <<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20";
    hlist<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
        <<"O"<<"P"<<"Q"<<"R"<<"S"<<"T";
    uii->fieldTable->setHorizontalHeaderLabels(hlist.mid(0,width));
    uii->fieldTable->setVerticalHeaderLabels(vlist.mid(0,height));

    // manage the size of the squares of the table
    for(int i=0;i<height;i++)
        uii->fieldTable->setColumnWidth(i,sqSize);
    for(int i=0;i<width;i++)
        uii->fieldTable->setRowHeight(i,sqSize);

    // fills the fields of the table with squareg items
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackgroundColor(Qt::blue);
            uii->fieldTable->setItem(i,j,item);
        }
    }
    uii->fieldTable->setDragDropMode(QAbstractItemView::DropOnly);
    uii->fieldTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/**
 * @brief SetWindow::getGameRef
 * @return  Game
 * returns the set game reference
 */
Game &SetWindow::getGameRef()
{
    return game;
}

/**
 * @brief SetWindow::setHost
 * @param h
 * get the information from the StartWindow if this player is host or not
 */
void SetWindow::setHost(MyServer *serve)
{
    server = serve;
    host = true;
    uii->startButton->setText("Start");
    connect(server, SIGNAL(sendReady()), this, SLOT(getBoard()));
}

void SetWindow::setClient(MySocket *socke)
{
    socket = socke;
    host = false;
    uii->startButton->setText("Bereit");
}
