#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent) {

}

ClickableLabel::~ClickableLabel()   {

}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {

    emit clicked();
}
