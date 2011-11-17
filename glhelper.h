#ifndef GLHELPER_H
#define GLHELPER_H

#include <QBrush>
#include <QPen>
#include <QFont>

#include <list>

class QPainter;
class QPaintEvent;

class GlHelper
{
public:
    GlHelper();

    void paint(QPainter* painter, QPaintEvent* event, std::list<QRect> squares);

private:
    QBrush mBackground;
    QFont mTextFont;
    QPen mTextPen;
    QBrush mSquare;
    typedef std::list<QRect>::iterator SquareIt;
};

#endif // GLHELPER_H
