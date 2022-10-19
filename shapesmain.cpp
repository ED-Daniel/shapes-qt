#include "shapesmain.h"
#include "ui_shapesmain.h"
#include "scenecontroller.h"

ShapesMain::ShapesMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShapesMain)
{
    ui->setupUi(this);
    ui->deleteSelectedButton->setEnabled(false);
}

ShapesMain::~ShapesMain()
{
    delete ui;
}

void ShapesMain::moveFigureToCursor()
{
    QPoint cursorPosition = this->mapFromGlobal(QCursor::pos());

    try {
        SceneController::getInstance().moveSelectedToCoordinates(cursorPosition.x(), cursorPosition.y(), this->size().width(), this->size().height());
    }
    catch (std::out_of_range & e) {
        ui->statusbar->showMessage("Out of bounds");
        setMouseTracking(false);
        canMoveObjects = false;
        updateFrames = false;
    }
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

void ShapesMain::moveFigure(bool)
{
    updateFrames = true;
}

void ShapesMain::rotateFigure(bool)
{
    RotateShapeDialog * rotateDialog = new RotateShapeDialog(this);
    rotateDialog->show();
    this->update();
}

void ShapesMain::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    SceneController::getInstance().renderFigures(painter);

    if (SceneController::getInstance().hasSelectedFigure()) {
        ui->deleteSelectedButton->setEnabled(true);
    }
    else {
        ui->deleteSelectedButton->setEnabled(false);
    }

    //ui->statusbar->showMessage("FRAME: " + QString::number(frameCounter));

    if (updateFrames) {
        frameCounter++;
        moveFigureToCursor();
        this->update();
    }
}

