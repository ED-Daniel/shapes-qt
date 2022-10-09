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
        outline.lineTo(x + width / 2 - endOffset, y + height);
        break;
    case Places::down:
        outline.lineTo(x - endOffset, y + height);
        break;
    case Places::downLeft:
        outline.lineTo(x, y - endOffset);
        break;
    default:
        break;
    }
}

void Shape::addOuterRound(qreal radius, Places place)
{
    switch (place) {
    case Places::upperLeft:
        outline.arcTo(radius, radius, radius, radius, 180, -90);
        break;
    case Places::upperRight:
        outline.arcTo(x + width - radius, y + radius, radius, radius, 90, -90);
        break;
    case Places::downLeft:
        outline.arcTo(x + radius, y + height - radius, radius, radius, -90, -90);
        break;
    case Places::downRight:
        outline.arcTo(x + width - radius, y + height - radius, radius, radius, 0, -90);
        break;
    default:
        break;
    }
}


