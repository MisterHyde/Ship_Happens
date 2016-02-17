#include "playwindow.h"
#include "ui_playwindow.h"

/**
 * @brief PlayWindow::PlayWindow
 * @param h
 * @param _game
 * @param parent
 * \nconstructor of the PlayWindow class
 *
 */
PlayWindow::PlayWindow(bool h, Game _game, NetworkStuff *pSocket, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    game(_game),
    playerBoard(game.getBoardRef()),
    enemyBoard(game.getEnemyBoardRef()),
    black(QColor(0,0,0)), red(QColor(255,0,0)),
    host(h),
    socket(pSocket)
{

    ui->setupUi(this);
    setWindowTitle("Ship Happens!");
    game.setStartActivity(host);

    ui->label_2->setText("Gewaesser von " + QString::fromStdString(game.get_enemy_name()));
    width = 10;
    height = 10;
    sqSize = 45;
    countSet();
    pen.setWidth(10);
    pen.setJoinStyle(Qt::RoundJoin);
    tableManagement();

    pen.setColor(Qt::black);
    templatBlack = QImage(45, 45, QImage::Format_RGB32);
    painter.begin(&templatBlack);
    painter.setPen(pen);
    for(int i=0;i<templatBlack.height();i++)
        for(int j=0;j<templatBlack.width();j++){
            painter.drawPoint(i,j);
        }
    painter.end();

    pen.setColor(Qt::blue);
    templatBlue = QImage(45, 45, QImage::Format_RGB32);
    painter.begin(&templatBlue);
    painter.setPen(pen);
    for(int i=0;i<templatBlue.height();i++)
        for(int j=0;j<templatBlue.width();j++){
            painter.drawPoint(i,j);
        }
    painter.end();

    connect(ui->enemyTable, SIGNAL(cellClicked(int,int)), this, SLOT(setBomb(int,int)));
    connect(socket, SIGNAL(shotReceived(int,int)), this, SLOT(getBombed(int,int)));
    //connect(ui->playerTable, SIGNAL(cellClicked(int,int)), this, SLOT(getBombed(int,int)));
    connect(this, SIGNAL(quitSignal()), parent, SLOT(revenge()));
    //game.printBoards();
}

/**
 * @brief PlayWindow::~PlayWindow
 * \nDeconstructor
 */
PlayWindow::~PlayWindow()
{
    delete ui;
}

/**
 * @brief PlayWindow::revenge
 * \nslot connected to the Ja-Button in the EndDialog window\n
 * close the EndDialog and the PlayWindow\n
 * emit the quitSignal() connected to the revenge() slot of StartWindow
 */
void PlayWindow::revenge()
{
    endD->close();
    this->close();
    emit quitSignal();
}

/**
 * @brief PlayWindow::setBomb
 * @param r <y-coordinate of the bombed square>
 * @param c <x-coordinate of the bombed square>
 * \nslot connected to the cellClicked signal of the enemys board\n
 * checks if the square is set or not and get the square hit\n
 * draws depending of set or not a red or black point on the square
 */
void PlayWindow::setBomb(int row, int column)
{
    if(!game.getPlayerState()){
        ui->statusbar->showMessage(tr("Der andere Spieler ist am Zug."), 4000);
        return;
    }

    if(enemyBoard.get_Square_ptr((size_t)column+1,(size_t)row+1)->get_square_hit()){
        ui->statusbar->showMessage(tr("Dieses Feld wurde schon bombardiert."), 4000);
        return;
    }

    int size = ui->enemyTable->iconSize().height();
    QImage temp = QImage(45, 45, QImage::Format_RGB32);
    // If the bombed square is occupied by an ship draw an red dot an count down the count down the square which are occupied
    if(enemyBoard.get_Square_ptr((size_t)(column+1),(size_t)(row+1))->get_square_set()){
        // Just drawing the bombed ship part
        pen.setColor(Qt::black);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        // Drawing the red dot
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage(tr("Yeaaaayyy das war der Gegner."), 4000);
        // Tell the logic that this square was bombed
        game.bomb_square((size_t)(column+1),(size_t)(row+1));
        countOther -=1;
        //if(!game.change_activity_status() && countOther == 0){
        if(game.checkEnemyLoose()){
            endD = new EndDialog(game.get_player_name(),true,this);
            endD->show();
        }
    }
    // If there was just water paint a black dot, bomb the square and change player activity
    else{
        pen.setColor(Qt::blue);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage(tr("Das war leider nur Wasser."), 4000);
        enemyBoard.get_Square_ptr((size_t)(column+1),(size_t)(row+1))->set_hit();
        game.change_activity_status();

    }

    ui->enemyTable->item(row,column)->setBackground(temp);
    socket->sendShot(row,column);
}

/**
 * @brief PlayWindow::getBombed
 * @param r <y-coordinate of the bombed square>
 * @param c <x-coordinate of the bombed square>
 * \nslot connected to the cellClicked signal of the players board\n
 * checks if the square is set or not and get the square hit\n
 * draws depending of set or not a red or black point on the square
 */
void PlayWindow::getBombed(int row, int column)
{
    int size = ui->enemyTable->iconSize().height();
    QImage temp = templatBlue;
    if(playerBoard.get_Square_ptr((size_t)(column+1),(size_t)(row+1))->get_square_set()){
        temp = templatBlack;
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.",4000);
        game.bomb_square((size_t)(column+1),(size_t)(row+1));
        countOwn -= 1;
        //if(game.change_activity_status() && countOwn == 0){
        if(game.checkPlayerLoose()){
            endD = new EndDialog(game.get_player_name(),false,this);
            endD->show();
        }
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.");
        playerBoard.get_Square_ptr((size_t)(column+1),(size_t)(row+1))->set_hit();
        game.change_activity_status();

    }
    ui->playerTable->item(row,column)->setBackground(QBrush(temp));
}

/**
 * @brief PlayWindow::tableManagement
 * \nset the size, headernames of the rows and columns and fills the enemyTable with items with blue backgrounds
 */
void PlayWindow::tableManagement()
{
    QTableWidget *table;
    for(int k=1;k<3;k++){
        if(k==1)
            table = ui->playerTable;
        else
            table = ui->enemyTable;

        table->setRowCount(width);
        table->setColumnCount(height);
        // set the headernames of the rows and columns
        QStringList hlist, vlist;
        vlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"
            <<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20";
        hlist<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
            <<"O"<<"P"<<"Q"<<"R"<<"S"<<"T";
        table->setHorizontalHeaderLabels(hlist.mid(0,width));
        table->setVerticalHeaderLabels(vlist.mid(0,height));

        // manage the size of the squares of the table
        for(int i=0;i<height;i++)
            table->setColumnWidth(i,sqSize);
        for(int i=0;i<width;i++)
            table->setRowHeight(i,sqSize);

        // fills the fields of the table with squareg items
//        QPixmap sea("/home/felix/Documents/prog/Field/images/sea.png");
//        QPixmap top("/home/felix/Documents/prog/Field/images/top.png");
//        QPixmap mid("/home/felix/Documents/prog/Field/images/middle.png");
//        QPixmap bot("/home/felix/Documents/prog/Field/images/bottom.png");
//        QPixmap left("/home/felix/Documents/prog/Field/images/left.png");
//        QPixmap vmid("/home/felix/Documents/prog/Field/images/vmiddle.png");
//        QPixmap right("/home/felix/Documents/prog/Field/images/right.png");
        for(size_t i=0;i<(size_t)width;i++){
            for(size_t j=0;j<(size_t)height;j++){
                if(k == 1){

                    if(playerBoard.get_Square_ptr(j+1, i+1)->get_square_set()){
                        //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon("images/white.png"),"",1000);
                        QTableWidgetItem *tempItem = new QTableWidgetItem();
                        tempItem->setBackgroundColor(Qt::black);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));

                    }
                    else{
                        //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
                        QTableWidgetItem *tempItem = new QTableWidgetItem();
                        tempItem->setBackgroundColor(Qt::blue);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                    }
                }
                else{
                    //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
                    QTableWidgetItem *tempItem = new QTableWidgetItem();
                    tempItem->setBackgroundColor(Qt::blue);
                    table->setItem(i,j,tempItem);
                    table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                }
            }
        }
        table->setDragDropMode(QAbstractItemView::DropOnly);
        table->setIconSize(QSize(sqSize+3,sqSize+3));
    }
}

void PlayWindow::countSet(){
    countOwn = 0;
    countOther = 0;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(game.getEnemyBoardRef().get_Square_ptr((size_t)i+1,(size_t)j+1)->get_square_set())
                countOther +=1;
            if(game.getBoardRef().get_Square_ptr((size_t)i+1,(size_t)j+1)->get_square_set())
                countOwn +=1;
        }
    }
}
