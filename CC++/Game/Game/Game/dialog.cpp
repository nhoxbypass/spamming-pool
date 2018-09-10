#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Game - Nguyen Chiem Minh Vu");

    ui->playButton->setEnabled(false);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(":/images/V.png"));

    ui->playButton->setIcon(QIcon(":/images/play.png"));
    ui->instructionButton->setIcon(QIcon(":/images/instruction.png"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_instructionButton_clicked()
{
    QMessageBox::information(this,"Instruction","After a few seconds to view the random path, you need to move on exactly that path. Press Key_Up to jump up, Key_Left to jump left.",QMessageBox::Ok);
}

void Dialog::on_playButton_clicked()
{
    int row = 0,col = 0;

    switch (ui->level->currentIndex())
    {
    case 0:
        row = col = 5;
            break;
    case 1:
        row = col = 7;
            break;
    case 2:
        row = col = 10;
            break;
    case 3:
        row = col = 15;
            break;
    }

    TableInterface* table = new TableInterface(row,col,ui->name->text(),ui->level->currentIndex());
    table->exec();
}

void Dialog::on_name_textChanged(const QString &arg1)
{
    if(ui->name->text() == "")
        ui->playButton->setEnabled(false);
    else
        ui->playButton->setEnabled(true);
}
