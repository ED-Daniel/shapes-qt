#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "shape.h"
#include <iostream>
#include <stdexcept>
#include <QtWidgets>
#include <random>

class SceneController
{
private:
    SceneController();
    SceneController( const SceneController&);
    SceneController& operator=( SceneController& );

    Shape * selected = nullptr;

public:
    static SceneController& getInstance() {
        static SceneController  instance;
        return instance;
    }

    qreal width = 300;
    qreal height = 200;
    qreal verticesRadius = 15;
    qreal verticesExcavations = 20;
    qreal pitDeepth = 20;
    qreal pitRadius = 20;

    bool useRandom = true;

    std::vector<Shape> shapes = std::vector<Shape>();

    void createFirstShape(qreal x, qreal y, ShapesTypes shapeType);

    void rotateFigure(size_t i, qreal angle);
    void rotateSelected(qreal angle);
    void set0Rotation(size_t i);
    void setSelected0Rotation();

    void scaleShape(size_t i, qreal value);

    void selectFigure(size_t i);
    void selectFigure(Shape * figure);

    void deselectFigure();

    void deleteFigure(Shape * figure);
    void deleteFigure(int index);
    void deleteSelectedFigure();

    void editSelectedFigure();

    void renderFigures(QPainter & painter);

    void moveSelectedToCoordinates(qreal x, qreal y, qreal windowWidth, qreal windowHeight);
    void moveToCoordinates(size_t i, qreal x, qreal y);

    bool hasSelectedFigure();

    Shape * getSlectedShape();

    qreal generateRandomRange(qreal min, qreal max);
};

#endif // SCENECONTROLLER_H
