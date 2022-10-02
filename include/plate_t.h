#pragma once
//#include "vector_t.h"
//#include "point_t.h"
#include "line_t.h"


namespace triangles {

//class vector_t;
//class point_t;

class plate_t {
    vector_t vec_ = {NAN, NAN, NAN};
    point_t pt = {NAN, NAN, NAN};

public:

    plate_t(const point_t &pt1, const point_t &pt2, const point_t &pt3);

    double distance(const point_t &pt) const;
};

plate_t::plate_t(const point_t &pt1, const point_t &pt2, const point_t &pt3)
{
    
}

double plate_t::distance(const point_t &pt0) const
{
    
    vector_t vec_pt0pt = pt0.make_vector() - pt.make_vector(); 
    double dist = vec_pt0pt.skalar_mul(vec_) / vec_.length();
    return dist;
}

};  //  namespace triangles