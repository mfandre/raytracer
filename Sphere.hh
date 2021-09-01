#ifndef SPHERE_HH
#define SPHERE_HH

#include "Basic.hh"

class Sphere : public Primitive
{
public:
  Vec3f center;
  float radius;
  
  Sphere(Vec3f center, float radius, Shader *shader)
    : center(center), radius(radius), Primitive(shader)
  {};
  
  ~Sphere() {};
  
    virtual bool Intersect(Ray &ray);
    
    virtual Vec3f GetNormal(Ray &ray);
    
    virtual Box CalcBounds()
    {
        // sphere's bounding box is computed based on the radius of the sphere
        Box b = Box();
        b.Extend(center + Vec3f(-radius,-radius,-radius));
        b.Extend(center + Vec3f(radius,radius,radius));
        return b;
    };

    virtual void GetUV(const Ray &ray, float &u, float &v) const {
	u = ray.u;
	v = ray.v;
    }
};

#endif




