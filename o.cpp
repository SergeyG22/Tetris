#include "o.h"

O::O(QObject *parent):QObject(parent){
    window = dynamic_cast<QWidget*>(parent);
    shape_configuration.step = 20;
    shape_configuration.position = 0;
    shape_configuration.activity = false;
    shape_configuration.number_of_elements = 4;
}

void O::setParametersShape(int pos_x, int pos_y, QSize size_rect){
    shape_configuration.size = size_rect;
    if(checkArgumentsShape(pos_x,pos_y,size_rect)){
     if(!figure.isEmpty()) {
         destroyShape();
     }

     int x = pos_x;
     int y = pos_y;
     figure.push_front(QRect(QPoint(x , y),size_rect));
     figure.push_front(QRect(QPoint(x + 20, y), size_rect));
     figure.push_front(QRect(QPoint(x + 20, y + 20), size_rect));
     figure.push_front(QRect(QPoint(x , y + 20), size_rect));
     shape_configuration.position++;
    }
}




