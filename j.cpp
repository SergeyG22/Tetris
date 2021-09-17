#include "j.h"

J::J(QObject *parent):QObject(parent){
   window = dynamic_cast<QWidget*>(parent);
   shape_configuration.step = 20;
   shape_configuration.position = 0;
   shape_configuration.activity = false;
   shape_configuration.number_of_elements = 4;
}

//установить начальные параметры фигуры
void J::setParametersShape(int pos_x, int pos_y, QSize size_rect){
    shape_configuration.size = size_rect;
    if(checkArgumentsShape(pos_x,pos_y,size_rect)){
     if(!figure.isEmpty()) {
         destroyShape();
     }

     int x = pos_x;
     int y = pos_y;
     figure.push_front(QRect(QPoint(x , y),size_rect));
     figure.push_front(QRect(QPoint(x , y + 20), size_rect));
     figure.push_front(QRect(QPoint(x + 20, y + 20), size_rect));
     figure.push_front(QRect(QPoint(x + 40, y + 20), size_rect));
     shape_configuration.position++;
    }
}

//вращение фигуры
void J::rotateShape(){
    switch(shape_configuration.position){
    case 0: {                               //второе положение
        int x = figure.value(3).x() - 20; //2
        int y = figure.value(3).y();      //2
      if(figure.value(1).x() + 20 < window->width()){  //условие при котором запрещено вращать фигуры у правой стены
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 40, y + 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
    }

   case 1: {                               //первое положение
        int x = figure.last().x() + 20; //1
        int y = figure.last().y();      //1
    if(figure.value(1).y() + 20 < window->height()) {   // условие при котором запрещено вращение у нижней стены
      if(!figure.isEmpty()) {
        destroyShape();
    }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 40), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
    }

    case 2: {                               //четвертое положение
        int x = figure.value(1).x() - 20; //4
        int y = figure.value(1).y();      //4
       if( figure.value(1).x() - 20 >= 0){        //условие при котором запрещено вращать фигуру у левой стены
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 40, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 40, y + 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
         }
        break;
    }

    case 3: {                               //третье положение
        int x = figure.value(2).x();      //3
        int y = figure.value(2).y() - 20; //3
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y + 40), shape_configuration.size));
        figure.push_front(QRect(QPoint(x - 20 , y + 40), shape_configuration.size));
        window->repaint();
        shape_configuration.position = 0;
         }
        break;
    }
}

bool J::intersection(FieldOfRectangles& field){
    switch (shape_configuration.position) {   // четвертое положение
    case 0: {
      int x = figure.value(1).x();  //4
      int y = figure.value(1).y();  //4
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y - 40) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              return false;
          }
         }
      break;
    }
    case 1:{                             //первое положение
      int x = figure.value(1).x();  //1
      int y = figure.value(1).y();  //1
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y + 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              return false;
          }
         }
      break;
    }
    case 2:{                             //второе положение
      int x = figure.value(1).x();  //2
      int y = figure.value(1).y();  //2
      if( figure.value(1).x() - 20 >= 0){        //условие которое преодтвращает выход за диапазон вектора
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[y / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[y / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              return false;
          }
         }
      }
      break;
    }
    case 3:{                           //третье положение
      int x = figure.value(1).x();  //3
      int y = figure.value(1).y();  //3
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x - 40) / shape_configuration.size.width()]){
              return false;
          }
         }
      break;
    }

    }
    return true;
}











