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
	
	
    bool containsPoint(const Point point)
    {
        /*  
         * STUDENT ANSWER 
         * TODO: check if a given point is entirely within the circle (does not count if the point lies on the circle).  
                 If contain, return true.
         */
         double a= pow(center.getX()-point.getX(),2)+pow(center.getY()-point.getY(),2);
         if (a<pow(radius,2)){
         	return true;
		 }
		 return false;
    }

    bool containsTriangle(const Point pointA, const Point pointB, const Point pointC)
    {
        /*  
         * STUDENT ANSWER   
         * TODO: check if a given triangle ABC (A, B, C are not on the same line) is entirely within the circle (does not count if any point of the triangle lies on the circle).  
                 If contain, return true.
         */
         if((pointA.getX()==pointB.getX()&&pointA.getX()==pointC.getX())||(pointA.getY()==pointB.getY()&&pointA.getY()==pointC.getY())){
         	return false;
		 }
         if(this->containsPoint(pointA)&&this->containsPoint(pointB)&&this->containsPoint(pointC)){
         	return true;
		 }
		return false;
    }
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main(){
	/*
	Point pointO(0, 2);
	Point point1(1, 2);
	Circle A = Circle(pointO, 2);
	cout << A.containsPoint(point1);
	*/
	Point pointO(1, 1);
//	Point point1(1, 0), point2(-1, 0), point3(0, 3);
	Circle A = Circle(pointO, 3);
	A.printCircle();
//	cout << A.containsTriangle(point1, point2, point3);
	
return 0;
}
