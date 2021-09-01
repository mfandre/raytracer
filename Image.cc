#include "Image.hh"

using namespace std;

int Image::SavePPM(char *fileName)
{
	FILE *outfile;

	// Open a file to write
	outfile = fopen(fileName, "w");

	// Verifing the file
	if (outfile == NULL)
	{
		fprintf(stderr, "ERROR: Image::SavePPM couldn't open file '%s' for output.\n",fileName);
		return 0;
	}

	// Putting the data

	fprintf(outfile, "P3\n");  // Heading
	fprintf(outfile, "%d	%d	255", resX, resY); // width, height and maximum color value

	int position;

	// Put the Colors for each pixel
	for(int contY=0; contY < resY; contY++)
		for(int contX=0; contX < resX; contX++)
		{
			position = contY*resX + contX;
			if ((position % 8) == 0)
			fprintf(outfile,"\n");
			fprintf(outfile, "%d %d %d ", (int) data[position].x, (int) data[position].y, (int) data[position].z);
		}

	// Close the file
	fclose(outfile);

	// All is correct...
	return 1;
}

void eatComments(FILE *f)
{
  int ch;
  while((ch=getc(f))=='#')
    {
      char str[1000];
      fgets(str,1000,f);
    }
  ungetc(ch,f);
}

void eatWhitespace(FILE *f)
{
  int ch;
  ch=getc(f);
  while(ch==' ' || ch=='\t' || ch=='\n' || ch=='\f' || ch=='\r')
    {
      ch=getc(f);
    }
  ungetc(ch,f);
}

int Image::LoadPPM(char *fileName)
{
  cout << "Reading ppm image " << fileName << endl;

  FILE *f;
  char ch;
  int width, height, colres;

  f = fopen(fileName,"r");

  if (f == NULL) {
    cerr << "ReadPPM : could not open file '" << fileName <<endl;
    exit(-1);
  }

  char str[100];
  eatWhitespace(f);
  eatComments(f);
  eatWhitespace(f);

  fscanf(f,"%s",str);
  if (!strcmp(str,"P3")) {
    eatWhitespace(f);
    eatComments(f);
    eatWhitespace(f);
    fscanf(f,"%d %d",&width,&height);
    if(width<=0 || height<=0)
      {
	printf("Error: width and height of the image must be greater than zero. File: %s\n",fileName);
	exit(1);
      }
    eatWhitespace(f);
    eatComments(f);
    eatWhitespace(f);
    fscanf(f,"%d",&colres);

    data = new Vec3f[width * height];
    resX = width;
    resY = height;

    ch=0;
    while(ch!='\n') fscanf(f,"%c",&ch);

    for (int y=0;y<height;y++) {
      for (int x=0;x<width;x++) {
	int c[3];
	fscanf(f,"%d %d %d",c+0,c+1,c+2);

	int position = (resY - y - 1)*resX + x;

	data[position].x = c[0] / float(colres);
	data[position].y = c[1] / float(colres);
	data[position].z = c[2] / float(colres);
      }
    }
    fclose(f);
  } else {
    cerr << "Wrong format !" << endl;
    exit(0);
  }
}


void Image::Clear()
{
	for(int contY=0; contY < resY; contY++)
		for(int contX=0; contX < resX; contX++)
		{
			int position = contY*resX + contX;

			data[position].x = 0;
			data[position].y = 0;
			data[position].z = 0;
		}
}

Vec3f Image::GetValuePixel(int x, int y)
{
	int position = (resY - y - 1)*resX + x;
	
	return data[position];
}


void Image::SetValuePixel(int x, int y, Vec3f &color)
{
	int position = (resY - y - 1)*resX + x;

	data[position].x = (int) 255 * color.x;
	data[position].y = (int) 255 * color.y;
	data[position].z = (int) 255 * color.z;
}

