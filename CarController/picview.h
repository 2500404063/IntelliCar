#ifndef PICVIEW_H
#define PICVIEW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>

class PicView : public QLabel
{
    Q_OBJECT
public:
    PicView(QWidget *&parent);
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
Q_SIGNALS:
    void keyPress(QKeyEvent *e);
    void keyRelease(QKeyEvent *e);
};

#endif // PICVIEW_H
