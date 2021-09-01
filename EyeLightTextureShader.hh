#ifndef EYALIGHTTEXTURESHADER_HH
#define EYALIGHTTEXTURESHADER_HH

#include "Basic.hh"
#include "Texture.hh"

class EyeLightTextureShader : public Shader
{
public:
  Vec3f color;
  char *  file_texture;
  Texture *texture;

  EyeLightTextureShader();
  EyeLightTextureShader(Vec3f color,char* filename)
    : color(color), file_texture(filename)
  {
	texture = new Texture();
	//cout << file_texture << endl;
	cout << texture->LoadPPM(file_texture) << endl;
	//cout << "============>" << texture->GetTexel(10,10).z << endl;
  };
  
  ~EyeLightTextureShader()
  {};
  
   //eyeLightshader
  virtual Vec3f Shade(Ray &ray)
  {
	color = color;//* fabs(Dot(ray.dir,ray.hit->GetNormal(ray))); 

	float u, v;
	ray.hit->GetUV(ray, u, v);
	Vec3f textureColor =  texture->GetTexel(u, v) ;
	//cout << textureColor.x << "," << textureColor.y << "," << textureColor.z << endl;
	//cout << "[" << color.x << "," << color.y << "," << color.z << "]" << endl;
	Vec3f result = Product(color, textureColor) ;
	result.assertInterval(0,1);
	
	return result* fabs(Dot(ray.dir,ray.hit->GetNormal(ray))); ;
  };

  virtual Vec3f getColor(){
    return color;
  };
};



#endif
