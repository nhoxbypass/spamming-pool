#ifndef TABLEINTERFACE_H
#define TABLEINTERFACE_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QTimer>
#include "path.h"
#include "player.h"
#include "keypress.h"

namespace Ui {
class TableInterface;
}

class TableInterface : public QDialog
{
    Q_OBJECT

public:
    explicit TableInterface(QWidget *parent = 0);
    explicit TableInterface(int row,int col,QString name,int level,QWidget *parent = 0);
    ~TableInterface();

    void setNumRow(int n);
    void setNumCol(int n);

signals:
    void timeToPlay();
    void end_game(bool win_game);
    void win(int lev);
    void lose(int lev);

public slots:
    void showPath();
    void resetColor();
    void play();
    void move(int key);
    void result(bool win_game);
    void lose_inform(int lev);
    void win_inform(int lev);

protected:


private:
    int index;
    bool check_move();

    Ui::TableInterface *ui;
    QTimer* timer;
    KeyPressReceiver* keypress;
    int num_row;
    int num_col;
    int rank;
    Path* randomPath;
    QTableWidgetItem* item_player;
    Player* player;
    QPoint* point_player;
};

#endif // TABLEINTERFACE_H
