#pragma once

#include "vector_t.h"
//#include "point_t.h"

namespace triangles {

//class vector_t;
//class point_t;

class line_t {
    vector_t vec_{NAN, NAN, NAN};
    point_t pt_{NAN, NAN, NAN};

public:
    line_t() {}
    line_t(vector_t vec, point_t pt) : vec_{vec}, pt_{pt} {}
    line_t(const point_t &pt1, const point_t &pt2);

    bool onLine(const point_t &pt1) const;
};

line_t::line_t(const point_t &pt1, const point_t &pt2)
{
    vector_t vec1 = pt1.make_vector();
    vector_t vec2 = pt2.make_vector();

    vec_ = vec2 - vec1;
    pt_ = pt1;
}

bool line_t::onLine(const point_t &pt1) const
{       
    if (pt1 == pt_) {
        return 1;
    }

    vector_t vec_pt1 = pt1.make_vector();
    vector_t vec_pt0 = pt_.make_vector();

    if (vec_.isPar(vec_pt1 - vec_pt0)) {
        return 1;
    }
    return 0;
}

};  //  namespace triangles