#include "Image.hh"
#include "Basic.hh" 
#include "Sphere.hh"
#include "Triangle.hh"
#include "InfinitePlane.hh"
#include "PerspectiveCamera.hh" 
#include "FlatShader.hh"
#include "Scene.hh"
#include <time.h>

void Render(char *filename,int num_rays, char *outputImg)
{ 
  printf("===============> %s, %d, %s \n", filename, num_rays, outputImg);
  int depth = 3;
  Scene	scene(depth); 
  scene.ParseNFF(filename);

  //kmeans
  double **cluster = kmeans_main(scene.amostras,6);
  vector<Primitive *>::iterator	iter = scene.primitives.primitive.begin();
  Primitive *pri;

  //criando os grupos
  for(int j=0;j<6;j++)
  	scene.grupos_primitivas.push_back(new Group());

  //Esse for pega todas as primitivias lidas do arquivo.nff
  //e separa em grupos definidos pelo kmeans...
  //vale lembrar que quando eh inserida uma primitiva em um grupo
  // ja � feito um box englobando ela e as demais prmitivas que pertecem 
  // ao mesmo grupo
  for(int i=0;i<scene.primitives.primitive.size();i++,iter++){
  	for(int j=0;j<6;j++){
	    if(cluster[j][i]==1){
		scene.grupos_primitivas[j]->Add(*iter);
            }
	}
  }
  
  //imprimindo os box!!!
  for(int i=0;i<scene.grupos_primitivas.size();i++){
	cout << "[" << scene.grupos_primitivas[i]->unionPri.min.x << "," << scene.grupos_primitivas[i]->unionPri.min.y << "," << scene.grupos_primitivas[i]->unionPri.min.z << "]" << endl;
	cout << "[" << scene.grupos_primitivas[i]->unionPri.max.x << "," << scene.grupos_primitivas[i]->unionPri.max.y << "," << scene.grupos_primitivas[i]->unionPri.max.z << "]" << endl;
	cout << scene.grupos_primitivas[i]->primitive.size() << endl;
  }

  Image	*img;
  int	RES_X, RES_Y;
  RES_X = ((PerspectiveCamera *)scene.camera)->resX; 
  RES_Y = ((PerspectiveCamera *)scene.camera)->resY;
  img = new Image(RES_X, RES_Y);
  if(!img) 
    return;
  img->Clear();
  
  time_t t1 = time(&t1);
  //Ray	ray;
  for(int j = 0; j < RES_Y; j++)
  {
    for(int i = 0; i < RES_X; i++)
    {
      vector<Ray> rays;
      Vec3f color(0,0,0);

      int number = scene.camera->InitRay(i, j, rays,num_rays);

      for(int s=0; s<number; s++){
          //Ray ray(rays[s]);
          //float weight = ray.contribution;
          //cout << weight << endl;
          color = color + scene.RayTrace(rays[s]);
      }
      color = color/number;
      //float sampleRatio = 0.25f;
      //float exposure = -1.00f;

//Vec3f	color = scene.RayTrace(ray);
      //color = Vec3f((1.0f-expf(color[0])*exposure),(1.0f-expf(color[1])*exposure),(1.0f-expf(color[2])*exposure));
//color = sampleRatio*color;
      img->SetValuePixel(i, j, color);
    }
  }
  time_t t2 = time(&t2);
  printf("Rendering Time = %d seg\n", (int)t2 - (int)t1);

  if(img == NULL){
    printf("opppssssss img null\n");
    return;
  }

  printf("Saving image\n");
  int result = img->SavePPM(outputImg);
  printf("Result save image %d\n", result);
  if(result < 0){
    printf("Cannot save the file %s.\n", outputImg);
  }
    
  delete img;
}

int main(int argc, char *argv[])
{
  if(argc < 4)
    {
      printf("render <inputfile> <outputfile> <numero_raios>\n");
      return 0;
    }
  printf(" ======> %s, %s, %s \n", argv[1], argv[2], argv[3]);

  printf("Rendering %s...\n", argv[1]);
  //time_t t1 = time(&t1);
  Render(argv[1],atoi(argv[3]), argv[2]);
  //time_t t2 = time(&t2);	
  printf("zica\n");
  
  //printf("Rendering Time = %d seg\n", (int)t2 - (int)t1);
  
  return 0;
}



