#ifndef SHAPE_H
#define SHAPE_H
#include <QRect>
#include <QVector2D>
#include <QObject>
#include <QTimer>
#include "fieldofrectangles.h"
#include <shapeconfiguration.h>

class Shape{
protected:
    ShapeConfiguration shape_configuration;
    QWidget *window;
    QList<QRect>figure;
public:
    inline virtual bool getActivity()const        { return shape_configuration.activity;}
    inline virtual void setActivity(bool activity){ shape_configuration.activity = activity;};
    inline void destroyShape() { figure.clear(); };
    inline void repaintShape() { window->repaint();};
    virtual bool checkArgumentsShape(int,int,QSize);
    virtual bool moveShape();
    virtual void moveToRight();
    virtual void moveToLeft();
    virtual bool moveToDown(FieldOfRectangles&);
    virtual void rotateShape(){ };
    virtual QList<QRect>& getShape(){ return figure; };
    virtual void setParametersShape(int,int,QSize) = 0;
    virtual bool intersection(FieldOfRectangles&){  return true; };
    virtual ~Shape();
};


#endif // SHAPE_H
