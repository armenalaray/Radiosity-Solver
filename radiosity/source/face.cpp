#include "face.h"

Mapping::Mapping(const Mapped_quad_ur& ur_,
                 const Mapped_quad_u& u_,
                 const Mapped_quad_ul& ul_,
                 const Mapped_quad_r& r_,
                 const Mapped_quad_k& k_,
                 const Mapped_quad_l& l_,
                 const Mapped_quad_br& br_,
                 const Mapped_quad_b& b_,
                 const Mapped_quad_bl& bl_):
ur{ur_},
u{u_},
ul{ul_},
r{r_},
k{k_},
l{l_},
br{br_},
b{b_},
bl{bl_}
{}

void Face::generate_mapping(){
    
    for(auto i=0; i<f.get_extent(0);++i){
        for(auto j=0; j<f.get_extent(1);++j){
            
            Mapped_quad_ur ur{};
            Mapped_quad_u u{};
            Mapped_quad_ul ul{};
            Mapped_quad_r r{};
            Mapped_quad_k k{};
            Mapped_quad_l l{};
            Mapped_quad_br br{};
            Mapped_quad_b b{};
            Mapped_quad_bl bl{};
            
            if(i+1<f.get_extent(0))
            {
                if(j+1<f.get_extent(1))
                    ur = {f(i+1,j+1)};
                
                u = {f(i+1,j)};
                
                if(j-1>=0)
                    ul = {f(i+1,j-1)};
            }
            
            if(j+1<f.get_extent(1))
                r = {f(i,j+1)};
            
            k = {f(i,j)};
            
            if(j-1>=0)
                l = {f(i,j-1)};
            
            if(i-1>=0){
                if(j+1<f.get_extent(1))
                    br = {f(i-1,j+1)};
                
                b = {f(i-1,j)};
                
                if(j-1>=0)
                    bl = {f(i-1,j-1)};
            }
            
            cm[f(i,j)] = Mapping
            {
                ur,
                u,
                ul,
                r,
                k,
                l,
                br,
                b,
                bl
            };
        }
    }
}

Face_xy_z0::Face_xy_z0(float fw, int hps, ElemIndex& ei):
Face(ei,hps,hps)
{
    float s = fw / float(hps);
    float z = 0.f;
    float y0 = 0.f;
    float y1 = y0 + s;
    for (size_t i = 0; i < hps ; i += 1, y0 += s, y1 += s){
        float x0 = 0.f;
        float x1 = x0 + s; 
        for (size_t j = 0; j < hps; j += 1, x0 += s, x1 += s, ei += 1){
            Vec3<float> p{x0+0.5f*x1,y0+0.5f*y1,z};
            f(i,j) = std::make_shared<Quad_XY_Z0>(p, ei, x0,x1,y0,y1,z);
        }
    }
    generate_mapping();
}


Face_yz_x0::Face_yz_x0(float fw, int hps, ElemIndex& ei):
Face(ei,hps,hps)
{
    float s = fw / float(hps);
    float x = 0.0f;
    float y0 = 0;
    float y1 = y0 + s;
    for (size_t i = 0; i < hps ; i += 1, y0 += s, y1 += s){
        float z0 = 0; 
        float z1 = z0 + s; 
        for (size_t j = 0; j < hps; j += 1, z0 += s, z1 += s, ei += 1){
            Vec3<float> p{x, y0+0.5f*y1,z0+0.5f*z1};
            f(i,j) = std::make_shared<Quad_YZ_X0>(p, ei, y0,y1,z0,z1,x);
        }
    }
    generate_mapping();
}


Face_xz_y0::Face_xz_y0(float fw, int hps, ElemIndex& ei):
Face(ei,hps,hps)
{
    float s = fw / float(hps);
    float y = 0.0f;
    float z0 = 0;
    float z1 = z0 + s;
    for (size_t i = 0; i < hps ; i += 1, z0 += s, z1 += s){
        float x0 = 0; 
        float x1 = x0 + s; 
        for (size_t j = 0; j < hps; j += 1, x0 += s, x1 += s, ei += 1){
            Vec3<float> p{x0+0.5f*x1, y,z0+0.5f*z1};
            f(i,j) = std::make_shared<Quad_XZ_Y0>(p, ei, x0,x1,z0,z1,y);
        }
    }
    generate_mapping();
}


Face_yz_x5::Face_yz_x5(float fw, int hps, ElemIndex& ei):
Face(ei,hps,hps)
{
    float s = fw / float(hps);
    float x = fw;
    float y0 = 0;
    float y1 = y0 + s;
    for (size_t i = 0; i < hps ; i += 1, y0 += s, y1 += s){
        float z0 = 0; 
        float z1 = z0 + s; 
        for (size_t j = 0; j < hps; j += 1, z0 += s, z1 += s, ei += 1){
            Vec3<float> p{x, y0+0.5f*y1,z0+0.5f*z1};
            f(i,j) = std::make_shared<Quad_YZ_X5>(p, ei, y0,y1,z0,z1,x);
        }
    }
    generate_mapping();
}


Face_xz_y5::Face_xz_y5(float fw, int hps, ElemIndex& ei):
Face(ei,hps,hps)
{
    float s = fw / float(hps);
    float y = fw;
    float z0 = 0;
    float z1 = z0 + s;
    for (size_t i = 0; i < hps ; i += 1, z0 += s, z1 += s){
        float x0 = 0; 
        float x1 = x0 + s; 
        for (size_t j = 0; j < hps; j += 1, x0 += s, x1 += s, ei += 1){
            Vec3<float> p{x0+0.5f*x1, y,z0+0.5f*z1};
            f(i,j) = std::make_shared<Quad_XZ_Y5>(p, ei, x0,x1,z0,z1,y);
        }
    }
    generate_mapping();
}

void Face_xy_z0::add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    ElemIndex i=si;
    for(auto a:cm){
        auto mapping=a.second;
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.u.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ul.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.r.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.l.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.br.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.b.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.bl.add_color(Color<float>{r(i),g(i),b(i)});
        ++i;
    }
}

void Face_yz_x0::add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    ElemIndex i=si;
    for(auto a:cm){
        auto mapping=a.second;
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.u.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ul.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.r.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.l.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.br.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.b.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.bl.add_color(Color<float>{r(i),g(i),b(i)});
        ++i;
    }
}

void Face_xz_y0::add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    ElemIndex i=si;
    for(auto a:cm){
        auto mapping=a.second;
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.u.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ul.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.r.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.l.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.br.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.b.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.bl.add_color(Color<float>{r(i),g(i),b(i)});
        ++i;
    }
}

void Face_yz_x5::add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    ElemIndex i=si;
    for(auto a:cm){
        auto mapping=a.second;
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.u.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ul.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.r.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.l.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.br.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.b.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.bl.add_color(Color<float>{r(i),g(i),b(i)});
        ++i;
    }
}

void Face_xz_y5::add_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    ElemIndex i=si;
    for(auto a:cm){
        auto mapping=a.second;
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ur.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.u.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.ul.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.r.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.l.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.br.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.b.add_color(Color<float>{r(i),g(i),b(i)});
        mapping.bl.add_color(Color<float>{r(i),g(i),b(i)});
        ++i;
    }
}