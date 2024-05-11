PImage Im, ImN, ImG, ImL;
void setup()
{
  Im=loadImage("lena.png");
  Im.resize(256,256);
  size(512,512);
  image(Im,0,0);
  
  ImN=negativo(Im);
  image(ImN,256,0);
  
  ImG=gamma(Im,2);
  image(ImG,0,256);
  ImL=logaritmo(Im);
  image(ImL,256,256);
  
  
}

void draw()
{
}

PImage negativo(PImage I)
{
  PImage R=I.copy();
  
  //I.loadPixels();
  R.loadPixels();
  
  float r,g,b;
  for(int i=0; i<R.pixels.length; i++)
  {
    r=255-red(R.pixels[i]);
    g=255-green(R.pixels[i]);
    b=255-blue(R.pixels[i]);
    
    R.pixels[i]=color(r,g,b);
  }
  
  R.updatePixels();
  
  return R;
}

PImage gamma(PImage I, float gm)
{
  PImage R=createImage(I.width,I.height,RGB);
  
  R.loadPixels();
  I.loadPixels();
  
  float r,g,b;
  float C=1/pow(255,gm-1);
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r=C*pow(red(I.pixels[i]),gm);
    g=C*pow(green(I.pixels[i]),gm);
    b=C*pow(blue(I.pixels[i]),gm);
    
    R.pixels[i]=color(r,g,b);
  }
  R.updatePixels();
  return R;
}

PImage logaritmo(PImage I)
{
  PImage R=createImage(I.width,I.height,RGB);
  
  R.loadPixels();
  I.loadPixels();
  
  float r,g,b;
  float C=255/log(256);
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r=C*log(1+red(I.pixels[i]));
    g=C*log(1+green(I.pixels[i]));
    b=C*log(1+blue(I.pixels[i]));
    
    R.pixels[i]=color(r,g,b);
  }
  R.updatePixels();
  return R;
}
