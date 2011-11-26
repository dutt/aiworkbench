#include "glhelper.h"

#include <QtGui>

GlHelper::GlHelper() {
    mBackground = QBrush(QColor(0, 180, 0));
    mSquare = QBrush(QColor(255,0,0));
    mTextPen = QPen(Qt::black);
    mTextFont.setPixelSize(20);
}

void GlHelper::paint(QPainter *painter, QPaintEvent *event, std::list<QRect> squares) {
    painter->fillRect(event->rect(), mBackground);
    for(SquareIt it = squares.begin(); it != squares.end(); ++it) {
        painter->fillRect(*it, mSquare);
    }
}
