#include "widget.h"

#include "glhelper.h"
#include <QtGui>
#include <Qt/qgl.h>

#include <stdlib.h>

#include <iostream>
using namespace std;
GlWidget::GlWidget(GlHelper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), mHelper(helper), mElapsed(0) {
    setAutoFillBackground(false);

    connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));

    QTimer* timer = new QTimer();
    timer->setInterval(1000);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start();
}

void GlWidget::tick() {
    int size = 20;
    for(SquareIt it = mSquares.begin(); it != mSquares.end(); ++it) {
        int dir = rand()%9;
        int x = it->x();
        int y = it->y();
        switch(dir) {
        case 0:
            it->moveTo(x-size, y-size);
            break;
        case 1:
            it->moveTo(x, y-size);
            break;
        case 2:
            it->moveTo(x+size, y-size);
            break;
        case 3:
            it->moveTo(x-size, y);
            break;
        case 4:
            it->moveTo(x+size, y);
            break;
        case 5:
            it->moveTo(x-size, y+size);
            break;
        case 6:
            it->moveTo(x, y+size);
            break;
        case 7:
            it->moveTo(x+size, y+size);
            break;
        }
        if(it->x() < 0) {
            it->moveTo(this->size().width(), it->y());
        }
        else if(it->x() > this->size().width()) {
            it->moveTo(0, it->y());
        }
        if(it->y() < 0) {
            it->moveTo(it->x(), this->size().height());
        }
        else if(it->y() > this->size().height()) {
            it->moveTo(it->x(), 0);
        }
    }
    repaint();
}

void GlWidget::mousePressEvent(QMouseEvent* event) {
    QRect* r = new QRect(event->pos().x(), event->pos().y(), 20, 20);
    mSquares.push_back(*r);
}

void GlWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    mHelper->paint(&painter, event, mSquares);
    painter.end();
}
