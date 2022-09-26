#pragma once
#include "point_t.h"

#include "line_t.h"

namespace triangles {


struct triangle_base_t {
    point_t pt1, pt2, pt3;
};

class triangle_t {
    
    enum tr_type {
        POINT, LINE, TRI, NOT_DEF
    };
    enum inters_type {
        PT_PT, PT_LINE, PT_TRI, LINE_LINE, LINE_TRI, TRI_TRI, NOT_DEF_PAIR
    };

    tr_type type;

    triangle_base_t triangle{{NAN, NAN, NAN}, {NAN, NAN, NAN}, {NAN, NAN, NAN}};

    triangle_t() : type{NOT_DEF} {}
    triangle_t(const point_t &pt1, const point_t &pt2, const point_t &pt3) 
        : triangle{pt1, pt2, pt3} {}

    void define_type();
    bool isLine() const;
    bool isPt() const;
    bool isValid() const;

    triangle_t::inters_type find_cases (const triangle_t &trian2) const;
    int intersection3D(const triangle_t&);
}; 

void triangle_t::define_type()
{
    if (isPt()) {
        type = POINT;  
        return;  
    }
    if (isLine()) {
        type = LINE;
        return;
    }
    


}

bool triangle_t::isLine() const
{
    line_t tmp_line {triangle.pt1, triangle.pt2};
    if (tmp_line.onLine(triangle.pt3)) 
        return 1;
    
    return 0;
}

bool triangle_t::isPt() const
{
    if (triangle.pt1.isEq(triangle.pt2) && triangle.pt2.isEq(triangle.pt3)) 
        return 1;
    
    return 0;
}

bool triangle_t::isValid() const
{
    if (triangle.pt1.isValid() && triangle.pt2.isValid() && triangle.pt3.isValid()) 
        return 1;
    
    return 0;
}

triangle_t::inters_type triangle_t::find_cases(const triangle_t &trian2) const
{
    if (type == POINT && trian2.type == POINT)
        return PT_PT;

    if ((type == POINT && trian2.type == LINE) || (type == LINE && trian2.type == POINT))
        return PT_LINE;

    if ((type == POINT && trian2.type == TRI) || (type == TRI && trian2.type == POINT))
        return PT_TRI;

    if (type == LINE && trian2.type == LINE)
        return LINE_LINE;

    if ((type == LINE && trian2.type == TRI) || (type == TRI && trian2.type == LINE))
        return LINE_TRI;

    if (type == TRI && trian2.type == TRI)
        return TRI_TRI;

    else {
        return NOT_DEF_PAIR;
    }
}

int triangle_t::intersection3D(const triangle_t &trian2)
{   
    /*type tr1_type = tr_type;
    type tr2_type = tr2.tr_type;
    
    switch (tr1_type) {
        case POINT:
        case LINE:
        case TRI:
        case NOT_DEF:

    };
*/
    return 0;
}

};