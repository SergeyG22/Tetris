#include "i.h"

I::I(QObject *parent):QObject(parent){
   window = dynamic_cast<QWidget*>(parent);
   shape_configuration.step = 20;
   shape_configuration.position = 0;
   shape_configuration.activity = false;
   shape_configuration.number_of_elements = 4;
}

//установить начальные параметры фигуры
void I::setParametersShape(int pos_x, int pos_y, QSize size_rect){
    shape_configuration.size = size_rect;
    if(checkArgumentsShape(pos_x,pos_y,size_rect)){
     if(!figure.isEmpty()) {
         destroyShape();
     }

     int x = pos_x;
     int y = pos_y + 20;
     figure.push_front(QRect(QPoint(x , y),size_rect));
     figure.push_front(QRect(QPoint(x + 20, y), size_rect));
     figure.push_front(QRect(QPoint(x + 40, y), size_rect));
     figure.push_front(QRect(QPoint(x + 60, y), size_rect));
     shape_configuration.position++;
    }
}

void I::rotateShape(){
    switch(shape_configuration.position){
    case 0: {
        int x = figure.value(2).x();
        int y = figure.value(2).y();
      if(figure.value(1).x() + 40 < window->width() && figure.value(1).x() - 20 >= 0){  //условие при котором запрещено вращать фигуры у правой и левой стены
        if(!figure.isEmpty()) {
            destroyShape();
        }
        figure.push_front(QRect(QPoint(x - 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 20, y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x + 40, y), shape_configuration.size));
        window->repaint();
        shape_configuration.position++;
    }
        break;
    }

   case 1: {
        int x = figure.value(2).x(); //1
        int y = figure.value(2).y(); //1      
   if(figure.first().y() + 40 < window->height()){
      if(!figure.isEmpty()) {
        destroyShape();
    }
        figure.push_front(QRect(QPoint(x , y - 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x , y), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 20), shape_configuration.size));
        figure.push_front(QRect(QPoint(x, y + 40), shape_configuration.size));
        window->repaint();
        shape_configuration.position = 0;
      }
    }
        break;
}
}

bool I::intersection(FieldOfRectangles& field){
    switch (shape_configuration.position) {
    case 1: {
      int x = figure.value(3).x();
      int y = figure.value(3).y();
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
                    if(field.getField()[(y - 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
                        return false;
                    }
                    if(field.getField()[(y + 20) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
                        return false;
                    }
                    if(field.getField()[(y + 40) / shape_configuration.size.width()][x / shape_configuration.size.width()]){
                        return false;
                    }
         }
      break;
    }
    case 0:{                             //первое положение
      int x = figure.value(2).x();  //1
      int y = figure.value(2).y();  //1
      if( figure.value(1).x() - 20 >= 0){
      if(y / shape_configuration.size.width() >= 0 && x/shape_configuration.size.width() >=0) {
                    if(field.getField()[y / shape_configuration.size.width()][(x - 20) / shape_configuration.size.width()]){
                        return false;
                    }
                    if(field.getField()[y / shape_configuration.size.width()][(x + 20) / shape_configuration.size.width()]){
                        return false;
                    }
                    if(field.getField()[y / shape_configuration.size.width()][(x + 40) / shape_configuration.size.width()]){
                        return false;
                    }
         }
      }
      break;
    }
 }
    return true;
}
