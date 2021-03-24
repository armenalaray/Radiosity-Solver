/* date = March 24th 2021 11:43 am */

#ifndef FACE_H
#define FACE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "matrix.h"
#include "quad.h"
#include "mapped_quad.h"

struct Mapping{
    Mapping(){};
    Mapping(const Mapped_quad_ur& ur_,
            const Mapped_quad_u& u_,
            const Mapped_quad_ul& ul_,
            const Mapped_quad_r& r_,
            const Mapped_quad_k& k_,
            const Mapped_quad_l& l_,
            const Mapped_quad_br& br_,
            const Mapped_quad_b& b_,
            const Mapped_quad_bl& bl_);
    Mapped_quad_ur ur;
    Mapped_quad_u u;
    Mapped_quad_ul ul;
    Mapped_quad_r r;
    Mapped_quad_k k; //k is self-pointer, it MUST be filled always!!!!
    Mapped_quad_l l;
    Mapped_quad_br br;
    Mapped_quad_b b;
    Mapped_quad_bl bl;
};

class Face{
    public:
    Face(ElemIndex ei, size_t i, size_t j):
    si{ei},
    f(i,j)
    {
        cm.reserve(i*j);
    }
    virtual void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b) = 0;
    protected:
    void generate_mapping();
    ElemIndex si;
    Matrix<std::shared_ptr<Quad>,2> f;
    public:
    std::unordered_map<std::shared_ptr<Quad>,Mapping> cm;
};

class Face_xy_z0:public Face{
    public:
    void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b)override;
    Face_xy_z0(float fw, int hps, ElemIndex& ei);
};

class Face_yz_x0:public Face{
    public:
    void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b)override;
    Face_yz_x0(float fw, int hps, ElemIndex& ei);
};

class Face_xz_y0:public Face{
    public:
    void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b)override;
    Face_xz_y0(float fw, int hps, ElemIndex& ei);
};

class Face_yz_x5:public Face{
    public:
    void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b)override;
    Face_yz_x5(float fw, int hps, ElemIndex& ei);
};

class Face_xz_y5:public Face{
    public:
    void add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b)override;
    Face_xz_y5(float fw, int hps, ElemIndex& ei);
};


#endif //FACE_H