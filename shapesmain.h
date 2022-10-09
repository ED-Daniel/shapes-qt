#ifndef SHAPESMAIN_H
#define SHAPESMAIN_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <stdexcept>

#include "editshapedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShapesMain; }
QT_END_NAMESPACE

class ShapesMain : public QMainWindow
{
    Q_OBJECT

public:
    ShapesMain(QWidget *parent = nullptr);
    ~ShapesMain();

private:
    Ui::ShapesMain *ui;

    bool canMoveObjects = true;

private slots:
    void deleteFigure(bool);
    void editFigure(bool);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // SHAPESMAIN_H
