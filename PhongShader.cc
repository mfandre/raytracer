#include "PhongShader.hh"
#include <math.h>

void PhongShader::Reflect(Vec3f &newDir, Vec3f &normal, Vec3f &oldDir)
{
  // Escreva o codigo aqui
}


Vec3f PhongShader::Shade(Ray &ray){
	const Vec3f la = Vec3f(1,1,1);
	const Vec3f ca = color;
	const Vec3f cd = ca;
	const Vec3f cs(1,1,1);

	Vec3f incident(ray.dir);
	Vec3f normal(ray.hit->GetNormal(ray));
	float cosinus = Dot(incident,normal);

	if (cosinus > 0) normal = -normal; else cosinus = -cosinus;
	
	Vec3f reflected = (2*cosinus)*normal + incident;
	
	Vec3f ambient = ka*Product(ca,la);
	
	Vec3f sumDiffuse(0,0,0);
	Vec3f sumSpecular(0,0,0);
	Vec3f intensidade;
	Vec3f dir;
	for(int i=0;i < scene->lights.size();i++){
		intensidade = scene->lights[i]->Illuminate(dir,ray.getHitPoint(0),0);
		intensidade.assertInterval(0,1);

		sumDiffuse = sumDiffuse + intensidade*std::max(0.0f,Dot(dir,normal));

		float specularPower = std::max(0.0f,Dot(dir,reflected));
		//cout << specularPower << endl;
	    	if (specularPower > 0) 
			specularPower = pow(specularPower,ke);
		
		sumSpecular =  intensidade * specularPower;
		sumSpecular.assertInterval(0,1);
	}
	Vec3f diffuse = kd * Product(cd, sumDiffuse);
	diffuse.assertInterval(0,1);

	Vec3f specular = ks * Product(cs, sumSpecular);
	specular.assertInterval(0,1);	

	Vec3f result = ambient + diffuse +specular;
	result.assertInterval(0,1);
	
	return result;//* fabs(Dot(ray.dir,ray.hit->GetNormal(ray)));
}

/*
Vec3f PhongShader::Shade(Ray &ray){
  const Vec3f la(1,1,1);
  const Vec3f ca = color;
  const Vec3f cd = ca;
  const Vec3f cs(1,1,1);

  Vec3f normal = ray.hit->GetNormal(ray);
  if(Dot(normal,ray.dir) > 0.0f)
    normal = - normal;

  //Normalize(normal);

  // Vetor de reflexao!!!
  Vec3f reflect = ray.dir - 2.0f * Dot(normal,ray.dir) * normal;
	//Normalize(reflect);

  Vec3f termo1 = ka*Product(ca,la);
  Vec3f termo2(0,0,0);
  Vec3f termo3(0,0,0);

  for(int i=0;i < scene->lights.size();i++){
    Vec3f dir;
      Vec3f intensidade = scene->lights[i]->Illuminate(dir,ray.getHitPoint(0),0);
      float cosLightNormal = Dot(dir,normal);
      if(cosLightNormal <= 0)
         continue;
      termo2 = termo2 + intensidade*cosLightNormal;
      float cosLightReflect = Dot(dir,reflect);
      if(cosLightReflect <= 0)
        continue;

      termo3 = termo3 + intensidade*powf(cosLightReflect,ke);
  }
  termo2 = Product(termo2,cd)*kd;
  termo3 = Product(termo3,cs)*ks;

  
  Vec3f result = termo1 + termo2 + termo3;
  //result.assertInterval(0,1);
  return result;
}
*/

/*
Vec3f PhongShader::Shade(Ray &ray)
{
  Vec3f act = color;
  Vec3f col;
  Vec3f normal = ray.hit->GetNormal(ray);

  if(Dot(normal,ray.dir) > 0.0f)
    normal = - normal;
  
  // Vetor de reflecao!!!
  Vec3f reflect = ray.dir - 2.0f * Dot(normal,ray.dir) * normal;

  // Dados do ambiente
  Vec3f ambienteIntensidade(1.0f,1.0f,1.0f);
  Vec3f amienteCor = ka*color;
  Vec3f result = Product(amienteCor,ambienteIntensidade);


  // Na direcao da luz
  Ray shadow;
  shadow.org = ray.org + ray.t * ray.dir - Vec3f(1.0f,1.0f,1.0f)*Epsilon; // -episilon

  // Para cara funte luz
  for(int i=0;i < scene->lights.size();i++){
    Vec3f intensidadeLuz;
    Vec3f result_local(0,0,0);
    
    //para o numero de raios que SAEM do ponto de luz!!! no meu caso é 1
    if(scene->lights[i]->Illuminate(shadow,intensidadeLuz)){
       //distancis pra fonte de luz
       float distancia = shadow.t;
       float cosLightNormal = Dot(shadow.dir,normal);
       if(cosLightNormal > 0.0f){
         if(scene->primitives.Intersect(shadow)){
           if(shadow.t < distancia)
             continue;
         }

         // termo difuso
         Vec3f corDifusa = kd*color;
         result_local = result_local + Product(corDifusa * cosLightNormal,intensidadeLuz);
    
         //termo specular
         float cosLightReflect = Dot(shadow.dir,reflect);
         if(cosLightReflect > 0.0f){
           Vec3f corSpecular = ks * Vec3f(1.0f,1.0f,1.0f); // branca
           result_local = result_local + Product(corSpecular * powf(cosLightReflect,ke),intensidadeLuz);
         }
       }
       
    }
    result = result + result_local;
  }

  return result;
}

*/






