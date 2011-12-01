#include "widget.h"

#include "glhelper.h"
#include <QtGui>
#include <Qt/qgl.h>

#include <stdlib.h>

#include <iostream>
using namespace std;

Square::Square() :
    mX(0), mY(0), mWidth(0), mHeight(0), mColor(Qt::red)
{ }

Square::Square(int x, int y, int height, int width, Qt::GlobalColor color)
    : mX(x), mY(y), mHeight(height), mWidth(width), mColor(color)
{ }

bool Square::is_at(int x, int y) {
    return (x > mX && x < mX + mWidth) && (y > mY && y < mY + mHeight);
}

GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), mElapsed(0) {
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
        //int dir = rand()%9;
        int dir = 9;
        int x = it->x();
        int y = it->y();
        switch(dir) {
        case 0:
            it->move_to(x-size, y-size);
            break;
        case 1:
            it->move_to(x, y-size);
            break;
        case 2:
            it->move_to(x+size, y-size);
            break;
        case 3:
            it->move_to(x-size, y);
            break;
        case 4:
            it->move_to(x+size, y);
            break;
        case 5:
            it->move_to(x-size, y+size);
            break;
        case 6:
            it->move_to(x, y+size);
            break;
        case 7:
            it->move_to(x+size, y+size);
            break;
        }
        if(it->x() < 0) {
            it->move_to(this->size().width(), it->y());
        }
        else if(it->x() > this->size().width()) {
            it->move_to(0, it->y());
        }
        if(it->y() < 0) {
            it->move_to(it->x(), this->size().height());
        }
        else if(it->y() > this->size().height()) {
            it->move_to(it->x(), 0);
        }
    }
    repaint();
}

void GlWidget::mousePressEvent(QMouseEvent* event) {
    //QRect* r = new QRect(event->pos().x(), event->pos().y(), 20, 20);
    //mSquares.push_back(*r);
    for(SquareIt it = mSquares.begin(); it != mSquares.end(); ++it)    {
        if(it->is_at(event->pos().x(), event->pos().y()))        {

        }
    }
}

void GlWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), mBackground);
    for(SquareIt it = mSquares.begin(); it != mSquares.end(); ++it)    {
        painter.fillRect(it->rect(), mSquare);
    }
    painter.end();
}
