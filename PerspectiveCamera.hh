#ifndef PERSPECTIVECAMERA_HXX
#define PERSPECTIVECAMERA_HXX

#include "Basic.hh"
#include "Vec3f.hh"


#include <vector> 
using namespace std;

class PerspectiveCamera : public Camera
{
	float focus;
	Vec3f xAxis,yAxis,zAxis;
	float aspect;
public:
  Vec3f pos, dir, up;
  float angle;
  int resX, resY;
  Vec3f dir_X, dir_Y;
  float res_X, res_Y;
  
  PerspectiveCamera()
  {};
  
  PerspectiveCamera(Vec3f p, Vec3f d, Vec3f vup, float ang, int rX, int rY)
  {
    pos = p;
    dir = d;
    Normalize(dir);
    up = vup;
    Normalize(up);
    angle = ang;
    resX = rX;
    resY = rY;
    
    if( ((ang-180) > Epsilon) || ((ang-180) < -Epsilon) )
      {
	res_Y = tan(angle/2) * 2;
	res_X = res_Y * resX / resY;
      }

    dir_X = Cross(up, dir);
    Normalize(dir_X);
    dir_Y = Cross(dir, dir_X); 
    Normalize(dir_Y);

    zAxis = dir;
    xAxis = Cross(dir,up);
    yAxis = Cross(xAxis,zAxis);

    Normalize(xAxis);
    Normalize(yAxis);
    Normalize(zAxis);

    aspect = resX / float(resY);

    // angulo de abertura:
    float angleInRad = angle * (float)M_PI / 180.0f;
    focus = 1.0f / tan(angleInRad/2.0f);
  };

  ~PerspectiveCamera() {};
  
  virtual int InitRay(float x, float y, vector<Ray>& rays,int num_rays);
};

#endif
