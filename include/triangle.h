#pragma once

namespace triangles {
struct base_point {
    double x, y, z;
};
struct base_line {
    base_point vec;
    base_point pt;
};

};