void ShapesMain::mousePressEvent(QMouseEvent *e)
{
    QPainterPath mouseRect;
    mouseRect.addRect(e->pos().x(), e->pos().y(), 1, 1);

    bool found = false;
    updateFrames = false;

    for (auto & shape : SceneController::getInstance().shapes) {
        if (shape.outline.intersects(mouseRect)) {

            if (e->button() == Qt::LeftButton) {
                SceneController::getInstance().selectFigure(&shape);
                ui->deleteSelectedButton->setEnabled(true);
                setMouseTracking(true);
            }
            else if (e->button() == Qt::RightButton) {
                SceneController::getInstance().selectFigure(&shape);
                ui->deleteSelectedButton->setEnabled(true);

                QMenu * contextMenu = new QMenu();
                QAction * deleteAction = new QAction("Delete", this);
                QAction * editAction = new QAction("Edit", this);
                QAction * moveAction = new QAction("Move", this);
                QAction * rotateAction = new QAction("Rotate", this);

                connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteFigure(bool)));
                connect(editAction, SIGNAL(triggered(bool)), this, SLOT(editFigure(bool)));
                connect(moveAction, SIGNAL(triggered(bool)), this, SLOT(moveFigure(bool)));
                connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(rotateFigure(bool)));

                contextMenu->addAction(deleteAction);
                contextMenu->addAction(editAction);
                contextMenu->addAction(moveAction);
                contextMenu->addAction(rotateAction);

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
            SceneController::getInstance().createFirstShape(e->pos().x(), e->pos().y(), selectedType);
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

void ShapesMain::on_deleteSelectedButton_clicked()
{
    SceneController::getInstance().deleteSelectedFigure();
    this->update();
}


void ShapesMain::on_firstShapeButton_toggled(bool checked)
{
    if (checked) {
        ui->secondShapeButton->setChecked(false);
        selectedType = ShapesTypes::first;
    }
    else {
        selectedType = ShapesTypes::nothing;
    }
}


void ShapesMain::on_secondShapeButton_toggled(bool checked)
{
    if (checked) {
        ui->firstShapeButton->setChecked(false);
        selectedType = ShapesTypes::second;
    }
    else {
        selectedType = ShapesTypes::nothing;
    }
}


void ShapesMain::on_actionDelete_All_triggered()
{
    SceneController::getInstance().shapes.clear();
    this->update();
}


void ShapesMain::on_actionDelete_Intersecting_triggered()
{
    std::vector<int> shapesToDelete = std::vector<int>();

    for (size_t i = 0; i < SceneController::getInstance().shapes.size(); i++) {
        for (size_t j = 0; j < SceneController::getInstance().shapes.size(); j++) {
            if (i != j && SceneController::getInstance().shapes[i].outline.intersects(SceneController::getInstance().shapes[j].outline)) {
                if (std::find(shapesToDelete.begin(), shapesToDelete.end(), i) == shapesToDelete.end()) {
                    shapesToDelete.push_back(i);
                }
                if (std::find(shapesToDelete.begin(), shapesToDelete.end(), j) == shapesToDelete.end()) {
                    shapesToDelete.push_back(j);
                }
            }
        }
    }

    QString output = "OUTPUT: ";

    for (size_t i = 0; i < shapesToDelete.size(); i++) {
        output += QString::number(shapesToDelete[i]) + "\t";
        SceneController::getInstance().deleteFigure(shapesToDelete[i] - i);
    }

    ui->statusbar->showMessage(output);

    this->update();
}


void ShapesMain::on_actionFit_Shapes_triggered()
{
  qreal width = this->size().width();
  qreal height = this->size().height();
  qreal margin = 3;
  qreal scaleValue = 1;
  qreal scaleStep = 0.1;

  std::sort(SceneController::getInstance().shapes.begin(), SceneController::getInstance().shapes.end(), [](Shape & lhs, Shape & rhs){
      return lhs.getHeight() >= rhs.getHeight();
  });

  while (scaleValue > 0.1) {
      bool completed = true;
      std::vector<Level> levels = std::vector<Level>();

      for (size_t i = 0; i < SceneController::getInstance().shapes.size(); i++) {
        SceneController::getInstance().set0Rotation(i);
        qreal shapeHeight = SceneController::getInstance().shapes[i].getHeight();
        qreal shapeWidth = SceneController::getInstance().shapes[i].getWidth();

        if (levels.empty()) {
            levels.push_back(Level(margin, shapeHeight + margin, width - 2 * margin));
        }

        double minFreeSpace = width + 10;
        size_t minSpaceIdx = 0;
        bool foundFit = false;

        for (size_t i = 0; i < levels.size(); i++) {
            if (levels[i].fits(shapeHeight, shapeWidth + 2 * margin)) {
                double freeSpace = levels[i].checkFreeSpace(shapeWidth + 2 * margin);
                if (freeSpace < minFreeSpace) {
                    minFreeSpace = freeSpace;
                    minSpaceIdx = i;
                }
                foundFit = true;
            }
        }
        if (foundFit) {
            SceneController::getInstance().moveToCoordinates(i, levels[minSpaceIdx].getUsedSpace() + margin, levels[minSpaceIdx].getStart());
            levels[minSpaceIdx].add(shapeWidth + 2 * margin);
        }
        else {
            double previousEnd = levels[levels.size() - 1].getEnd();
            levels.push_back(Level(previousEnd + margin, previousEnd + shapeHeight + margin, width - 2 * margin));
            SceneController::getInstance().moveToCoordinates(i, levels[levels.size() - 1].getUsedSpace() + margin, levels[levels.size() - 1].getStart());
            levels[levels.size() - 1].add(shapeWidth);

            if (margin + levels[levels.size() - 1].getEnd() >= height) {
                completed = false;
                break;
            }
        }
      }
    if (completed) {
        break;
    }

    scaleValue -= scaleStep;
    for (size_t i = 0; i < SceneController::getInstance().shapes.size(); i++) {
      SceneController::getInstance().scaleShape(i, 1 / SceneController::getInstance().shapes[i].getScaleValue());
      SceneController::getInstance().scaleShape(i, scaleValue);
    }
  }
  this->update();
}

void ShapesMain::on_actionTurn_On_Off_toggled(bool arg1)
{
    SceneController::getInstance().useRandom = arg1;
}

