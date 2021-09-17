#ifndef J_H
#define J_H
#include <shape.h>
#include <algorithm>
#include "shapeconfiguration.h"

class J:public QObject,public Shape{
    Q_OBJECT
public:
    J(QObject *parent);
    void rotateShape() override;
    void setParametersShape(int,int,QSize) override;
    bool intersection(FieldOfRectangles&)override;
};

#endif // J_H
