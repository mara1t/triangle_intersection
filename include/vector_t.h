#pragma once
#include <cmath>
#include <cassert>
#include "triangle.h"

namespace triangles {

const double eps = 1e-6;

//class point_t;



class vector_t {
    
    double x_ = NAN, y_ = NAN, z_ = NAN;

public:

    vector_t () {}
    vector_t (double x, double y, double z) : x_{x}, y_{y}, z_{z} {}

    bool isPar(const vector_t &vec2) const;
    double skalar_mul(const vector_t &vec2) const;
    vector_t vector_mul(const vector_t &vec2) const;
    double length() const;
    void normalize();
    base_point make_bs_vec() const;

    vector_t operator + (const vector_t &v2) const;
    vector_t operator - (const vector_t &v2) const;
    vector_t operator * (const double num) const;
};


bool vector_t::isPar(const vector_t &vec2) const
{
    vector_t tmp_vec = vector_mul(vec2);
    if ((tmp_vec.length()) < eps) {
        return 1;
    }
    return 0;
}

double vector_t::skalar_mul(const vector_t &vec) const
{
    return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_; 
}

vector_t vector_t::vector_mul(const vector_t &vec) const
{
    double x = y_ * vec.z_ - z_ * vec.y_;
    double y = z_ * vec.x_ - x_ * vec.z_;
    double z = x_ * vec.y_ - y_ * vec.x_;

    vector_t res{x, y, z};

    return res;
}

double vector_t::length() const
{   
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

void vector_t::normalize()
{
    double len = length();
    assert(len > eps);
    x_ /= len;
    y_ /= len;
    z_ /= len;
}

base_point vector_t::make_bs_vec() const
{
    return base_point{x_, y_, z_};
}

vector_t vector_t::operator + (const vector_t &v2) const
{
    return vector_t{x_ + v2.x_, y_ + v2.y_, z_ + v2.z_};
}

vector_t vector_t::operator - (const vector_t &v2) const
{
    return vector_t{x_ - v2.x_, y_ - v2.y_, z_ - v2.z_};
}

vector_t vector_t::operator * (const double num) const
{
    return vector_t{x_ * num, y_ * num, z_ * num};
}

}; //  namespace triangles