#include "scenecontroller.h"

SceneController::SceneController()
{

}

void SceneController::createFirstShape()
{
    Shape shape = Shape(startX, startY, rectWidth, rectHeight);
    shape.setStart(a);

    shape.addRoundPit(radius, Places::upper);
    shape.addStair(a, Places::upperRight);
    shape.addStair(a, Places::downRight);
    shape.addLine(Places::downRight);
    shape.addOuterRound(radius, Places::downLeft);
    shape.addStair(a, Places::upperLeft);

    shapes.push_back(shape);
}
