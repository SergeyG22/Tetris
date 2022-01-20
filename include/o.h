#ifndef O_H
#define O_H
#include <shape.h>
#include <algorithm>
#include "shapeconfiguration.h"

class O:public QObject,public Shape{
    Q_OBJECT
public:
    O(QObject* parent);
    void setParametersShape(int,int,QSize) override;
};

#endif // O_H
