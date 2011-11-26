#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Qt/qgl.h"

class GlHelper;

class GlWidget : public QGLWidget {
    Q_OBJECT

public:
    GlWidget(GlHelper* helper, QWidget* parent);

public slots:
    void tick();

protected:
    void mousePressEvent(QMouseEvent*  event);
    void paintEvent(QPaintEvent* event);

private:
    std::list<QRect> mSquares;
    typedef std::list<QRect>::iterator SquareIt;
    GlHelper* mHelper;
    int mElapsed;
};

#endif // WIDGET_H
