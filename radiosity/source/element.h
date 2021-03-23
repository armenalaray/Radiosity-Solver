/* date = March 20th 2021 2:51 pm */

#ifndef ELEMENT_H
#define ELEMENT_H

#if defined(_MSC_VER)
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#endif

#include "vec3.h"
#include "ray.h"
#include "matrix.h"
#include "hemi_cube.h"

using ElemIndex = typename int;
enum class corner_it : int {tf=0,rf=1,lf=2,ff=3,bf=4,corner_index_count=5};

class Element;

struct Element_impl{
    Element_impl(){}
    Element_impl(const Vec3<float>& n,const Vec3<float>& p);
    Vec3<float> u;
    Vec3<float> v;
    Vec3<float> w;
    int corner_i;
    Vec3<float> corners[corner_it::corner_index_count];
    HemiCube hm;
};


class Element_ref{
    public:
    /* 
    DO NOT have implementation
     */
    Element_ref& operator=(const Element& e);
    Vec3<float> n;
    Vec3<float> p;
    ElemIndex i;
};

class Element{
    public:
    
    Element(const Vec3<float>& n, const Vec3<float>& p, const ElemIndex i);
    
    Element()=delete;
    Element(const Element&)=delete;
    Element& operator=(const Element&)=delete;
    Element(Element&&)=delete;
    Element& operator=(Element&&)=delete;
    
    bool get_ray(Ray& r);
    void calc_ff(const Ray& r, const Element_ref& j, Matrix<float,2>& ffm);
    ElemIndex get_index()const{return i;}
    
    Vec3<float> get_n()const{return n;}
    Vec3<float> get_p()const{return p;}
    ElemIndex get_i()const{return i;}
    private:
    Vec3<float> n;
    Vec3<float> p;
    ElemIndex i;
    Element_impl impl;
};


#endif //ELEMENT_H
