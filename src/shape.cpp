#include "shape.h"

Shape::~Shape(){

}

bool Shape::moveShape(){
    for(int i = 0; i < figure.size(); ++i){
        //если конец остановить
        if(figure.value(i).y() == window->height() - shape_configuration.size.width()){
            return true;
        }
    }

   if(shape_configuration.activity){
     for(QRect& rect: figure){
         int y = rect.y() + shape_configuration.step;
         rect.moveTo(rect.x(),y);
         repaintShape();
     }
    }
   return false;
}

bool Shape::checkArgumentsShape(int pos_x, int pos_y, QSize size_rect){
    if(pos_x < 0 || pos_y < 0 || size_rect.width() < 0 || size_rect.height() < 0){
        perror("argument is less than zero");
        return false;
    }
    return true;
}

void Shape::moveToRight(){
    if(shape_configuration.activity){
        if(std::all_of(figure.begin(), figure.end(), [&](QRect i){ return i.x() < window->width() - shape_configuration.size.width();})){
               for(QRect &rect: figure){
                   rect.moveTo(rect.x() + rect.size().width(),rect.y());
                     repaintShape();
                  }
         }
    }
}

void Shape::moveToLeft(){
    if(shape_configuration.activity){
       if(std::all_of(figure.begin(), figure.end(), [](QRect i){ return i.x() - i.size().width() >= 0;})){
           for(QRect &rect: figure) {
                 rect.moveTo(rect.x() - rect.size().width(),rect.y());
                 repaintShape();
                }
         }
      }
}

bool Shape::moveToDown(FieldOfRectangles& field){
    if(shape_configuration.activity){
        if(std::all_of(figure.begin(), figure.end(), [&](QRect i){ return i.y() + i.size().width() < window->height();})){
            if(field.bottomCollision(figure)){
                return true;
            }
        for(QRect &rect: figure) {
              rect.moveTo(rect.x(),rect.y() + rect.size().width());
              repaintShape();
             }

          for(QRect &rect: figure){
           if(rect.y() + rect.size().width() == window->height()){
             return true;
           }
          }
        }

    }
    return false;
}

