//Estrazione bitplane. Con + e - si cambia il piano di bit estratto. Di default il numero più significativo (numero 7)
PImage Im,Ib;
int K;
void setup()
{
  Im=loadImage("lena.png");
  Im.filter(GRAY);
  size(1024,512);
  image(Im,0,0);
  
  K=7;
  Ib=bitplane(Im,K);
  image(Ib,512,0);
}

void draw()
{
}

PImage bitplane(PImage I, int nb)
{
  PImage R=I.copy();
  
  R.loadPixels();
  
  int x;
  int r;
  for(int i=0; i<R.pixels.length;i++)
  {
    x=int(blue(R.pixels[i]));
    
    r=(x>>nb)&1;
    
    R.pixels[i]=color(255*r); 
  }
  
  R.updatePixels();
  return R;
}

void keyPressed()
{
  if((key=='+')&&(K<7))
  {
    Ib=bitplane(Im,++K);
    image(Ib,512,0);
    println(K);
  }
  if((key=='-')&&(K>0))
  {
    Ib=bitplane(Im,--K);
    image(Ib,512,0);
    println(K);
  }
}
