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

void ShapesMain::paintEvent(QPaintEvent *)
{
    SceneController::getInstance().createFirstShape();

    qreal rectWidth = SceneController::getInstance().rectWidth;
    qreal rectHeight = SceneController::getInstance().rectHeight;

    qreal startX = SceneController::getInstance().startX;
    qreal startY = SceneController::getInstance().startY;

    qreal angle = 10 / 3;

    QPainter painter(this);
    QTransform transform;

    transform.translate(startX + rectWidth / 2, startY + rectHeight / 2);
    transform.rotate(angle);
    transform.translate(-(startX + rectWidth / 2), -(startY + rectHeight / 2));

    SceneController::getInstance().shapes[0].outline = transform.map(SceneController::getInstance().shapes[0].outline);

    painter.strokePath(SceneController::getInstance().shapes[0].outline, QPen(Qt::black, 1));
}

void ShapesMain::mousePressEvent(QMouseEvent *e)
{
    QPainterPath mouseRect;
    mouseRect.addRect(e->pos().x(), e->pos().y(), 1, 1);

    if (SceneController::getInstance().shapes[0].outline.intersects(mouseRect)) {
        ui->statusbar->showMessage("Inside");
    }
    else {
        ui->statusbar->showMessage("Outside");
    }
}
