#include "enddialog.h"
#include "ui_enddialog.h"

/**
 * @brief EndDialog::EndDialog
 * @param name
 * @param win
 * @param parent
 * \nConstructor
 */
EndDialog::EndDialog(std::string name, bool win, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    ui->setupUi(this);
    if(win){
        ui->picture->setPixmap(QPixmap("images/funny.png"));
        ui->label->setText("Herzlichen Glueckwunsch " + QString::fromStdString(name) + ", du hast das Spiel Gewonnen");
    }
    else{
        ui->picture->setPixmap(QPixmap("images/sad.png"));
        ui->label->setText("Tut mir leid " + QString::fromStdString(name) + ", aber du hattest heute scheinbar kein Glueck");
    }

    setWindowTitle("Lust auf eine Revanche?");
    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(ui->pushButton_2, SIGNAL(clicked()), parent, SLOT(revenge()));
}

/**
 * @brief EndDialog::~EndDialog
 * \nDestructor
 */
EndDialog::~EndDialog()
{
    delete ui;
}
