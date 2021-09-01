#ifndef PHONGSHADER_HXX
#define PHONGSHADER_HXX

#include "Basic.hh"
#include "Scene.hh"

class PhongShader : public Shader
{
public:
  Vec3f color;
  float ka, ks, kd, kg, ke;
  Scene *scene;

  PhongShader(Vec3f color, float ka, float ks, float kd, float ke, Scene *scene)
    : color(color), ka(ka), ks(ks), kd(kd) , ke(ke) , scene(scene)
  {};

  ~PhongShader()
  {};
  
  void Reflect(Vec3f &newDir, Vec3f &normal, Vec3f &oldDir);
  
  virtual Vec3f Shade(Ray &ray);
};

#endif



