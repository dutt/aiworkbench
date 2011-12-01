#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Qt/qgl.h"

class GlHelper;

class Square
{
public:
    Square();
    Square(int x, int y, int heigth, int width, Qt::GlobalColor color);

    inline int x() { return mX; }
    inline int y() { return mY; }
    inline int width() { return mWidth; }
    inline int heigth() { return mHeight; }
    Qt::GlobalColor color() { return mColor; }

    inline void x(int x) { mX = x; }
    inline void y(int y) { mY = y; }
    inline void color(Qt::GlobalColor color) { mColor = color; }
    inline void width(int width) { mWidth = width; }
    inline void height(int height) { mHeight = height; }

    bool is_at(int x, int y);
    void move_to(int x, int y) { mX = x; mY = y; }
    QRect rect() { return QRect(mX, mY, mWidth, mHeight); }
private:
    Qt::GlobalColor mColor;
    int mX, mY;
    int mHeight, mWidth;
};

class GlWidget : public QGLWidget {
    Q_OBJECT

public:
    GlWidget(QWidget* parent);

public slots:
    void tick();

protected:
    void mousePressEvent(QMouseEvent*  event);
    void paintEvent(QPaintEvent* event);

private:
    QBrush mBackground;
    QFont mTextFont;
    QPen mTextPen;
    QBrush mSquare;

    std::list<Square> mSquares;
    typedef std::list<Square>::iterator SquareIt;
    GlHelper* mHelper;
    int mElapsed;
};

#endif // WIDGET_H
