#ifndef FLATSHADER_HXX
#define FLATSHADER_HXX

#include "Basic.hh"

class FlatShader : public Shader
{
public:
  Vec3f color;
  
  FlatShader();
  FlatShader(Vec3f color)
    : color(color)
  {};
  
  ~FlatShader()
  {};
  
   virtual Vec3f Shade(Ray &ray){
     return color;
   };

   virtual Vec3f getColor(){
     return color;
   };
};



#endif
