#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include <QtCore>
#include "customtypes.h"

class Shape
{
public:
    Shape(qreal x, qreal y, qreal width, qreal height, ShapesTypes shapeType = ShapesTypes::first);

    QPainterPath outline;
    qreal rotationAngle = 0;

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

    void scale(qreal value);
    void rotate(qreal angle);
    void resetRotation();

    qreal getX();
    qreal getY();

    qreal getHeight();
    qreal getWidth();

    qreal getPerimeter();
    qreal getArea();
    qreal getScaleValue();

    ShapesTypes getShapeType();

private:
    qreal x;
    qreal y;

    qreal width;
    qreal height;

    qreal previousX;
    qreal previousY;

    qreal area;
    qreal perimeter;

    qreal scaleValue = 1;

    ShapesTypes shapeType;
};

#endif // SHAPE_H
