#pragma once
#include <iostream>
#include <math.h>
#include "triangle.h"

namespace triangles {

extern const double eps;

class vector_t;


class point_t {
    double x_ = NAN, y_ = NAN, z_ = NAN;

public:
    point_t() {}
    point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}

    base_point get_coordinate() const;
    bool pt_linesegm_inters(const point_t &pt2, const point_t &pt3) const;
    bool isEq(const point_t &pt2) const;
    vector_t make_vector() const;    
    bool isValid() const;

    point_t operator = (const point_t &pt2);
    bool operator == (const point_t &pt2) const;
};


base_point point_t::get_coordinate() const
{
    return base_point{x_, y_, z_};
}

bool point_t::pt_linesegm_inters(const point_t &pt2, const point_t &pt3) const 
{
    if ( ( (pt2.x_ - x_) / (pt2.x_ - pt3.x_) - (pt2.y_ - y_) / (pt2.y_ - pt3.y_) ) < eps &&
        ( (pt2.x_ - x_) / (pt2.x_ - pt3.x_) - (pt2.z_ - z_) / (pt2.z_ - pt3.z_) ) < eps) {
        if ( (pt2.x_ - pt3.x_) < eps) {
            if ((pt2.y_ - y_) * (pt3.y_ - y_) < 0)
                return 1;
            else 
                return 0; 
        }
        else  {
            if ((pt2.x_ - x_) * (pt3.x_ - x_) < 0)
                return 1;
            else 
                return 0;  
        
        }
    }
    return 0;
}

bool point_t::isEq(const point_t &pt2) const
{
    return x_ == pt2.x_ && y_ == pt2.y_ && z_ == pt2.z_;
}

vector_t point_t::make_vector() const
{
    return vector_t{x_, y_, z_};
}

bool point_t::isValid() const
{
    if (x_ == x_ && y_ == y_ && z_ == z_)
        return 1;
    return 0;
}

point_t point_t::operator = (const point_t &pt2) 
{
    x_ = pt2.x_;
    y_ = pt2.y_;
    z_ = pt2.z_;

    return *this;
}

bool point_t::operator == (const point_t &pt2) const
{
    return ((x_ - pt2.x_) < eps) && ((y_ - pt2.y_) < eps) && ((z_ - pt2.z_) < eps);
}

};  //  namespace triangles

#include "vector_t.h"