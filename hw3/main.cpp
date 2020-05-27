/*Name: Louie Solovy
Date: 2/25/2020
Name of program: Rectangle class program
Description of program: With the rectangle class, it stores the coordinates of the rectangles (x,y,h,w). There are methods
that will compute the union area and the intersecting area up to three rectangles. There is also a file with this program
that has hard coded inputs (x,y,h,w) for multiple rectangles that will also compute the union and intersecting area of those
rectangles.
 */

#include <iostream>
#include "Rectangle.h"
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // will read in my file of data.txt and will make sure that the file can open, if not will return and error message.
    ifstream fin("data.txt"); // Attempt to open file

    if (fin.fail()){
        cout << "Error: could not open data.txt";
        return -1;
    }
    double x;
    double y;
    double h;
    double w;


    vector <Rectangle> Rectangles;
    // will read through the file of rectangles four points and but them in a vector
    while (fin.good()){
        fin >> x >> y >> h >> w;
        Rectangle R(x,y,h,w);
        Rectangles.push_back(R);
    }
    // will print the points (x,y,h,w) of all the rectangles in the vector.
    cout << " RECTANGLES FROM THE FILE";
    for(Rectangle Rec : Rectangles){
        Rec.print();
    }
    /* will compute the intersection area and the union area for three rectangles. Will take the first three of rectangles and then the next
    ...etc, and so on until the loop reaches the end of the file.*/
    for (int i = 0; i < Rectangles.size()-3; i++){
        Rectangle R = Rectangles[i];
        cout << "\n Rectangles: "<< i+1 << "," << i+2 << "," << i+3 <<  " " << "IntersectArea: "<< R.intersectArea(Rectangles[i+1],Rectangles[i+2]);
        cout << "\n Rectangles: "<< i+1 << "," << i+2 << "," << i+3 <<  " " << "UnionArea: "<< R.unionArea(Rectangles[i+1],Rectangles[i+2]);

    }
    // unit testing to make sure that all the methods work and that the expected values actually equal the actual value.
    cout << "\n" << endl;
    Rectangle r3(2,2,2,2);
    r3.print();
    Rectangle r4(1,1,3,3);
    r4.print();
    Rectangle r5(1,1,2,2);
    r5.print();
    cout << "\nr3 = (2,2,2,2), r4=(1,1,3,3), r5= (1,1,2,2)";
    cout << "\nExpected value of r5.intersectArea is 4. Actual value is : "<< r5.intersectArea(r4);
    cout << "\nExpected value of r5.unionArea is 9. Actual value is : " << r5.unionArea(r4);
    cout << "\nExpected value of r5.intersectArea is 1. Actual value is : "<< r5.intersectArea(r4,r3);
    cout << "\nExpected value of r5.unionArea is 9. Actual value is :" << r5.unionArea(r4,r3);
    cout <<"\nExpected value of r4.getWidth is 3. Actual value is : "<< r4.getWidth();
    cout <<"\nExpected value of r4.getHeight is 3. Actual value is : "<< r4.getHeight();
    cout <<"\nExpected value of r4.area is 9. Actual value is : " << r4.area();
    Rectangle r0(-1);
    r0.print();
    Rectangle r1;
    r1.print();
    Rectangle r2(1,1,-1);
    r2.print();
    cout << "\nr0 =(-1,0,0,0), r1 = (0,0,0,0), r2(1,1,0,0)";
    cout << "\nExpected value of r0.intersectArea is 0. Actual value is : "<< r0.intersectArea(r1);
    cout << "\nExpected value of r0.unionArea is 0. Actual value is : " << r0.unionArea(r1);
    cout << "\nExpected value of r0.intersectArea is 0. Actual value is : "<< r0.intersectArea(r1,r2);
    cout << "\nExpected value of r0.unionArea is 0. Actual value is :" << r0.unionArea(r1,r2);
    cout <<"\nExpected value of r0.getWidth is 0. Actual value is : "<< r0.getWidth();
    cout <<"\nExpected value of r0.getHeight is 0. Actual value is : "<< r0.getHeight();
    cout <<"\nExpected value of r0.area is 0. Actual value is : " << r0.area();
    Rectangle r6(4,4,4,4);
    r6.print();
    Rectangle r7(-2,3,0,0);
    r7.print();
    Rectangle r8(2,3,1,0);
    r8.print();
    cout << "\nr0 =(4,4,4,4), r1 = (-2,3,0,0), r2(2,3,1,0)";
    cout << "\nExpected value of r0.intersectArea is 0. Actual value is : "<< r6.intersectArea(r7);
    cout << "\nExpected value of r5.unionArea is 16. Actual value is : " << r6.unionArea(r7);
    cout << "\nExpected value of r5.intersectArea is 0. Actual value is : "<< r6.intersectArea(r7,r8);
    cout << "\nExpected value of r5.unionArea is 16. Actual value is :" << r6.unionArea(r7,r8);
    return 0;
}
