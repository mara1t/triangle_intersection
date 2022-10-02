//#pragma once
#include <iostream>
//#include "point_t.h"
#include "plate_t.h"

//#include "line_t.h"


namespace triangles {

//class point_t;
//class plate_t;
//class line_t;

class triangle_t {

    point_t pt1_ = {NAN, NAN, NAN};
    point_t pt2_ = {NAN, NAN, NAN};
    point_t pt3_ = {NAN, NAN, NAN};

public:

    enum tr_type {
        POINT, LINE, TRI, NOT_DEF
    };
    enum inters_type {
        PT_PT, PT_LINE, PT_TRI, LINE_LINE, LINE_TRI, TRI_TRI, NOT_DEF_PAIR
    };

    tr_type type_;

    

    triangle_t() : type_{NOT_DEF} {}
    triangle_t(const point_t &pt1, const point_t &pt2, const point_t &pt3) 
        : pt1_{pt1}, pt2_{pt2}, pt3_{pt3} { define_type(); }

    void define_type();
    bool isLine() const;
    bool isPt() const;
    bool isValid() const;
    //bool pt_linesegm_inters(const point_t &pt1, const point_t &pt2, const point_t &pt3) const;

    inters_type find_cases (const triangle_t &trian2) const;
    bool pt_pt_inters(const triangle_t &trian2) const;
    bool pt_line_inters(const triangle_t &trian2) const;
    bool pt_tri_inters(const triangle_t &trian2);
    bool line_line_inters(const triangle_t &trian2) const;
    bool line_tri_inters(const triangle_t &trian2) const;
    bool tri_tri_inters(const triangle_t &trian2) const;

    bool SameSide(const point_t &p1, const point_t &p2, const point_t &a, const point_t &b);
    bool PointInTriangle(const point_t &p, const point_t &a, const point_t &b, const point_t &c);
}; 

void triangle_t::define_type()
{
    if (isPt()) {
        type_ = POINT;  
        return;  
    }
    if (isLine()) {
        type_ = LINE;
        return;
    }
    
    type_ = TRI;
}

bool triangle_t::isLine() const
{
    line_t tmp_line {pt1_, pt2_};

    if (tmp_line.onLine(pt3_)) 
        return 1;
    
    return 0;
}

bool triangle_t::isPt() const
{
    if (pt1_.isEq(pt2_) && pt2_.isEq(pt3_)) 
        return 1;
    
    return 0;
}

bool triangle_t::isValid() const
{
    if (pt1_.isValid() && pt2_.isValid() && pt3_.isValid()) 
        return 1;
    
    return 0;
}

/*
bool triangle_t::pt_linesegm_inters(const triangle_t &trian2) const 
{
    if ( ( (pt2.x_ - pt1.x_) / (pt2.x_ - pt3.x_) - (pt2.y_ - pt1.y_) / (pt2.y_ - pt3.y_) ) < eps &&
        ( (pt2.x_ - pt1.x_) / (pt2.x_ - pt3.x_) - (pt2.z_ - pt1.z_) / (pt2.z_ - pt3.z_) ) < eps) {
        if ( (pt2.x_ - pt3.x_) < eps) {
            if ()
        }
        else  {
            ( (pt2.x_ - pt1.x_) * 
        
        }
    }


}*/

triangle_t::inters_type triangle_t::find_cases(const triangle_t &trian2) const
{
    if (type_ == POINT && trian2.type_ == POINT)
        return PT_PT;

    if ((type_ == POINT && trian2.type_ == LINE) || (type_ == LINE && trian2.type_ == POINT))
        return PT_LINE;

    if ((type_ == POINT && trian2.type_ == TRI) || (type_ == TRI && trian2.type_ == POINT))
        return PT_TRI;

    if (type_ == LINE && trian2.type_ == LINE)
        return LINE_LINE;

    if ((type_ == LINE && trian2.type_ == TRI) || (type_ == TRI && trian2.type_ == LINE))
        return LINE_TRI;

    if (type_ == TRI && trian2.type_ == TRI)
        return TRI_TRI;

    else {
        return NOT_DEF_PAIR;
    }
}

bool triangle_t::pt_pt_inters(const triangle_t &trian2) const
{
    return pt1_ == trian2.pt1_;
}

bool triangle_t::pt_line_inters(const triangle_t &trian2) const
{
    if (type_ == POINT) {
        line_t tmp_line{trian2.pt1_, trian2.pt2_};
        if (tmp_line.onLine(pt1_)) {
            if (pt1_.pt_linesegm_inters(trian2.pt1_, trian2.pt2_) || pt1_.pt_linesegm_inters(trian2.pt1_, trian2.pt3_) ||
            pt1_.pt_linesegm_inters(trian2.pt2_, trian2.pt3_)) {
                return 1;
            }
        }
    }
    else if (type_ == LINE) {
        line_t tmp_line{pt1_, pt2_};
        if (tmp_line.onLine(trian2.pt1_)) {
            if (trian2.pt1_.pt_linesegm_inters(pt1_, pt2_) || trian2.pt1_.pt_linesegm_inters(pt1_, pt3_) ||
            trian2.pt1_.pt_linesegm_inters(pt2_, pt3_)) {
                return 1;
            }
        }
    }
    return 0;
    
}

bool triangle_t::pt_tri_inters(const triangle_t &trian2)
{
    if (type_ == POINT) {
        plate_t tri_plate{trian2.pt1_, trian2.pt2_, trian2.pt3_};

        if (std::abs(tri_plate.distance(pt1_)) < eps) {
            return PointInTriangle(pt1_, trian2.pt1_, trian2.pt2_, trian2.pt3_);
        }
    }
    else {
        plate_t tri_plate{pt1_, pt2_, pt3_};

        if (std::abs(tri_plate.distance(trian2.pt1_)) < eps) {
            return PointInTriangle(trian2.pt1_, pt1_, pt2_, pt3_);
        }
    }
    return 0;
    
}

bool triangle_t::line_line_inters(const triangle_t &trian2) const
{

}

bool triangle_t::line_tri_inters(const triangle_t &trian2) const
{

}

bool triangle_t::tri_tri_inters(const triangle_t &trian2) const
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

bool triangle_t::SameSide(const point_t &p1, const point_t &p2, const point_t &a, const point_t &b)
{
    vector_t vec_ab = b.make_vector() - a.make_vector();
    vector_t vec_p1a = p1.make_vector() - a.make_vector();
    vector_t vec_p2a = p2.make_vector() - a.make_vector();
    vector_t cp1 = vec_ab.vector_mul(vec_p1a);
    vector_t cp2 = vec_ab.vector_mul(vec_p2a);

    if (cp1.skalar_mul(cp2) >= 0) 
        return 1;
    
    return 0;
}

bool triangle_t::PointInTriangle(const point_t &p, const point_t &a, const point_t &b, const point_t &c)
{
    if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b))
        return 1;
    
    return 0;
}

};