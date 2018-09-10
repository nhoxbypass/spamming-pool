#include "player.h"

Player::Player()
{
    rank = -1;
}

Player::Player(QString name,int lev)
{
    this->name = name;
    rank = lev;
}

Player::~Player()
{

}

void Player::setName(QString name)
{
    this->name = name;
}

void Player::setRank(int lev)
{
    rank = lev;
}

void Player::updateRank(int lev)
{
    if(lev > rank)
        rank = lev;
}

QString Player::getName()
{
    return name;
}

int Player::getRank()
{
    return rank;
}
