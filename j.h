#ifndef J_H
#define J_H
#include <shape.h>
#include <algorithm>
#include "shapeconfiguration.h"

class J:public QObject,public Shape{
    Q_OBJECT
    QList<QRect>figure_j;
    QWidget *window;
    ShapeConfiguration shape_configuration;
    bool checkArgumentsShape(int,int,QSize);
public:
    J(QObject *parent);
    QList<QRect>& getShape() override;
    void moveToRight()override;
    void moveToLeft()override;
    void rotateShape() override;
    void setParametersShape(int,int,QSize) override;
    bool intersection(FieldOfRectangles&)override;
    inline void destroyShape()override { figure_j.clear(); };
    inline void setActivity(bool activity)override{ shape_configuration.activity = activity;};
    inline bool getActivity()const override { return shape_configuration.activity;};
    inline void repaintShape()override { window->repaint();};
    bool moveShape()override;
};

#endif // J_H
