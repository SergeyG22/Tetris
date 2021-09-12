#ifndef FIELDOFRECTANGLES_H
#define FIELDOFRECTANGLES_H
#include <QVector>
#include <QWidget>
#include <QDebug>
#include <iostream>
//

class FieldOfRectangles{
    QVector<QVector<bool>>field;
    int distance_to_collision = 20;
    int element_size = 20;
public:
    QVector<QVector<bool>>&getField(){ return field;};
    void createField(QWidget*);
    void setTruthFlags(const QList<QRect>&);
    bool bottomCollision(const QList<QRect>&);
    bool rightCollision(const QList<QRect>&);
    bool leftCollision(const QList<QRect>&);
};

#endif // FIELDOFRECTANGLES_H
