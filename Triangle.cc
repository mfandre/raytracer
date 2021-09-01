#include "Triangle.hh"

Triangule::Triangule(Vec3f a, Vec3f b, Vec3f c, Shader *s) : Primitive(s), a(a), b(b), c(c)
{
  Vec3f	v1 = b - a;
  Vec3f	v2 = c - a;
  normal = Cross(v1, v2);
  Normalize(normal);
}

bool Triangule::PointInTriangle(Vec3f &pt, Ray &ray)
{
  //Verifica se um ponto pertence ao triangulo
  return true;
}











