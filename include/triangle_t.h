#pragma once
#include <iostream>
#include <cmath>
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

    tr_type type_;

    triangle_t() : type_{NOT_DEF} {}
    triangle_t(const point_t &pt1, const point_t &pt2, const point_t &pt3) 
        : pt1_{pt1}, pt2_{pt2}, pt3_{pt3} { define_type(); }

    void define_type();
    bool isLine() const;
    bool isPt() const;
    bool isValid() const;

    bool all_intersection(const triangle_t &trian2) const;
    bool pt_pt_inters(const triangle_t &trian2) const;
    bool pt_line_inters(const triangle_t &trian2) const;
    bool pt_tri_inters(const triangle_t &trian2) const;
    bool line_line_inters(const triangle_t &trian2) const;
    bool line_tri_inters(const triangle_t &trian2) const;
    bool tri_tri_inters(const triangle_t &trian2) const;

    bool SameSide(const point_t &p1, const point_t &p2, const point_t &a, const point_t &b) const;
    bool PointInTriangle(const point_t &p, const point_t &a, const point_t &b, const point_t &c) const;
    bool linesegm_inters(const point_t &tmp_pt1, const point_t &tmp_pt2, const point_t &tmp_pt3, const point_t &tmp_pt4) const;
    bool linesegm_tri_inters(const point_t &A, const point_t &B, const point_t &C, const point_t &X, const point_t &Y) const;
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

bool triangle_t::all_intersection(const triangle_t &trian2) const
{
    if (type_ == POINT && trian2.type_ == POINT)
        return pt_pt_inters(trian2);

    if ((type_ == POINT && trian2.type_ == LINE) || (type_ == LINE && trian2.type_ == POINT))
        return pt_line_inters(trian2);

    if ((type_ == POINT && trian2.type_ == TRI) || (type_ == TRI && trian2.type_ == POINT))
        return pt_tri_inters(trian2);

    if (type_ == LINE && trian2.type_ == LINE)
        return line_line_inters(trian2);

    if ((type_ == LINE && trian2.type_ == TRI) || (type_ == TRI && trian2.type_ == LINE))
        return line_tri_inters(trian2);

    if (type_ == TRI && trian2.type_ == TRI)
        return tri_tri_inters(trian2);

    return 0;
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

bool triangle_t::pt_tri_inters(const triangle_t &trian2) const
{
    if (type_ == POINT) {
        plate_t tri_plate{trian2.pt1_, trian2.pt2_, trian2.pt3_};

        if (fabs(tri_plate.distance(pt1_)) < eps) {
            return PointInTriangle(pt1_, trian2.pt1_, trian2.pt2_, trian2.pt3_);
        }
    }
    else {
        plate_t tri_plate{pt1_, pt2_, pt3_};

        if (fabs(tri_plate.distance(trian2.pt1_)) < eps) {
            return PointInTriangle(trian2.pt1_, pt1_, pt2_, pt3_);
        }
    }
    return 0;
    
}

bool triangle_t::line_line_inters(const triangle_t &trian2) const
{
    if (trian2.pt1_ == trian2.pt2_) {
        plate_t tmp_plate {trian2.pt1_, trian2.pt3_, pt1_};
        if (pt1_ == pt2_) {
            if (fabs(tmp_plate.distance(pt3_)) < eps) {
                return linesegm_inters(pt1_, pt3_, trian2.pt1_, trian2.pt3_);
            }
        }
        else {
            if (fabs(tmp_plate.distance(pt2_)) < eps) {
                return linesegm_inters(pt1_, pt2_, trian2.pt1_, trian2.pt3_);
            }
        }
    }
    else {
        plate_t tmp_plate {trian2.pt1_, trian2.pt2_, pt1_};
        if (pt1_ == pt2_) {
            if (fabs(tmp_plate.distance(pt3_)) < eps) {
                return linesegm_inters(pt1_, pt3_, trian2.pt1_, trian2.pt2_);
            }
        }
        else {
            if (fabs(tmp_plate.distance(pt3_)) < eps) {
                return linesegm_inters(pt1_, pt2_, trian2.pt1_, trian2.pt2_);
            }
        }
    }
    return 0;
}

bool triangle_t::line_tri_inters(const triangle_t &trian2) const
{
    if (type_ == LINE) {
        if (pt1_ == pt2_) {
            return linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt3_); 
        }
        else {
            return linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt2_); 
        }
    }   
    else {
        if (trian2.pt1_ == trian2.pt2_) {
            return linesegm_tri_inters(trian2.pt1_, trian2.pt3_, trian2.pt3_, pt1_, pt3_); 
        }
        else {
            return linesegm_tri_inters(trian2.pt1_, trian2.pt3_, trian2.pt3_, pt1_, pt2_); 
        }
    }
}

