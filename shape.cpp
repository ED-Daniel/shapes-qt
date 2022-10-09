#include "shape.h"

Shape::Shape(qreal x, qreal y, qreal width, qreal height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Shape::setStart(qreal startOffset)
{
    outline.moveTo(x + startOffset, y);
}

void Shape::addLine(Places place, qreal endOffset)
{
    switch (place) {
    case Places::upperLeft:
        outline.lineTo(x + width / 2 - endOffset, y);
        break;
    case Places::upper:
        outline.lineTo(x + width - endOffset, y);
        break;
    case Places::upperRight:
        outline.lineTo(x + width, y + height - endOffset);
        break;
    case Places::downRight:
        outline.lineTo(x + width / 2 + endOffset, y + height);
        break;
    case Places::down:
        outline.lineTo(x + endOffset, y + height);
        break;
    case Places::downLeft:
        outline.lineTo(x, y + endOffset);
        break;
    default:
        break;
    }
}

void Shape::addOuterRound(qreal radius, Places place)
{
    switch (place) {
    case Places::upperLeft:
        addLine(Places::downLeft, radius);
        outline.arcTo(x, y, radius * 2, radius * 2, 180, -90);
        break;
    case Places::upperRight:
        addLine(Places::upper, radius);
        outline.arcTo(x + width - radius * 2, y, radius * 2, radius * 2, 90, -90);
        break;
    case Places::downLeft:
        addLine(Places::down, radius);
        outline.arcTo(x, y + height - radius * 2, radius * 2, radius * 2, -90, -90);
        break;
    case Places::downRight:
        addLine(Places::upperRight, radius);
        outline.arcTo(x + width - radius * 2, y + height - radius * 2, radius * 2, radius * 2, 0, -90);
        break;
    default:
        break;
    }
}

void Shape::addInnerRound(qreal radius, Places place)
{
    switch (place) {
    case Places::upperLeft:
        addLine(Places::downLeft, radius);
        outline.arcTo(x - radius, y - radius, radius * 2, radius * 2, 270, 90);
        break;
    case Places::upperRight:
        addLine(Places::upper, radius);
        outline.arcTo(x + width - radius, y - radius, radius * 2, radius * 2, 180, 90);
        break;
    case Places::downLeft:
        addLine(Places::down, radius);
        outline.arcTo(x - radius, y + height - radius, radius * 2, radius * 2, 0, 90);
        break;
    case Places::downRight:
        addLine(Places::upperRight, radius);
        outline.arcTo(x + width - radius, y + height - radius, radius * 2, radius * 2, 90, 90);
        break;
    default:
        break;
    }
}

void Shape::addRoundPit(qreal radius, Places place)
{
    switch (place) {
    case Places::upper:
        addLine(Places::upperLeft, radius);
        outline.arcTo(x + width / 2 - radius, y - radius, radius * 2, radius * 2, 180, 180);
        break;
    case Places::down:
        addLine(Places::downRight, radius);
        outline.arcTo(x + width / 2 - radius, y + height - radius, radius * 2, radius * 2, 0, 180);
        break;
    default:
        break;
    }
}

void Shape::addStair(qreal a, Places place)
{
    switch (place) {
    case Places::upperLeft:
        addLine(Places::downLeft, a);
        outline.lineTo(x + a, y + a);
        outline.lineTo(x + a, y);
        break;
    case Places::upperRight:
        addLine(Places::upper, a);
        outline.lineTo(x + width - a, y + a);
        outline.lineTo(x + width, y + a);
        break;
    case Places::downLeft:
        addLine(Places::down, a);
        outline.lineTo(x + a, y + height - a);
        outline.lineTo(x, y + height - a);
        break;
    case Places::downRight:
        addLine(Places::upperRight, a);
        outline.lineTo(x + width - a, y + height - a);
        outline.lineTo(x + width - a, y + height);
        break;
    default:
        break;
    }
}

void Shape::addSlope(qreal a, Places place)
{
    switch (place) {
    case Places::upperLeft:
        addLine(Places::downLeft, a);
        outline.lineTo(x + a, y);
        break;
    case Places::upperRight:
        addLine(Places::upper, a);
        outline.lineTo(x + width, y + a);
        break;
    case Places::downLeft:
        addLine(Places::down, a);
        outline.lineTo(x, y + height - a);
        break;
    case Places::downRight:
        addLine(Places::upperRight, a);
        outline.lineTo(x + width - a, y + height);
        break;
    default:
        break;
    }
}

void Shape::addPit(qreal a, Places place)
{
    switch (place) {
    case Places::upper:
        addLine(Places::upperLeft, a);
        outline.lineTo(x + width / 2 - a, y + a);
        outline.lineTo(x + width / 2 + a, y + a);
        outline.lineTo(x + width / 2 + a, y);
        break;
    case Places::down:
        addLine(Places::downRight, a);
        outline.lineTo(x + width / 2 + a, y + height - a);
        outline.lineTo(x + width / 2 - a, y + height - a);
        outline.lineTo(x + width / 2 - a, y + height);
        break;
    default:
        break;
    }
}

void Shape::setPosition(qreal x, qreal y)
{
    previousX = this->x;
    previousY = this->y;

    this->x = x;
    this->y = y;
}

void Shape::restorePosition()
{
    outline.translate(previousX - this->x, previousY - this->y);
    this->x = previousX;
    this->y = previousY;
}

qreal Shape::getX()
{
    return x;
}

qreal Shape::getY()
{
    return y;
}


