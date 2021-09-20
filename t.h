#ifndef T_H
#define T_H
#include <shape.h>
#include "shapeconfiguration.h"

class T:public QObject,public Shape{
    Q_OBJECT
public:
    T(QObject *parent);
    void rotateShape() override;
    void setParametersShape(int,int,QSize) override;
};

#endif // T_H
