#ifndef SCENE_HXX
#define SCENE_HXX

#include "Group.hh"
#include "PerspectiveCamera.hh"
#include "Light.hxx"
#include <vector> // for dynamic array stl template 'vector'
#include "kmeans2.hh"
class Scene
{
  int rayDepth, maxDepth;
  // parse an nff file 'fileName', add all its primitives
  // to the specified group...
  void ParseNFF(FILE *file, char *fileName, Group *groupToAddTo);
  
public:
  Group primitives; // group of all the primitives of this scene
  Vec3f bgColor; // background color, as long as we don't have an environment shader ...
  Camera *camera;
  std::vector<Light*> lights; // vetor com a luzes da cena
  bool castShadows;
  vector<Vec3f> amostras; //vetor com as posicoes das primitivas, usado no kmeans
  vector<Group*> grupos_primitivas;

  Scene(int depth = 0)
    : bgColor(Vec3f(0,0,0)), maxDepth(depth),
      camera(new PerspectiveCamera(Vec3f(0,0,0),Vec3f(0,0,-1),
				   Vec3f(0,1,0),60,640,480))
  { rayDepth = 0;};
  
  ~Scene()
  {  if(camera) delete camera;  };
  
  void ParseNFF(char *fileName);
  
  bool Intersect(Ray &ray);
  
  Vec3f RayTrace(Ray &ray);
};

#endif
