#ifndef GLHELPER_H
#define GLHELPER_H

#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QFont>

#include <list>

class QPainter;
class QPaintEvent;

class GlHelper
{
public:
    GlHelper();

    void paint(QPainter* painter, QPaintEvent* event, std::list<QRect> squares);

private:

    typedef std::list<QRect>::iterator SquareIt;
};

#endif // GLHELPER_H
