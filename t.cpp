#include "t.h"

T::T(QObject *parent):QObject(parent){
    window = dynamic_cast<QWidget*>(parent);
    shape_configuration.step = 20;
    shape_configuration.position = 0;
    shape_configuration.activity = false;
    shape_configuration.number_of_elements = 4;
}

void T::setParametersShape(int pos_x, int pos_y, QSize size_rect){
    shape_configuration.size = size_rect;
    if(checkArgumentsShape(pos_x,pos_y,size_rect)){
     if(!figure.isEmpty()) {
         destroyShape();
     }

     int x = pos_x + 20;
     int y = pos_y + 20;
     figure.push_front(QRect(QPoint(x , y),size_rect));       //0
     figure.push_front(QRect(QPoint(x + 20, y),size_rect));   //1
     figure.push_front(QRect(QPoint(x, y + 20),size_rect));   //2
     figure.push_front(QRect(QPoint(x - 20, y),size_rect));   //3
     shape_configuration.position++;
    }
}

void T::rotateShape(){
    switch(shape_configuration.position){
    case 0: {
        int x = figure.value(3).x();      //4
        int y = figure.value(3).y();      //4
     if(figure.value(3).x()-20 >= 0){   //условие при котором запрещено вращать фигуры у левой стены
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x - 20, y), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
}
        break;
    }

   case 1: {
        int x = figure.value(3).x();      //0
        int y = figure.value(3).y();      //0

      if(!figure.isEmpty()) {
        destroyShape();
    }
        figure.push_front(QRect(QPoint(x, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x - 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y - 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
        break;
    }

    case 2: {
        int x = figure.value(3).x();      //1
        int y = figure.value(3).y();      //1

    if(figure.value(3).x() + 20 < window->width()){ // условие при котором запрещено вращать фигуры у правой стены
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x - 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y - 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
     }

    case 3: {
        int x = figure.value(3).x(); //2
        int y = figure.value(3).y(); //2
      if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y - 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position = 0;
        }
        break;
    }
}
