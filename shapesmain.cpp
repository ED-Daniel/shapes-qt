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

void ShapesMain::deleteFigure(bool)
{
    SceneController::getInstance().deleteSelectedFigure();
    this->update();
}

void ShapesMain::editFigure(bool)
{
    EditShapeDialog * editShapeDialog = new EditShapeDialog(this);
    editShapeDialog->show();
    this->update();
}

void ShapesMain::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    SceneController::getInstance().renderFigures(painter);
}

void ShapesMain::mousePressEvent(QMouseEvent *e)
{
    QPainterPath mouseRect;
    mouseRect.addRect(e->pos().x(), e->pos().y(), 1, 1);

    bool found = false;

    for (auto & shape : SceneController::getInstance().shapes) {
        if (shape.outline.intersects(mouseRect)) {

            if (e->button() == Qt::LeftButton) {
                SceneController::getInstance().selectFigure(&shape);
                setMouseTracking(true);
            }
            else if (e->button() == Qt::RightButton) {
                SceneController::getInstance().selectFigure(&shape);

                QMenu * contextMenu = new QMenu();
                QAction * deleteAction = new QAction("Delete", this);
                QAction * editAction = new QAction("Edit", this);

                connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteFigure(bool)));
                connect(editAction, SIGNAL(triggered(bool)), this, SLOT(editFigure(bool)));

                contextMenu->addAction(deleteAction);
                contextMenu->addAction(editAction);

                contextMenu->popup(this->mapToGlobal(e->pos()));
            }

            found = true;
            break;
        }
    }

    if (!found) {
        if (e->button() == Qt::LeftButton) {
            SceneController::getInstance().deselectFigure();
        }
        else if (e->button() == Qt::RightButton) {
            SceneController::getInstance().createFirstShape(e->pos().x(), e->pos().y());
        }
    }

    this->update();
}

void ShapesMain::mouseMoveEvent(QMouseEvent *e)
{
    if (!canMoveObjects) {
        return;
    }

    try {
        SceneController::getInstance().moveSelectedToCoordinates(e->pos().x(), e->pos().y(), this->size().width(), this->size().height());
    }
    catch (std::out_of_range & e) {
        ui->statusbar->showMessage("Out of bounds");
        setMouseTracking(false);
        canMoveObjects = false;
    }

    this->update();
}

void ShapesMain::mouseReleaseEvent(QMouseEvent *)
{
    setMouseTracking(false);
    canMoveObjects = true;
}
