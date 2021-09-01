#ifndef BASIC_HH
#define BASIC_HH

#include "Vec3f.hh"
#include <vector> 
using namespace std;

class Primitive;
class Light;

class Ray
{
public:
  Vec3f org, dir;
  float t;
  Primitive *hit;
  float u, v;
  int maxBounce;
  float contribution;
  int xCoord,yCoord;

  Ray(): hit(NULL)
  {
    t = Infinity;
    contribution = 1.0f;
    maxBounce = 3;
    xCoord = 0;
    yCoord = 0;
  };

  Ray(Vec3f org, Vec3f dir, float t)
    : org(org), dir(dir), t(t), hit(NULL),maxBounce(3), contribution(1.0f)
  {};
  
  ~Ray()
  {};

  Vec3f getHitPoint(float eps) const {
	return org + (t+eps) * dir;
  }
};






class Box
{
public:
	Vec3f min,max;

	Box() 
	{ 
		Clear(); 
	};

    Box(const Box& b)
    {
        min = b.min;
        max = b.max;
    }

	inline void Extend(Vec3f a)
	{ 
		min = Min(a,min); 
		max = Max(a,max); 
	}

	inline void Clear()
	{ 
		min = Vec3f(Infinity,Infinity,Infinity); 
		max = Vec3f(-Infinity,-Infinity,-Infinity); 
	}

	inline void Extend(Box box)
	{
		Extend(box.min);
		Extend(box.max);
	}

	inline float getSurfaceArea()
	{
		float xDim = max[0] - min[0];
		float yDim = max[1] - min[1];
		float zDim = max[2] - min[2];

		return 2* (xDim*yDim + yDim*zDim + zDim*xDim);
	}

	//retorna (infinito, -infinito) caso nao haja intersecao
	bool Intersect(const Ray &ray) const
	{
		float d0 = -Infinity, d1 = Infinity;

		if(fabs(ray.dir.x) > Epsilon)
		{
			d0 = (min.x - ray.org.x) / ray.dir.x;
			d1 = (max.x - ray.org.x) / ray.dir.x;
			if(d1 < d0)
				std::swap(d0, d1);
		}

		if(fabs(ray.dir.y) > Epsilon)
		{
			float t0, t1;
			t0 = (min.y - ray.org.y) / ray.dir.y;
			t1 = (max.y - ray.org.y) / ray.dir.y;
			if(t1 < t0)
				std::swap(t0, t1);
			d0 = MAX(d0, t0);
			d1 = MAX(d1, t1);
		}

		if(fabs(ray.dir.z) > Epsilon)
		{
			float t0, t1;
			t0 = (min.z - ray.org.z) / ray.dir.z;
			t1 = (max.z - ray.org.z) / ray.dir.z;
			if(t1 < t0)
				std::swap(t0, t1);
			d0 = MAX(d0, t0);
			d1 = MIN(d1, t1);
		}

		if(d1 < d0 || d0 == -Infinity)
			return false;
		else
			return true;
	}
};



class Shader
{
public:
  // Virtual Shader routine
  virtual Vec3f Shade(Ray &ray) = 0;

};

class Primitive
{
public:
  Shader *shader;
  
  Primitive(Shader *sh): shader(sh)
  {};
  
  ~Primitive()
  {};
  
  // Virtual ray/primitive intersection routine
  virtual bool Intersect(Ray &ray) = 0;

  // Virtual Normal routine
  virtual Vec3f GetNormal(Ray &ray) = 0;

  virtual Box CalcBounds() {};

  virtual void GetUV(const Ray &ray, float &u, float &v) const {
    u = ray.getHitPoint(0).x;
    v = ray.getHitPoint(0).z;
  }


};

class Camera
{
public:
  // Virtual camera routine
  virtual int InitRay(float x, float y, vector<Ray>& rays,int num_rays)
  {};
};

#endif






