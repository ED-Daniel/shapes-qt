#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include <QtCore>

enum Places {
    upperLeft,
    upper,
    upperRight,
    downLeft,
    down,
    downRight
};

class Shape
{
public:
    Shape(qreal x, qreal y, qreal width, qreal height);

    QPainterPath outline;

    void setStart(qreal startOffset);

    void addLine(Places place, qreal endOffset=0);

    void addOuterRound(qreal radius, Places place);
    void addInnerRound(qreal radius, Places place);
    void addRoundPit(qreal radius, Places place);
    void addStair(qreal a, Places place);
    void addSlope(qreal a, Places place);
    void addPit(qreal a, Places place);

    void setPosition(qreal x, qreal y);
    void restorePosition();

    qreal getX();
    qreal getY();

private:
    qreal x;
    qreal y;

    qreal width;
    qreal height;

    qreal previousX;
    qreal previousY;
};

#endif // SHAPE_H
