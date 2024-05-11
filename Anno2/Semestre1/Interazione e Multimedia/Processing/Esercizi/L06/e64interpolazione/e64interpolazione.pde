PImage Im,Ic,Ir;
float mseO, mseP, mseR,psnrO,psnrP,psnrR;
void setup()
{
  
  Im=loadImage("lena.png");
  Im.filter(GRAY);
  size(1536,512);
  background(0);
  
  Ic=Im.copy();
  Ic.resize(256,256);
  Ic.resize(512,512);
  
  Ir=Im.copy();
  Ir.resize(256,256);
  Ir=replication2x(Ir);

  mseO=MSE(Im,Im);
  mseP=MSE(Im,Ic);
  mseR=MSE(Im,Ir);
  
  psnrO=PSNR(Im,Im);
  psnrP=PSNR(Im,Ic);
  psnrR=PSNR(Im,Ir);
  
  println("MSE con se stessa: " + mseO);
  println("MSE processing: " + mseP);
  println("MSE replication: " + mseR);
  
  println("PSNR con se stessa: " + psnrO);
  println("PSNR processing: " + psnrP);
  println("PSNR replication: " + psnrR);
  
  image(Im,0,0);
  image(Ic,512,0);
  image(Ir,1024,0);
  
}

void draw()
{
  
}

PImage replication2x(PImage I)
{
  PImage R=createImage(2*I.width,2*I.height,RGB);
  
  for(int x=0; x<I.width; x++)
  {
    for(int y=0; y<I.height;y++)
    {
      
      R.set(2*x,2*y,I.get(x,y));
      
      R.set(2*x+1,2*y,I.get(x,y));
      R.set(2*x,2*y+1,I.get(x,y));
      R.set(2*x+1,2*y+1,I.get(x,y));
      
    }
  }
  
  return R;
}

float MSE(PImage I1, PImage I2)
{
  float res=0;
  
  I1.loadPixels();
  I2.loadPixels();
  
  for(int i=0; i<I1.pixels.length;i++)
  {
    res+=pow(blue(I1.pixels[i])-blue(I2.pixels[i]),2);
  }
  
  res=res/I1.pixels.length;
  
  return res;
}

float PSNR(PImage I1, PImage I2)
{
  float res=0;
  
  float mse=MSE(I1,I2);
  //log è in base e
  //quindi per calcolare in base 10, serve dividere per log(10)
  
  // Calculates the base-10 logarithm of a number
  //float log10 (int x) {
  //  return (log(x) / log(10));
  //}
  
  res=10*log(255*255/mse)/log(10);
  return res;
}
