//
// Created by solov on 2/16/2020.
//

#ifndef HW3_RECTANGLE_H
#define HW3_RECTANGLE_H

class Rectangle{
public:
    Rectangle(double x = 0, double y = 0, double h = 0, double w = 0);
    // will get the x coordinate of the rectangle and then return it.
    double getX() const {return m_x; }
    // will get the y coordinate of the rectangle and then return it.
    double getY() const {return m_y; }
    // will get the h coordinate of the rectangle and then return it.
    double getHeight() const {return m_h; }
    // will get the w coordinate of the rectangle and then return it.
    double getWidth() const { return m_w; }
    void setX (double x) {m_x = x; }
    void setY (double y) {m_y = y ;}
    void setHeight(double h);
    void setWidth(double w);
    void print () const;
    /* will compute the area of the a single rectangle when the width and height are given.
    will return the area (a double) */
    double area() const {return m_h*m_w; }
    double intersectArea (const Rectangle &rectangle)const;
    double unionArea (const Rectangle &rectangle)const;
    double intersectArea(const Rectangle &rectangle, const Rectangle &rectangle2) const;
    double unionArea(const Rectangle &rectangle, const Rectangle &r4) const;

private:
    double m_x;
    double m_y;
    double m_h;
    double m_w;
};


#endif //HW3_RECTANGLE_H
