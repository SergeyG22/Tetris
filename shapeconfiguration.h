#ifndef SHAPECONFIGURATION_H
#define SHAPECONFIGURATION_H
#include <QSize>

struct ShapeConfiguration{
    QSize size;
    int step = 20;
    int position = 0;
    bool activity = false;
    int number_of_elements = 4;
};

#endif // SHAPECONFIGURATION_H
