#ifndef TRIANGULE_HXX
#define TRIANGULE_HXX

#include "Basic.hh"

class Triangule : public Primitive
{
private:
  Vec3f	a, b, c;
  Vec3f	normal;
  bool PointInTriangle(Vec3f &pt, Ray &ray);

public:
	Triangule(Vec3f a, Vec3f b, Vec3f c, Shader *s);
	~Triangule() {};
  
   virtual Box CalcBounds()
   {
        Box bounds;
        
        bounds.Extend(a);
        bounds.Extend(b);
        bounds.Extend(c);

        return bounds;
   };

    virtual bool Intersect(Ray &ray)
    {
		//// the ray hit the backside of the triangle ..
		//// we count that as not hit
		//if( ray.dir.dot( GetNormal(ray) ) < 0 )
		//	return false;

        const Vec3f edge1 = b-a;
        const Vec3f edge2 = c-a;

        const Vec3f pvec = Cross(ray.dir,edge2);

        const float det = Dot(edge1, pvec);
        if (fabs(det) < Epsilon) return false;

        const float inv_det = 1.0f / det;

        const Vec3f tvec = ray.org-a;
        float lambda = Dot(tvec, pvec);
        lambda *= inv_det;

        if (lambda < 0.0f || lambda > 1.0f) return false;

        const Vec3f qvec = Cross(tvec,edge1);
        float mue = Dot(ray.dir, qvec);
        mue *= inv_det;

        if (mue < 0.0f || mue+lambda > 1.0f) return false;

        float f = Dot(edge2, qvec);
        f = f * inv_det;// - Epsilon;
		//f = f * inv_det + Epsilon;
        if (ray.t <= f || f < Epsilon  ) return false;

        ray.u = lambda;
        ray.v = mue;
        ray.t = f;
        ray.hit = this;

        return true;
    };

	//! Get triangle's normal
    virtual Vec3f GetNormal( Ray &ray )
    {
        Vec3f e1 = b - a;
        Vec3f e2 = c - a;
        Vec3f normal = Cross(e1,e2);
        Normalize(normal);
        return normal;
    };

    virtual void GetUV(const Ray &ray, float &u, float &v) const {
	//float alpha = 1 - ray.u - ray.v;
	//Vec3f interpolated(alpha * ray.getHitPoint(0) + ray.u * ray.getHitPoint(0) + ray.v * ray.getHitPoint(0));

	//Vec3f bar = ray.getHitPoint(0);

	//u = bar.x*u + bar.y*u + bar.z*u;
	//v = bar.x*v + bar.y*v + bar.z*v;
	u = ray.u;
	v = ray.v;	

	//u = interpolated.x;
	//v = interpolated.y;
    }
};

#endif








