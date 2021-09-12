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
     if(!figure_j.isEmpty()) {
         destroyShape();
     }

     int x = pos_x;
     int y = pos_y;
     figure_j.push_front(QRect(QPoint(x , y),size_rect));
     figure_j.push_front(QRect(QPoint(x , y + 20), size_rect));
     figure_j.push_front(QRect(QPoint(x + 20, y + 20), size_rect));
     figure_j.push_front(QRect(QPoint(x + 40, y + 20), size_rect));
     shape_configuration.position++;
    }
}

QList<QRect>& J::getShape(){
    return figure_j;
}

//движение по таймеру
bool J::moveShape(){
     for(int i = 0; i < figure_j.size(); ++i){
         //если конец остановить
         if(figure_j.value(i).y() == window->height() - shape_configuration.size.width()){
             return true;
         }
     }

    if(shape_configuration.activity){
      for(QRect& rect: figure_j){
          int y = rect.y() + shape_configuration.step;
          rect.moveTo(rect.x(),y);
          repaintShape();
      }
     }
    return false;
}

//проверка на корректность входящих данных
bool J::checkArgumentsShape(int pos_x, int pos_y, QSize size_rect){
    if(pos_x < 0 || pos_y < 0 || size_rect.width() < 0 || size_rect.height() < 0){
        perror("argument is less than zero");
        return false;
    }
    return true;
}

//движение вправо
void J::moveToRight(){
   if(shape_configuration.activity){
       if(std::all_of(figure_j.begin(), figure_j.end(), [&](QRect i){ return i.x() < window->width() - shape_configuration.size.width();})){
              for(QRect &rect: figure_j){
                  rect.moveTo(rect.x() + rect.size().width(),rect.y());
                    repaintShape();
                 }
        }
   }
}

//движение влево
void J::moveToLeft(){
    if(shape_configuration.activity){
       if(std::all_of(figure_j.begin(), figure_j.end(), [](QRect i){ return i.x() - i.size().width() >= 0;})){
           for(QRect &rect: figure_j) {
                 rect.moveTo(rect.x() - rect.size().width(),rect.y());
                 repaintShape();
                }
         }
      }
}

//вращение фигуры
void J::rotateShape(){
    switch(shape_configuration.position){
    case 0: {                               //второе положение
        int x = figure_j.value(3).x() - 20; //2
        int y = figure_j.value(3).y();      //2
      if(figure_j.value(1).x() + 20 < window->width()){  //условие при котором запрещено вращать фигуры у правой стены
        if(!figure_j.isEmpty()) {
            destroyShape();
        }
        figure_j.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x , y + 20), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 20, y + 20), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 40, y + 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
    }

   case 1: {                               //первое положение
        int x = figure_j.last().x() + 20; //1
        int y = figure_j.last().y();      //1
    if(figure_j.value(1).y() + 20 < window->height()) {   // условие при котором запрещено вращение у нижней стены
      if(!figure_j.isEmpty()) {
        destroyShape();
    }
        figure_j.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x, y + 40), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
    }

    case 2: {                               //четвертое положение
        int x = figure_j.value(1).x() - 20; //4
        int y = figure_j.value(1).y();      //4
       if( figure_j.value(1).x() - 20 >= 0){        //условие при котором запрещено вращать фигуру у левой стены
        if(!figure_j.isEmpty()) {
            destroyShape();
        }
        figure_j.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 40, y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x + 40, y + 20), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
         }
        break;
    }

    case 3: {                               //третье положение
        int x = figure_j.value(2).x();      //3
        int y = figure_j.value(2).y() - 20; //3
        if(!figure_j.isEmpty()) {
            destroyShape();
        }
        figure_j.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x , y + 20), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x , y + 40), shape_configuration.size));
        figure_j.push_front(QRect(QPoint(x - 20 , y + 40), shape_configuration.size));
        window->repaint();
        shape_configuration.position = 0;
         }
        break;
    }

}

bool J::intersection(FieldOfRectangles& field){
    switch (shape_configuration.position) {
    case 0: {
      int x = figure_j.value(1).x();  //4
      int y = figure_j.value(1).y();  //4
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y - 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              qDebug() << "case 0: 1";
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              qDebug() << "case 0: 2";
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              qDebug() << "case 0: 3";
              return false;
          }
         }
      break;
    }
    case 1:{
      int x = figure_j.value(1).x();  //1
      int y = figure_j.value(1).y();  //1
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y + 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              qDebug() << "case 1: 1";
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
              qDebug() << "case 1: 2";
              return false;
          }
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              qDebug() << "case 1: 3";
              return false;
          }
         }
      break;
    }
    case 2:{
      int x = figure_j.value(1).x();  //2
      int y = figure_j.value(1).y();  //2
      if( figure_j.value(1).x() - 20 >= 0){        //условие которое преодтвращает выход за диапазон вектора
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[y / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              qDebug() << "case 2: 1";
              return false;
          }
          if(field.getField()[y / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              qDebug() << "case 2: 2";
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
              qDebug() << "case 2: 3";
              return false;
          }
         }
      }
      break;
    }
    case 3:{
      int x = figure_j.value(1).x();  //3
      int y = figure_j.value(1).y();  //3
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
          if(field.getField()[(y - 20) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              qDebug() << "case 3: 1";
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
              qDebug() << "case 3: 2";
              return false;
          }
          if(field.getField()[(y + 20) / shape_configuration.size.width()][(x - 40) / shape_configuration.size.width()]){
              qDebug() << "case 3: 3";
              return false;
          }
         }
      break;
    }

    }
    return true;
}

