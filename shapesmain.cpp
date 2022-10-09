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

//    qreal radius = 40;

    qreal a = 20;

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
    shape.setStart(a);

    shape.addLine(Places::upperLeft);
    shape.addSlope(a, Places::upperRight);
    shape.addSlope(a, Places::downRight);
    shape.addLine(Places::downRight);
    shape.addSlope(a, Places::downLeft);
    shape.addSlope(a, Places::upperLeft);

    QPainter painter(this);
    painter.translate(startX + rectWidth / 2, startY + rectHeight / 2);
    painter.rotate(angle);
    painter.translate(-(startX + rectWidth / 2), -(startY + rectHeight / 2));
    painter.strokePath(shape.outline, QPen(Qt::black, 1));
}
