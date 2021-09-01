#ifndef INFINITEPLANE_HXX
#define INFINITEPLANE_HXX

#include "Basic.hh"
#include "stdio.h"
class InfinitePlane : public Primitive
{
public:
  Vec3f origin, normal;
  
  InfinitePlane(Vec3f origin, Vec3f normal, Shader *shader)
    : origin(origin), normal(normal), Primitive(shader)
  {
    Normalize(normal);
  };
  
  ~InfinitePlane() {};


   virtual Box CalcBounds()
   {
	// return box of 0 dimension.
        Box b = Box();
        b.Extend(Vec3f(0,0,0));
        return b;
   };
 
	
virtual bool Intersect(Ray &ray)
{
    Vec3f diff = origin - ray.org;
    float t = Dot(diff,normal) / Dot(ray.dir,normal);
    if (t < Epsilon || t > ray.t) return false;
    ray.t = t;
    return true;
};

virtual Vec3f GetNormal(Ray &ray)
{
  return normal;
}

};


#endif