bool triangle_t::tri_tri_inters(const triangle_t &trian2) const
{   
    if (linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt1_, trian2.pt2_)        || 
        linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt1_, trian2.pt3_)        || 
        linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt3_, trian2.pt2_)        || 
        linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt2_) || 
        linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt3_) || 
        linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt3_, pt2_)) 
        return 1;
    /*
    if (linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt1_, trian2.pt2_)) {
        return 1;
    } 
    if (linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt1_, trian2.pt3_)) {
        return 1;
    }    
    if (linesegm_tri_inters(pt1_, pt2_, pt3_, trian2.pt3_, trian2.pt2_)) {
        return 1;
    } 
    if (linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt2_)) {
        return 1;
    } 
    if (linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt1_, pt3_)) {
        return 1;
    } 
    if (linesegm_tri_inters(trian2.pt1_, trian2.pt2_, trian2.pt3_, pt3_, pt2_)) {
        return 1;
    }   
    */
    return 0;
}

bool triangle_t::SameSide(const point_t &p1, const point_t &p2, const point_t &a, const point_t &b) const
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

bool triangle_t::PointInTriangle(const point_t &p, const point_t &a, const point_t &b, const point_t &c) const
{
    if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b))
        return 1;
    
    return 0;
}

bool triangle_t::linesegm_inters(const point_t &tmp_pt1, const point_t &tmp_pt2, const point_t &tmp_pt3, const point_t &tmp_pt4) const
{
    
    vector_t da = tmp_pt2.make_vector() - tmp_pt1.make_vector(); 
    vector_t db = tmp_pt4.make_vector() - tmp_pt3.make_vector();
    vector_t dc = tmp_pt3.make_vector() - tmp_pt1.make_vector();

    if ((da.vector_mul(db)).length() < eps) { // parallel
        line_t line12{da, tmp_pt1};
        if (line12.onLine(tmp_pt3)) {
            vector_t d13 = tmp_pt3.make_vector() - tmp_pt1.make_vector(); 
            vector_t d14 = tmp_pt4.make_vector() - tmp_pt1.make_vector();
            vector_t d23 = tmp_pt3.make_vector() - tmp_pt2.make_vector(); 
            vector_t d24 = tmp_pt4.make_vector() - tmp_pt2.make_vector();
            if (d13.length() < eps || d14.length() < eps || 
            d23.length() < eps || d24.length() < eps) {
                return 1;
            }
            if (d13.skalar_mul(d14) > 0 && d23.skalar_mul(d24) > 0 && d13.skalar_mul(d23) > 0 && d13.skalar_mul(d14) > 0) {
                return 0;
            }
        }
        return 0;
    }

    if (fabs(dc.skalar_mul(da.vector_mul(db))) > eps) // lines are not coplanar
        return 0;

    vector_t d1 = dc.vector_mul(db);
    vector_t d2 = da.vector_mul(db);
    vector_t d3 = dc.vector_mul(da);
    
    double d1d2 = d1.skalar_mul(d2);
 
    double s = (dc.vector_mul(db)).skalar_mul(da.vector_mul(db)) / (da.skalar_mul(db) * da.skalar_mul(db));

    double t = (dc.vector_mul(da)).skalar_mul(da.vector_mul(db)) / (da.skalar_mul(db) * da.skalar_mul(db));

    if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0) {
        return 1;
    }

    return 0;
}

bool triangle_t::linesegm_tri_inters(const point_t &A, const point_t &B, const point_t &C, const point_t &X, const point_t &Y) const
{
    
    vector_t AB = B.make_vector() - A.make_vector();
    vector_t AC = C.make_vector() - A.make_vector();
    vector_t N =  AB.vector_mul(AC);
    N.normalize();
    vector_t W = Y.make_vector() - X.make_vector();
    
    if (N.skalar_mul(W) < eps) {
        plate_t tmp_tri_plate{A, B, C};

        if (tmp_tri_plate.distance(X) > eps)
            return 0;

        if (linesegm_inters(X, Y, A, B) || linesegm_inters(X, Y, A, C) || linesegm_inters(X, Y, C, B))
            return 1;
    }

    vector_t V = A.make_vector() - X.make_vector();
    
    double d =  N.skalar_mul(V);
    
    
    double e =  N.skalar_mul(W);
    
    if (fabs(e) < eps) {
        base_point baseX = X.make_bs_pt();
        base_point baseY = Y.make_bs_pt();
        base_point baseW = W.make_bs_vec();
        
        point_t inters_pt{baseX.x  +  baseW.x * d/e, baseX.y  +  baseW.y * d/e, baseX.z  +  baseW.z * d/e};

        if (PointInTriangle(inters_pt, A, B, C)) {
            vector_t OX = X.make_vector() - inters_pt.make_vector();
            vector_t OY = Y.make_vector() - inters_pt.make_vector();
            if (OX.length() < eps || OY.length() < eps || OX.skalar_mul(OY) < 0) {
                return 1;
            }
        }

        return 0;
    }
    return 0;
}



};