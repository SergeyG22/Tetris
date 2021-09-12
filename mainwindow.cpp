#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    field.createField(this);
    timer = new QTimer;
    timer->start(500);
    buildShape();
    this->setFixedSize(QSize(200,400));
    connect(timer, &QTimer::timeout, this, &MainWindow::moveShapeByTimer);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
        painter.setPen(Qt::blue);
        for(auto it = shapes.begin(); it!=shapes.end();++it){
            for(const QRect& rect : it.i->t()->getShape()){
                painter.drawRect(rect);
            }
        }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_Space:{
            for(auto it = shapes.begin(); it!=shapes.end();++it){
              //если обьект активный и нет препятствий для вращения
              if(it.i->t()->getActivity() && it.i->t()->intersection(field)){
                it.i->t()->rotateShape();        // то повернуть обьект
                }
            }
            break;
         }
    case Qt::Key::Key_A:{
        qDebug()<<"acac";
        for(auto it = shapes.begin(); it!=shapes.end();++it){
          if(it.i->t()->getActivity() && !field.leftCollision(it.i->t()->getShape())){
            it.i->t()->moveToLeft();
            }
        }
        break;

    }
    case Qt::Key::Key_D:{
        for(auto it = shapes.begin(); it!=shapes.end();++it){
          if(it.i->t()->getActivity() && !field.rightCollision(it.i->t()->getShape())){
            it.i->t()->moveToRight();
            }
        }
        break;
    }


}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

}

void MainWindow::moveShapeByTimer(){
    for(auto it = shapes.begin(); it!=shapes.end(); it++){
            if((it.i->t()->moveShape() && it.i->t()->getActivity()) ||
                    //если обьект обнаружил препятствие снизу  и этот обьект активный
                    (field.bottomCollision(it.i->t()->getShape()) && it.i->t()->getActivity())) {
                field.setTruthFlags(it.i->t()->getShape());  // установить флаги этого обьекта
                it.i->t()->setActivity(false);               // сделать обьект не активным
                buildShape();                                // собрать новый обьект
                break;
            }
        }
}

void MainWindow::buildShape(){
    Shape* shape = new J(this);
    shape->setActivity(true);
    shape->setParametersShape(0,0, QSize(20,20));
    shapes.push_back(shape);
}
































































