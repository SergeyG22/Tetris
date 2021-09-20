#ifndef I_H
#define I_H
#include <shape.h>
#include <algorithm>
#include "shapeconfiguration.h"

class I:public QObject,public Shape{
    Q_OBJECT
public:
    I(QObject *parent);
    void rotateShape() override;
    void setParametersShape(int,int,QSize) override;
    bool intersection(FieldOfRectangles&)override;
};

#endif // I_H
