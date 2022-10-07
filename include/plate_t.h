#pragma once
//#include "vector_t.h"
//#include "point_t.h"
#include "line_t.h"
#include <cmath>


namespace triangles {

//class vector_t;
//class point_t;

class plate_t {
    vector_t vec_ = {NAN, NAN, NAN};
    point_t pt_ = {NAN, NAN, NAN};

public:

    plate_t(const point_t &pt1, const point_t &pt2, const point_t &pt3);

    double distance(const point_t &pt) const;
};

plate_t::plate_t(const point_t &tmp_pt1, const point_t &tmp_pt2, const point_t &tmp_pt3)
{
    base_point pt1 = tmp_pt1.make_bs_pt();
    base_point pt2 = tmp_pt2.make_bs_pt();
    base_point pt3 = tmp_pt3.make_bs_pt();
    
    double A = pt1.y * (pt2.z - pt3.z) + pt2.y * (pt3.z - pt1.z) + pt3.y * (pt1.z - pt2.z);
    double B = pt1.z * (pt2.x - pt3.x) + pt2.z * (pt3.x - pt1.x) + pt3.z * (pt1.x - pt2.x);
    double C = pt1.x * (pt2.y - pt3.y) + pt2.x * (pt3.y - pt1.y) + pt3.x * (pt1.y - pt2.y);

    vec_ = vector_t{A, B, C};
    pt_ = tmp_pt1;
}

double plate_t::distance(const point_t &pt0) const
{
    
    vector_t vec_pt0pt = pt0.make_vector() - pt_.make_vector(); 
    double dist = vec_pt0pt.skalar_mul(vec_) / vec_.length();
    return fabs(dist);
}

};  //  namespace triangles