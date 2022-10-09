#include "scenecontroller.h"

SceneController::SceneController()
{

}

void SceneController::createFirstShape(qreal x, qreal y)
{
    Shape shape = Shape(x, y, width, height);
    shape.setStart(verticesExcavations);

    shape.addRoundPit(pitRadius, Places::upper);
    shape.addStair(verticesExcavations, Places::upperRight);
    shape.addStair(verticesExcavations, Places::downRight);
    shape.addLine(Places::downRight);
    shape.addOuterRound(verticesRadius, Places::downLeft);
    shape.addStair(verticesExcavations, Places::upperLeft);

    shapes.push_back(shape);
}

void SceneController::rotateFigure(size_t i, qreal angle)
{
    if (i >= shapes.size()) {
        return;
    }

    Shape chosenShape = shapes[i];

    QTransform transform;
    transform.translate(chosenShape.getX() + width / 2, chosenShape.getY() + height / 2);
    transform.rotate(angle);
    transform.translate(-chosenShape.getX() - width / 2, -chosenShape.getY() - height / 2);

    shapes[i].outline = transform.map(chosenShape.outline);
}

void SceneController::selectFigure(size_t i)
{
    if (i >= shapes.size()) {
        return;
    }

    selected = &shapes[i];
}

void SceneController::selectFigure(Shape *figure)
{
    selected = figure;
}

void SceneController::deselectFigure()
{
    selected = nullptr;
}

void SceneController::deleteFigure(Shape *figure)
{
    for (size_t i = 0; i < shapes.size(); i++) {
        if (figure == &shapes[i]) {
            if (figure == selected) {
                selected = nullptr;
            }
            shapes.erase(shapes.begin() + i);
        }
    }
}

void SceneController::deleteSelectedFigure()
{
    deleteFigure(selected);
    deselectFigure();
}

void SceneController::editSelectedFigure()
{

}

void SceneController::renderFigures(QPainter & painter)
{
    for (Shape & shape : shapes) {
        if (&shape == selected) {
            painter.strokePath(shape.outline, QPen(Qt::blue, 3));
            continue;
        }
        painter.strokePath(shape.outline, QPen(Qt::black, 1));
    }
}

void SceneController::moveSelectedToCoordinates(qreal x, qreal y)
{
    if (selected == nullptr) {
        return;
    }

    selected->outline.translate(x - selected->getX(), y - selected->getY());
    selected->setPosition(x, y);
}
