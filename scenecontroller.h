#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "shape.h"

class SceneController
{
private:
    SceneController();
    SceneController( const SceneController&);
    SceneController& operator=( SceneController& );
public:
    static SceneController& getInstance() {
        static SceneController  instance;
        return instance;
    }

    qreal rectWidth = 200;
    qreal rectHeight = 100;

    qreal radius = 15;

    qreal a = 20;

    qreal startX = 100;
    qreal startY = 100;

    std::vector<Shape> shapes = std::vector<Shape>();

    void createFirstShape();
};

#endif // SCENECONTROLLER_H
