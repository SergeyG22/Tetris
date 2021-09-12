#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <j.h>
#include <shape.h>
#include <fieldofrectangles.h>

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
private:
    Ui::MainWindow *ui;
    QList<Shape*>shapes;
    FieldOfRectangles field;
    QTimer* timer;
protected:
    void paintEvent(QPaintEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;
    void keyReleaseEvent(QKeyEvent* event)override;
private slots:
    void moveShapeByTimer();
};
#endif // MAINWINDOW_H
