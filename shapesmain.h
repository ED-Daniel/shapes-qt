#ifndef SHAPESMAIN_H
#define SHAPESMAIN_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

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

protected:
    void paintEvent(QPaintEvent *);
};

#endif // SHAPESMAIN_H
