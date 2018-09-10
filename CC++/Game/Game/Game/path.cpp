#include "path.h"

Path::Path()
{

}

Path::Path(int num_row, int num_col)
{
    createPath(num_row,num_col);
}

Path::~Path()
{

}

void Path::createPath(int num_row, int num_col)
{
    QPoint begin(0,0);
    QPoint end(num_row-1,num_col-1);

    path.push_back(begin);

    srand(time(NULL));
    while(begin != end)
    {
        begin = nextPoint(begin,num_row,num_col);
        path.push_back(begin);
    }
}

QPoint Path::nextPoint(QPoint p,int row,int col)
{
    QPoint temp = p;
    if(temp.x() == row-1)
        temp.ry()++;
    else if(temp.y() == col-1)
        temp.rx()++;
    else
    {
        int ran = rand()%2;
        switch (ran) {
        case 0:
            temp.rx()++;
            break;
        case 1:
            temp.ry()++;
            break;
        }
    }
    return temp;
}

QPoint Path::at(int i)
{
    return path[i];
}
