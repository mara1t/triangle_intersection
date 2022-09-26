#pragma once
#include <cmath>
#include "point_t.h"

namespace triangles {

const double eps = 1e-6;

class vector_t {
    
    coordin_t coord{NAN, NAN, NAN};

public:

    vector_t () {}
    vector_t (double x, double y, double z) : coord{x, y, z} {}

    void copy(const vector_t &vec2) const;
    bool isPar(const vector_t &vec2) const;
    double skalar_mul(const vector_t &vec2) const;
    vector_t vector_t::vector_mul(const vector_t &vec2) const;
    double length() const;

    vector_t operator + (const vector_t &v2) const;
    vector_t operator - (const vector_t &v2) const;
    vector_t operator * (const double num) const;
};

void vector_t::copy(const vector_t &vec2) const
{
    coord.x = vec2.coord.x;
    coord.y = vec2.coord.y;
    coord.z = vec2.coord.z;
}

bool vector_t::isPar(const vector_t &vec2) const
{
    if (fabs((vector_mul(vec2)).length) < eps) {
        return 1;
    }
    return 0;
}

double vector_t::skalar_mul(const vector_t &vec) const
{
    return coord.x * vec.coord.x + coord.y * vec.coord.y + coord.z * vec.coord.z; 
}

vector_t vector_t::vector_mul(const vector_t &vec) const
{
    double x = coord.y * vec.coord.z - coord.z * vec.coord.y;
    double y = coord.z * vec.coord.x - coord.x * vec.coord.z;
    double z = coord.x * vec.coord.y - coord.y * vec.coord.x;

    vector_t res{x, y, z};
    return res;
}

double vector_t::length() const
{   
    return sqrt(coord.x * coord.x + coord.y * coord.y + coord.z * coord.z);
}

vector_t vector_t::operator + (const vector_t &v2) const
{
    return vector_t{coord.x + v2.coord.x, coord.y + v2.coord.y, coord.z + v2.coord.z};
}

vector_t vector_t::operator - (const vector_t &v2) const
{
    return vector_t{coord.x - v2.coord.x, coord.y - v2.coord.y, coord.z - v2.coord.z};
}

vector_t vector_t::operator * (const double num) const
{
    return vector_t{coord.x * num, coord.y * num, coord.z * num};
}

}; //  namespace triangles