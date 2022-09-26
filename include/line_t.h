#pragma once
#include "vector_t.h"
#include "point_t.h"

namespace triangles {

struct line_base_t {
    vector_t vec;
    point_t pt;
};

class line_t {
    line_base_t line {{NAN, NAN, NAN}, {NAN, NAN, NAN}};

public:
    line_t() {}
    line_t(vector_t vec, point_t pt) : line{vec, pt} {}
    line_t(const point_t &pt1, const point_t &pt2);

    bool onLine(const point_t &pt1) const;
};

line_t::line_t(const point_t &pt1, const point_t &pt2)
{
    vector_t vec1 = pt1.make_vector();
    vector_t vec2 = pt2.make_vector();

    line.vec.copy(vec2 - vec1);
    line.pt = pt1;
}

bool line_t::onLine(const point_t &pt1) const
{       
    if (pt1 == line.pt) {
        return 1;
    }

    vector_t vec_pt1 = pt1.make_vector();
    vector_t vec_pt0 = line.pt.make_vector();

    if (line.vec.isPar(vec_pt1 - vec_pt0)) {
        return 1;
    }
    return 0;
}

};  //  namespace triangles