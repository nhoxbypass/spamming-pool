#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "tableinterface.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_instructionButton_clicked();

    void on_playButton_clicked();

    void on_name_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
