#include "shapesmain.h"
#include "ui_shapesmain.h"
#include "shape.h"

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
    qreal rectWidth = 200;
    qreal rectHeight = 100;
    qreal radius = 40;

    qreal startX = 100;
    qreal startY = 100;

    qreal angle = 0;

//    QPainterPath outline;
//    outline.moveTo(startX, startY);

//    outline.lineTo(startX + rectWidth, startY);
//    outline.lineTo(startX + rectWidth, startY + rectHeight - radius);
//    outline.arcTo(startX + rectWidth - radius, startY + rectHeight - radius, radius, radius, 0, -90);
//    outline.lineTo(startX, startY + rectHeight);
//    outline.lineTo(startX, startY);

    Shape shape = Shape(startX, startY, rectWidth, rectHeight);
    shape.setStart(0);

    shape.addLine(Places::upperLeft);
    shape.addLine(Places::upper);
    shape.addLine(Places::upperRight, radius);

    shape.addOuterRound(radius, Places::downRight);

    shape.addLine(Places::downRight);
    shape.addLine(Places::down);
    shape.addLine(Places::downLeft);

    QPainter painter(this);
    painter.translate(startX + rectWidth / 2, startY + rectHeight / 2);
    painter.rotate(angle);
    painter.translate(-(startX + rectWidth / 2), -(startY + rectHeight / 2));
    painter.strokePath(shape.outline, QPen(Qt::black, 1));
}
