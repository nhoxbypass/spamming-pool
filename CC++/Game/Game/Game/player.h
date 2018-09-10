#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT

public:
    Player();
    Player(QString name,int lev);
    ~Player();

    void setName(QString name);
    void setRank(int lev);
    QString getName();
    int getRank();

public slots:

    void updateRank(int lev);

private:
    QString name;
    int rank;
};

#endif // PLAYER_H
