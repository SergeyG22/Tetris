#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    field.createField(this);
    timer = new QTimer;
//    timer->start(500);
    buildShape();
    this->setFixedSize(QSize(200,400));
    connect(timer, &QTimer::timeout, this, &MainWindow::moveToDown);
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
    case Qt::Key::Key_S: {
        moveToDown();
    }


}
}

void MainWindow::moveToDown(){
    for(auto it = shapes.begin(); it!=shapes.end();++it){
      if(it.i->t()->getActivity()){
         if(it.i->t()->moveToDown(field)){      // вернет истину когда внизу препятствие
             field.setTruthFlags(it.i->t()->getShape());
             it.i->t()->setActivity(false);
             findAndDestroyRow();
             buildShape();
             break;
         }
        }
    }
}

short MainWindow::random(int first,int second){
        std::mt19937 rng(rd());
        std::uniform_int_distribution<quint32> uni(first,second);
        random_integer = uni(rng);
        return random_integer;
}


void MainWindow::buildShape(){
    Shape* shape = nullptr;
    shape = new T(this);
//  switch (random(0,1)) {
//    case 0:{
//        shape = new O(this);
//        break;
//        }
//    case 1:{
//        shape = new J(this);
//        break;
//        }
//    }

    shape->setActivity(true);
    size_shape.setWidth(20);
    size_shape.setHeight(20);
    shape->setParametersShape(0,0, size_shape);
    shapes.push_back(shape);
}

void MainWindow::destroyRow(int row){
    int pos_y = row * size_shape.width();
    for(auto it = shapes.begin(); it!=shapes.end();++it){
        for(auto iter = it.i->t()->getShape().begin(); iter!=it.i->t()->getShape().end(); ){
             if(iter.i->t().y() == pos_y){
                     iter = it.i->t()->getShape().erase(iter);
             }else{
                 ++iter;
             }
        }
    }
}

void MainWindow::findAndDestroyRow(){
    int pos_x = (this->width() / size_shape.width())-1;
    int pos_y = (this->height() / size_shape.width())-1;
    for(int row = 0; row <= pos_y; ++row){
       for(int column = 0; column <= pos_x; ++column){
           if(!field.getField()[row][column]){
               break;
           }
           if(column==pos_x){
              destroyRow(row);
              field.clearField(this);
              moveRows(row);
           }
       }
    }
}

void MainWindow::moveRows(int row){
    for(auto it = shapes.begin(); it!=shapes.end();++it){
        for(auto iter = it.i->t()->getShape().begin(); iter!=it.i->t()->getShape().end(); ++iter){
            if((row * size_shape.width())  > iter.i->t().y()){
             iter.i->t().moveTo(iter.i->t().x(), iter.i->t().y() + size_shape.width());
            }
        }
    }
    for(auto it = shapes.begin(); it!=shapes.end();++it){
        field.setTruthFlags(it.i->t()->getShape());
    }

}



























































