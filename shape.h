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
    void addStair(qreal x, Places place);
    void addSlope(qreal x, Places place);
    void addPit(qreal x, Places place);

private:
    qreal x;
    qreal y;

    qreal width;
    qreal height;
};

#endif // SHAPE_H
