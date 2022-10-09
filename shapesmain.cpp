#include "shapesmain.h"
#include "ui_shapesmain.h"
#include "scenecontroller.h"

ShapesMain::ShapesMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShapesMain)
{
    ui->setupUi(this);
}

ShapesMain::~ShapesMain()
{
    delete ui;
}

void ShapesMain::paintEvent(QPaintEvent *) {
    if (SceneController::getInstance().shapes.empty()) {
        return;
    }

    QPainter painter(this);
    SceneController::getInstance().renderFigures(painter);
}

void ShapesMain::mousePressEvent(QMouseEvent *e)
{
    QPainterPath mouseRect;
    mouseRect.addRect(e->pos().x(), e->pos().y(), 1, 1);

    if (SceneController::getInstance().shapes.empty()) {
        SceneController::getInstance().createFirstShape(e->pos().x(), e->pos().y());
    }

    for (auto & shape : SceneController::getInstance().shapes) {
        if (shape.outline.intersects(mouseRect)) {
            ui->statusbar->showMessage("Inside");
            SceneController::getInstance().rotateFigure(0, 20);
            SceneController::getInstance().selectFigure(&shape);
        }
        else {
            ui->statusbar->showMessage("Outside");
        }
    }

    this->update();
}
