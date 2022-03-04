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


int main(){
	Point A(2, 3);
	cout << A.getX() << " " << A.getY()<<'\n';
	Point B(1, 1);
	cout << pow(A.distanceToPoint(B), 2);
return 0;
}
