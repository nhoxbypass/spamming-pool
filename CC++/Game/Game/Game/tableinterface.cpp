#include "tableinterface.h"
#include "ui_tableinterface.h"
#include <QKeyEvent>

TableInterface::TableInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableInterface)
{
    ui->setupUi(this);
}

TableInterface::TableInterface(int row,int col,QString name,int level,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableInterface)
{
    ui->setupUi(this);
    item_player = new QTableWidgetItem;
    keypress = new KeyPressReceiver;
    connect(this,SIGNAL(end_game(bool)),this,SLOT(result(bool)));
    ui->tableWidget->installEventFilter(keypress);

    player = new Player();
    player->setName(name);
    timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(resetColor()));
    connect(this,SIGNAL(timeToPlay()),this,SLOT(play()));

    setNumRow(row);
    setNumCol(col);
    ui->tableWidget->move(0,0);

    ui->tableWidget->setRowCount(num_row);
    ui->tableWidget->setColumnCount(num_col);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setWindowTitle("Graph");
    this->setMinimumSize(ui->tableWidget->width(),ui->tableWidget->height());
    this->resize(this->minimumSize());
    this->setFixedSize(this->size());

    randomPath = new Path(num_row,num_col);
    showPath();

    rank = level;
    switch (level) {
    case 0:
    case 1:
        timer->start(2000);
        break;
    case 2:
        timer->start(3000);
        break;
    case 3:
        timer->start(5000);
        break;
    default:
        break;
    }
}

TableInterface::~TableInterface()
{
    delete ui;
}

void TableInterface::setNumCol(int n)
{
    num_col = n;
}

void TableInterface::setNumRow(int n)
{
    num_row = n;
}

void TableInterface::showPath()
{
    item_player->setBackgroundColor(Qt::green);

    for(int i = 0; i < num_row+num_col-1; i++)
    {
        ui->tableWidget->setItem(randomPath->at(i).x(),randomPath->at(i).y(),item_player->clone());
    }
}

void TableInterface::resetColor()
{
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setBackgroundColor(Qt::white);

    for(int i = 0; i < num_row+num_col-1; i++)
    {
        ui->tableWidget->setItem(randomPath->at(i).x(),randomPath->at(i).y(),item->clone());
    }
    timer->stop();
    emit timeToPlay();
}

void TableInterface::play()
{
    connect(keypress,SIGNAL(getKey(int)),this,SLOT(move(int)));
    index = num_row + num_col - 2;
    point_player = new QPoint(randomPath->at(index).x(),randomPath->at(index).y());
    item_player = new QTableWidgetItem;

    item_player->setBackgroundColor(Qt::green);

    ui->tableWidget->setItem(randomPath->at(index).x(),randomPath->at(index).y(),item_player->clone());

    connect(this,SIGNAL(win(int)),player,SLOT(updateRank(int)));
    connect(this,SIGNAL(win(int)),this,SLOT(win_inform(int)));
    connect(this,SIGNAL(lose(int)),this,SLOT(lose_inform(int)));
}

void TableInterface::move(int key)
{
    switch (key) {
    case Qt::Key_Up:
            index--;
            point_player->rx()--;
            break;

    case Qt::Key_Left:
            index--;
            point_player->ry()--;
            break;
    default:
        break;
    }

    ui->tableWidget->setItem(point_player->x(),point_player->y(),item_player->clone());

    if(point_player->x() == 0 && point_player->y() == 0)
    {
        emit end_game(true);
    }
    else if(check_move() == false)
    {
        showPath();

        item_player->setBackgroundColor(Qt::red);
        ui->tableWidget->setItem(point_player->x(),point_player->y(),item_player->clone());
        emit end_game(false);
    }
}

bool TableInterface::check_move()
{
    if(point_player->x() == randomPath->at(index).x() && point_player->y() == randomPath->at(index).y())
        return true;
    return false;
}

void TableInterface::win_inform(int lev)
{
    int choice = 0;
    switch (lev) {
    case 0:
        choice = QMessageBox::information(this,"Congratulation!","Not bad!",QMessageBox::Ok);
        break;
    case 1:
        choice = QMessageBox::information(this,"Congratulation!","Good job!",QMessageBox::Ok);
        break;
    case 2:
        choice = QMessageBox::information(this,"Congratulation!","Nice one!",QMessageBox::Ok);
        break;
    case 3:
        choice = QMessageBox::information(this,"Congratulation!","WTF? You're really GOD!",QMessageBox::Ok);
        break;
    default:
        this->close();
        break;
    }
    if(choice == QMessageBox::Ok)
        this->close();
}

void TableInterface::lose_inform(int lev)
{
    int choice = 0;
    switch (lev) {
    case 0:
        choice = QMessageBox::information(this,"Inform","You're very stupid!",QMessageBox::Ok);
        break;
    case 1:
        choice = QMessageBox::information(this,"Inform","Don't worry, let's try again!",QMessageBox::Ok);
        break;
    case 2:
        choice = QMessageBox::information(this,"Inform","Come on! You can do it better!",QMessageBox::Ok);
        break;
    case 3:
        choice = QMessageBox::information(this,"Inform","Maybe this level beyond your ability!",QMessageBox::Ok);
        break;
    default:
        this->close();
        break;
    }
    if(choice == QMessageBox::Ok)
        this->close();
}

void TableInterface::result(bool win_game)
{
    if(win_game)
    {
        emit win(rank);
    }
    else
    {
        emit lose(rank);
    }
}
