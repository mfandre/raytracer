#ifndef GROUP_HH
#define GROUP_HH

#include <vector> 

// for stl template 'vector' that realizes a dynamic array
#include "Basic.hh"

using namespace std;

class Group : public Primitive
{
public:
  vector<Primitive *> primitive;
  Box unionPri; // isso passará a ser um vetor...

  Group() : Primitive(NULL)
  {};
  
  ~Group();
  
  void Add(Primitive *prim)
  {
    primitive.push_back(prim);
    unionPrimitives(prim);
  };

  //Dado o centro (pos) e o raio da sphera
  // é calculado o cluster que ela vai pertencer
  // Cadascluster eh envolvido por um BOX
  int calcClusterSphere(Vec3f pos, float r){
  }

  int calcClusterTriangle(Vec3f center){
  }

  //Une todas as primitivas em um BOX, essa funcao dps será alterada pra criar varios boxes
  //Kmeans...
  void unionPrimitives(Primitive *prim){
	Box b;
	b = prim->CalcBounds();
	
	unionPri.Extend(b);

	/*
	cout << "[" << b.min.x << "," << b.min.y << "," << b.min.z << "]" << endl;
	cout << "[" << unionPri.min.x << "," << unionPri.min.y << "," << unionPri.min.z << "]" << endl << "---"<< endl;*/
	
  };

  virtual bool Intersect(Ray &ray);
  
  virtual Vec3f GetNormal(Ray &ray)
  {
    cerr << "cannot call getnormal of a group !" << endl;
    return Vec3f(0,0,0); 
  };
};

#endif




