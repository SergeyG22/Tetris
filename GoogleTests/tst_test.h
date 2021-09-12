#ifndef TST_TEST_H
#define TST_TEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "shape.h"
#include "i.h"

using namespace testing;

TEST(I, Position_Rectangle_A){
 I i;
 i.setParametersShape(0,0, QSize(20,20));
 QVector2D rect_a =  i.getCoordinateElementOfShape(3);
 ASSERT_EQ(0,rect_a.x());
 ASSERT_EQ(0,rect_a.y());
}

TEST(I, Position_Rectangle_B)
{
 I i;
 i.setParametersShape(0,0, QSize(20,20));
 QVector2D rect_b =  i.getCoordinateElementOfShape(2);
 ASSERT_EQ(0,rect_b.x());
 ASSERT_EQ(20,rect_b.y());
}

TEST(I, Position_Rectangle_C)
{
 I i;
 i.setParametersShape(0,0, QSize(20,20));
 QVector2D rect_c =  i.getCoordinateElementOfShape(1);
 ASSERT_EQ(0,rect_c.x());
 ASSERT_EQ(40,rect_c.y());
}

TEST(I, Position_Rectangle_D)
{
 I i;
 i.setParametersShape(0,0, QSize(20,20));
 QVector2D rect_d =  i.getCoordinateElementOfShape(0);
 ASSERT_EQ(0,rect_d.x());
 ASSERT_EQ(60,rect_d.y());
}





#endif // TST_TEST_H
