#pragma once
#include "vector_t.h"

namespace triangles {

struct coordin_t {
    double x, y, z;
};

class point_t {
    coordin_t coord {NAN, NAN, NAN};

public:
    point_t() {}
    point_t(double x, double y, double z) : coord{x, y, z} {}

    bool isEq(const point_t &pt2) const;
    vector_t make_vector() const;    
    bool isValid() const;

    point_t operator = (const point_t &pt2);
    bool operator == (const point_t &pt2) const;
};

bool point_t::isEq(const point_t &pt2) const
{
    return ((coord.x == pt2.coord.x) && (coord.y == pt2.coord.y) && (coord.z == pt2.coord.z));
}

vector_t point_t::make_vector() const
{
    return vector_t{coord.x, coord.y, coord.z};
}

bool point_t::isValid() const
{
    if (coord.x == coord.x && coord.y == coord.y && coord.z == coord.z)
        return 1;
    return 0;
}

point_t point_t::operator = (const point_t &pt2) 
{
    coord.x = pt2.coord.x;
    coord.y = pt2.coord.y;
    coord.z = pt2.coord.z;

    return *this;
}

bool point_t::operator == (const point_t &pt2) const
{
    return coord.x == pt2.coord.x && coord.y == pt2.coord.y && coord.z == pt2.coord.z;
}

};  //  namespace triangles