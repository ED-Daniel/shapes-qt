#ifndef SHAPESMAIN_H
#define SHAPESMAIN_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

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

private slots:
    void deleteFigure(bool);
    void editFigure(bool);
    void repaint();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

#endif // SHAPESMAIN_H
