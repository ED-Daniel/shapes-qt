#include "editshapedialog.h"
#include "ui_editshapedialog.h"

EditShapeDialog::EditShapeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditShapeDialog)
{
    ui->setupUi(this);
}

EditShapeDialog::~EditShapeDialog()
{
    delete ui;
}

void EditShapeDialog::on_submitDialogBox_accepted()
{
    qreal width = qStringToDouble(ui->widthEdit->text());
    qreal height = qStringToDouble(ui->heightEdit->text());
    qreal angle = qStringToDouble(ui->rotationEdit->text());
    qreal x = qStringToDouble(ui->xEdit->text());
    qreal y = qStringToDouble(ui->yEdit->text());

    SceneController::getInstance().height = height;
    SceneController::getInstance().width = width;

    SceneController::getInstance().deleteSelectedFigure();
    SceneController::getInstance().createFirstShape(x, y);
    SceneController::getInstance().rotateFigure(SceneController::getInstance().shapes.size() - 1, angle);
}

double EditShapeDialog::qStringToDouble(const QString &value)
{
    double ret;
    if (value.isEmpty())
        ret = std::numeric_limits<double>::quiet_NaN();
    else
        ret = value.toDouble();
    return ret;
}

