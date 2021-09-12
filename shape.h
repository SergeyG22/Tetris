#ifndef SHAPE_H
#define SHAPE_H
#include <QRect>
#include <QVector2D>
#include <QObject>
#include <QTimer>
#include "fieldofrectangles.h"

class Shape{
public:
    virtual void setActivity(bool) = 0;
    virtual bool getActivity()const = 0;
    virtual bool moveShape() = 0;
    virtual void moveToRight() = 0;
    virtual void moveToLeft() = 0;
//  virtual bool moveToBottom() = 0;
    virtual void rotateShape(){ };
    virtual void destroyShape() = 0;
    virtual void repaintShape() = 0;
    virtual QList<QRect>& getShape() = 0;
    virtual void setParametersShape(int,int,QSize) = 0;
  //virtual QVector2D getCoordinateElementOfShape(int)const = 0;
    virtual bool intersection(FieldOfRectangles&) = 0;
  //virtual bool checkFieldValues(int,int,FieldOfRectangles&) = 0;
    virtual ~Shape() {
    } ;
};


#endif // SHAPE_H
