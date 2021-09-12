#include "fieldofrectangles.h"

void FieldOfRectangles::createField(QWidget* window){
    for(int i = 0; i <= window->height() / element_size; ++i) {
        QVector<bool>vector;
        for(int j = 0; j <= window->width() / element_size; ++j){
            vector.push_back(false);
        }
        field.push_back(vector);
    }
}


void FieldOfRectangles::setTruthFlags(const QList<QRect>&list){
    for(const QRect& rect : list){
        field[rect.y()/element_size][rect.x()/element_size] = true;
    }
}

// проверяет столкновение с обьектом внизу (не с границей экрана)
bool FieldOfRectangles::bottomCollision(const QList<QRect>&list){
    for(const QRect& rect: list){   //проверить коллизию
    if(field[((rect.y() + distance_to_collision)/element_size)][rect.x() / element_size]){

        qDebug() << rect.y();
        return true;
     }
   }
    return false;
}

// проверяет столкновение с обьектом справа
bool FieldOfRectangles::rightCollision(const QList<QRect>&list){
    for(const QRect& rect: list){
    if(field[(rect.y() / element_size)][(rect.x() + distance_to_collision) / element_size]){
        return true;
     }
   }
    return false;
}

// проверяет столкновение с обьектом слева
bool FieldOfRectangles::leftCollision(const QList<QRect>&list){
    for(const QRect& rect: list){
       int x = 0;
          if((rect.x() - distance_to_collision)/element_size >= 0){
             x = (rect.x() - distance_to_collision)/element_size;
             }
    if(field[(rect.y() / element_size)][x]){
        return true;
     }
   }
    return false;
}


//        for(int i = 0; i < 400 / 20; ++i) {
//            for(int j = 0; j < 200 / 20; ++j){
//                 std::cout << field[i][j]<<' ';
//            }
//            std::cout << std::endl;
//        }




