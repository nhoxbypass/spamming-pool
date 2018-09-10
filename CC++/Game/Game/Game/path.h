#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QPoint>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <QMessageBox>

class Path : public QObject
{
    Q_OBJECT

public:
    Path();
    Path(int num_row,int num_col);
    ~Path();
    void createPath(int num_row,int num_col);
    QPoint at(int i);

signals:

public slots:

private:
    std::vector<QPoint> path;
    QPoint nextPoint(QPoint p,int row,int col);
};

#endif // PATH_H
