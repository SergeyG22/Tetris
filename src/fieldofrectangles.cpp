#include "fieldofrectangles.h"


//создает поле истинности-ложности
void FieldOfRectangles::createField(QWidget* window){
    for(int i = 0; i <= window->height() / element_size; ++i) {
        QVector<bool>vector;
        for(int j = 0; j <= window->width() / element_size; ++j){
            vector.push_back(false);
        }
        field.push_back(vector);
    }
}


//заполняет строку истиными значениями
void FieldOfRectangles::setTruthFlags(const QList<QRect>&list){
    for(const QRect& rect : list){
        field[rect.y()/element_size][rect.x()/element_size] = true;
    }
}

//очищает поле, устанавливая все флаги в положение false
void FieldOfRectangles::clearField(QWidget* window){
    for(int i = 0; i <= window->height() / element_size; ++i) {
        for(int j = 0; j <= window->width() / element_size; ++j){
            field[i][j] = false;
        }
    }
}

//заполняет удаляемую строку ложными значениями
void FieldOfRectangles::makeRowFalse(int row){
   for(int i = 0; i <= (200/20)-1; ++i){
     field[row][i] = false;
   }
}

// проверяет столкновение с обьектом внизу (не с границей экрана)
bool FieldOfRectangles::bottomCollision(const QList<QRect>&list){
    for(const QRect& rect: list){
    if(field[((rect.y() + 20)/element_size)][rect.x() / element_size]){
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






