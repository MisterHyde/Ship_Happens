#include "enddialog.h"
#include "ui_enddialog.h"

/**
 * @brief EndDialog::EndDialog
 * @param name
 * @param win
 * @param parent
 * \nConstructor
 */
EndDialog::EndDialog(QString name, bool win, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    ui->setupUi(this);
    if(win){
        ui->picture->setPixmap(QPixmap("../Ship_Happens/images/funny.png"));
        ui->label->setText("Herzlichen Glueckwunsch " + name + ", du hast das Spiel Gewonnen");
    }
    else{
        ui->picture->setPixmap(QPixmap("../Ship_Happens/images/sad.png"));
        ui->label->setText("Tut mir leid " + name + ", aber du hattest heute scheinbar kein Glueck");
    }

    setWindowTitle("Lust auf eine Revanche?");
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), parent, SLOT(revenge(QAbstractButton*)));
//    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(noRevenge()));
//    connect(ui->pushButton_2, SIGNAL(clicked()), parent, SLOT(revenge()));
}

/**
 * @brief EndDialog::~EndDialog
 * \nDestructor
 */
EndDialog::~EndDialog()
{
    delete ui;
}
