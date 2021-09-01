#ifndef POINTLIGHT_HXX
#define POINTLIGHT_HXX

#include "Light.hxx"

class PointLight : public Light
{
 public:
    Scene *scene;
    Vec3f pos; // position
    Vec3f intensity;

    PointLight(Vec3f pos, Vec3f intensity, Scene *scene)
	: pos( pos ), intensity( intensity ), scene(scene)
	{}
/*
    virtual Vec3f Illuminate(Ray &ray, Vec3f &intensity, int index=0) {
	ray.dir = pos - ray.org;
	ray.t = Length(ray.dir) - Epsilon;
	Normalize(ray.dir);

	float c1 = 1.0f;
	float c2 = 0.5;
	float c3 = 0.0f;

	float f_att = 1.0f / (c1 + c2*ray.t + c3*ray.t*ray.t);
	intensity = intensity * f_att;

	return intensity;
    }*/

    virtual Vec3f Illuminate(Vec3f &dir, Vec3f org, int index=0){
	Ray nray;
	dir = pos - org;
	Normalize(dir);
	nray.dir = dir;
	nray.org = org;
	float length = Length(nray.dir) - Epsilon;
	//ray.t = Length(ray.dir) - Epsilon;
	nray.t = length;
	//Normalize(nray.dir);

        if(scene->primitives.Intersect(nray) && nray.t > Epsilon)
           return Vec3f(0,0,0);

	float c1 = 1.0f;
	float c2 = 0.5;
	float c3 = 0.0f;

	float f_att = 1.0f / (length*length);//(c1 + c2*nray.t + c3*nray.t*nray.t);
	intensity = intensity * f_att;

	return intensity;
    }

 };

#endif // POINTLIGHT_HXX
