#ifndef EYALIGHTSHADER_HH
#define EYALIGHTSHADER_HH

#include "Basic.hh"

class EyeLightShader : public Shader
{
public:
  Vec3f color;
  char *  file_texture;
  Texture *texture;

  EyeLightShader();
  EyeLightShader(Vec3f color)
    : color(color)
  {
  };
  
  ~EyeLightShader()
  {};
  
   //eyeLightshader
  virtual Vec3f Shade(Ray &ray)
  {
	return color* fabs(Dot(ray.dir,ray.hit->GetNormal(ray))); ;
  };

  virtual Vec3f getColor(){
    return color;
  };
};



#endif
