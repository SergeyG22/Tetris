#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <j.h>
#include <o.h>
#include <t.h>
#include <shape.h>
#include <fieldofrectangles.h>
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildShape();
    void findRow();
    void destroyRow(int);
    void moveRows(int);
    void findAndDestroyRow();
    short random(int,int);
private:
    Ui::MainWindow *ui;
    QList<Shape*>shapes;
    FieldOfRectangles field;
    QSize size_shape;
    QTimer* timer;
    uint random_integer;
    std::random_device rd;
protected:
    void paintEvent(QPaintEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;
private slots:
    void moveToDown();
};
#endif // MAINWINDOW_H
