//
// Created by solov on 2/16/2020.
//

#include <iostream>
#include "Rectangle.h"
using namespace std;
/* Rectangle constructor that will initialize all four points to zero.
Inputs are doubles of the four points. Outputs are the four doubles of the private variables.
Also calls setHeight and setWidth to make sure that if the values are negative it will return 0.*/
Rectangle :: Rectangle(double x , double y, double h, double w ): m_x{x}, m_y{y} {
    setHeight(h);
    setWidth(w);
}
/* setHeight method that will make sure that if a negative value is given for the height, it will return 0.
Input is the double H.
Output is the value in the private (m_h).
*/
void Rectangle::setHeight(double H) {
    if(H >= 0){
        m_h = H;
    } else{
        m_h = 0;
    }

}
/* setWidth method that will make sure that if a negative value is given for the width, it will return 0.
Input is the double W.
Output is the value in the private (m_w).
*/
void Rectangle::setWidth(double W) {
    if(W >= 0){
        m_w = W;
    } else {
        m_w = 0;
    }

}
/* Print method that will print the four values for the rectangle in an neat way.
 Since the method is the a void function there is no return type.
 */
void Rectangle :: print() const {
    cout << " \n Rectangle: " ;
    cout <<"x = " << m_x ;
    cout <<" y = " << m_y ;
    cout <<" h = " << m_h ;
    cout <<" w = " << m_w  ;

}
/*IntersectArea method will take look at the points of the TWO rectangles by using the getters and setters and the method of "this->" and compute the intersecting area of the two rectangles,
equations were given to us and it will also make sure that if the width or height is negative it will return 0 (b/c they don't overlap)
Input is both rectangle four points although there is only one parameter
Output is the area of the intersection (a double)
 */
double Rectangle :: intersectArea(const Rectangle &rectangle) const {
    double W = min(rectangle.getX() + rectangle.getWidth(), this->m_x + this -> m_w) - max(rectangle.getX(), this ->m_x);
    double H = min(rectangle.getY() + rectangle.getHeight(), this ->m_y + this ->m_h) - max(rectangle.getY(), this ->m_y);
    if((W > 0) && (H > 0)){
        return W*H;
    } else{
        return 0;
    }

    }
/*Unionarea method will take look at the points of the TWO rectangles and compute the union area of the two rectangles.
It will use the area and intersectArea functions to compute the union area with the given equation.
Input is both rectangle four points although there is only one parameter.
Output is the area of the union (a double).
 */

double Rectangle ::unionArea(const Rectangle &rectangle) const {
    double A = rectangle.area();
    double B = area();
    double C = intersectArea(rectangle);
    return abs(A)+abs(B) - abs(C);

}
/*IntersectArea method will take look at the points of the THREE rectangles by using getters and setters and the method of "this->" and compute the intersecting area of the three rectangles,
equations were given to us and it will also make sure that if the width or height is negative it will return 0 (b/c they don't overlap)
Input is all three rectangle four points although there are only two parameters
Output is the area of the intersection (a double)
 */
double Rectangle :: intersectArea(const Rectangle &rectangle, const Rectangle &rectangle2) const {
    double c = rectangle.getX() + rectangle.getWidth();
    double g = rectangle2.getX() + rectangle2.getWidth();
    double k = this->m_x + this->m_w;
    double a = rectangle.getX();
    double e = rectangle2.getX();
    double i = this->m_x;
    double W = min(min(c,g), k) - max(max(a,e), i);

    double d = rectangle.getY() + rectangle.getHeight();
    double h = rectangle2.getY() + rectangle2.getHeight();
    double m = this->m_y + this->m_h;
    double b = rectangle.getY();
    double f = rectangle2.getY();
    double j = this->m_y;

    double H = min(min(d,h), m) - max(max(b,f), j);
    if ((W > 0) &&  (H > 0)) {
        return W * H;
    } else {
        return 0;
    }

}
/*Unionarea method will take look at the points of the THREE rectangles and compute the union area of the two rectangles.
It will use the area and intersectArea functions to compute the union area with the given equation.
Input is all three rectangle four points although there is only two parameter.
Output is the area of the union (a double).
 */

double Rectangle :: unionArea(const Rectangle &rectangle, const Rectangle &rectangle2)const  {
    double A = rectangle.area();
    double B = rectangle2.area();
    double C = area();

    return abs(A) + abs(B) + abs(C) - abs(intersectArea(rectangle)) - abs(intersectArea(rectangle2)) - abs(rectangle.intersectArea(rectangle2)) + abs(intersectArea(rectangle2, rectangle));
}
