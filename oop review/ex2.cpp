#include <iostream>
#include <math.h>
using namespace std;


class Point
{
private:
    double x, y;

public:
    Point()
    {
         x=0;
         y=0;
         
    }

    Point(double x, double y)
    {
        
         this->x=x;
         this->y=y;
        
    }

    void setX(double x)
    {
         this->x=x;
         
    }

    void setY(double y)
    {
        this->y=y;
    }

    double getX() const
    {
        return x;
    }

    double getY() const
    {
       return y;
    }

    double distanceToPoint(const Point& pointA)
    {
         double result = sqrt(  pow( (this->getX() - pointA.getX()),2 ) + pow( (this->getY() - pointA.getY()),2)  );
         return result;
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*  
         * STUDENT ANSWER   
         * TODO: set zero center's x-y and radius
         */
         center.setX(0);
         center.setY(0);
         radius=0;
    }

    Circle(Point center, double radius)
    {
        /*  
         * STUDENT ANSWER
         */
         this->center=center; 
         this->radius=radius;
    }

    Circle(const Circle &circle)
    {
        /*  
         * STUDENT ANSWER
         */
         this->radius=circle.radius;
         this->center=circle.center;//
    }
    
    void setCenter(Point point)
    {
        /*  
         * STUDENT ANSWER
         */
         center.setX(point.getX());
         center.setY(point.getY());
    }

    void setRadius(double radius)
    {
        /*  
         * STUDENT ANSWER
         */
         this->radius=radius;
    }

    Point getCenter() const
    {
        /*  
         * STUDENT ANSWER
        */
         return center;
    }

    double getRadius() const
    {
        /*  
         * STUDENT ANSWER
         */
         return radius;
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};
int main(){
	Point B(2,2);
	Circle A;
	A.printCircle();
	cout<<'\n';
	A.setCenter(B);
	A.setRadius(1);
	Circle C(A);
	C.printCircle();
	/*
	Point A(2, 3);
	cout << A.getX() << " " << A.getY()<<'\n';
	Point B(1, 1);
	cout << pow(A.distanceToPoint(B), 2);
	*/
return 0;
}
