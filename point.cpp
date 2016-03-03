//
//  point.cpp
//  PA2
//

#include "Point.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

namespace Clustering
{
    
unsigned int Point::__idGen = 0;

Point::Point (int num) //constructor
{
    
    __id = __idGen++;
    __dim = num;
    __values = new double[num];
    
    for (int i = 0; i < num; i++)
    {
        __values[i] = 0;
    }
    
}

Point::Point (int num, double *newVal)
{

    __id = __idGen++;
    __dim = num;
    __values = new double[__dim];


}

//copy constructor
Point::Point(const Point &p)
{
    __dim = p.__dim;
    __id = p.__id;
    __values = new double[__dim];
    
    for (int i = 0; i < __dim ; i++)
    {
        __values[i] = p.__values[i];
    }
}

//overloaded operator=
Point &Point::operator=(const Point &p)
{
    if (this == &p)
    {
        return *this;
    }
    else
    {
        __id = p.__id;
        __dim = p.__dim;
        
        if(__values != nullptr)
            delete [] __values;
        
        __values = new double[__dim];
        
        for (int i = 0; i < __dim; i++)
        {
                __values[i] = p.__values[i];
        }
        
        return *this;
        
    }
    

}

//destructor
Point::~Point()
{
    if (__values != nullptr)
        delete [] __values;
    
}

// Accessors & mutators
int Point::getId() const
{
    return __id;
}
int Point::getDims() const
{
    return __dim ;
}
void Point::setValue(int i, double n)
{
    __values[i] = n;
}
double Point::getValue(int i) const
{
    return __values[i];
}

//functions
double Point::distanceTo(const Point &point) const
{
    double dist = 0;
    
    for(int i = 0; i < __dim; i++)
    {
        dist += pow((__values[i] - point.getValue(i)),2);
    }
    
    return sqrt(dist);
}

//overload operator
Point &Point::operator*=(double n)
{
    for (int i = 0; i < __dim; ++i)
    {
        __values[i] *= n;
    }
    
    return *this;
    
}

Point &Point::operator/=(double n)
{
    for (int i = 0; i < __dim; ++i)
        __values[i] /= n;
    
    return *this;
}

const Point Point::operator*(double n) const
{
    Point p(*this);
    p *= n;
    return p;
}

const Point Point::operator/(double n) const
{
    Point p(*this);
    p /= n;
    
    return p;
}

double &Point::operator[](int index)
{

    return __values[index];
}

// Friends
Point &operator+=(Point &lhs, const Point &rhs)
{
    
    for (int i = 0; i < lhs.getDims(); i++)
    {
        lhs.__values[i] += rhs.__values[i];
    }
    
    return lhs;
    
}

Point &operator-=(Point &lhs, const Point &rhs)
{
    for(int i = 0; i < lhs.getDims(); i++)
    {
        lhs.__values[i] -= rhs.__values[i];
    }
    
    return lhs;
}

const Point operator+(const Point &lhs, const Point &rhs)
{
    Point p(lhs);
    p += rhs;
    return p;
}

const Point operator-(const Point &lhs, const Point &rhs)
{
    Point p(lhs);
    p -= rhs;
    return p;
}

bool operator==(const Point &lhs, const Point &rhs)
{
    if (lhs.__id != rhs.__id)
        return false;
    bool isEqual = true;
    for (int i = 0; i < lhs.__dim; i++)
    {
        if (lhs.__values[i] != rhs.__values[i])
        {
            isEqual = false;
        }
    }
    return isEqual;
}
bool operator!=(const Point &lhs, const Point &rhs)
{
    
    return !(lhs==rhs);
}

bool operator<(const Point &lhs, const Point &rhs) {
    /*bool isLess = true;
    for (int i = 0; i < lhs.__dim; i++)
    {
        if (lhs.__values[i] < rhs.__values[i])
           return true;
        if(lhs.__values[i]>rhs.__values[i])
            return false;
    }
    return isLess;
     */

    int usedDims = std::max(lhs.__dim, rhs.__dim);

    for (int i = 0; i < usedDims; ++i) {
        if (lhs.getValue(i) != rhs.getValue(i))
        {
            return (lhs.getValue(i) < rhs.getValue(i));
        }
    }


    return false;

}

bool operator>(const Point &lhs, const Point &rhs)
{

    /*
    bool isMore = true;
    for (int i = 0; i < lhs.__dim; i++)
    {
        if (lhs.__values[i] > rhs.__values[i])
            return true;
        if (lhs.__values[i] < rhs.__values[i])
            return false;
    }
    
    return isMore;
     */
    return (rhs < lhs);
}


bool operator<=(const Point &lhs, const Point &rhs)
{
    /*
    if (lhs > rhs)
        return false;
    else
        return true;
        */
    return !(lhs > rhs);
}

bool operator>=(const Point &lhs, const Point &rhs)
{
    /*
    if (lhs < rhs)
        return true;
    else
        return false;
        */
    return !(lhs<rhs);
}

    std::ostream &operator<<(std::ostream &out, const Point &p)
    {
        int i = 0;
        for ( ; i < p.__dim - 1; ++i)
            out << p.__values[i] << ", ";
        
        out << p.__values[i];
        
        return out;
    }

std::istream &operator>>(std::istream &is, Point &p)
{
    
    double d;
    std::string line;
    for(int i=0;i<p.__dim;i++)
    {
        is>>line;
        std::stringstream is(line);
        is>>d;
        p.__values[i] = d;
    }
    return is;
}
    
}



