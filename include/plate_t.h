#pragma once
#include "vector_t.h"
#include "point_t.h"


namespace triangles {
    
struct plate_base_t {
    vector_t norm;
    point_t pl_pt;
};

class plate_t {
    plate_base_t plate {{NAN, NAN, NAN}, NAN};
public:
    plate_t(const point_t &pt1, const point_t &pt2, const point_t &pt3);
};

};  //  namespace triangles