#include "picview.h"

PicView::PicView(QWidget *&parent)
{
    this->setParent(parent);
}

void PicView::keyPressEvent(QKeyEvent *e){
    if(!e->isAutoRepeat()){
        emit PicView::keyPress(e);
    }
}

void PicView::keyReleaseEvent(QKeyEvent *e){
    if(!e->isAutoRepeat()){
        emit PicView::keyRelease(e);
    }
}
