PImage Im;
int N;
void setup()
{
  size(512,512);
  Im=loadImage("lena.png");
  N=101;
}

void draw()
{
  image(Im,0,0);
  noFill();
  stroke(0,255,0);
  rectMode(CENTER);
  rect(mouseX,mouseY,N,N);
  
  if(mousePressed)
    Im=applyArea(Im,mouseX,mouseY,N,mouseButton==RIGHT);
}

PImage lemonFilter(PImage I)
{
  PImage R=I.copy();
  
  R.loadPixels();
  float r,g,b;
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r=red(R.pixels[i]);
    g=green(R.pixels[i]);
    b=blue(R.pixels[i]);
    
    R.pixels[i]=color(r-b/8,g+b,0);
  }
  
  R.updatePixels();
  return R;
}

PImage orangeFilter(PImage I)
{
  PImage R=I.copy();
  
  R.loadPixels();
  float r,g,b;
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r=red(R.pixels[i]);
    g=green(R.pixels[i]);
    b=blue(R.pixels[i]);
    
    R.pixels[i]=color(r+b,g,0);
  }
  
  R.updatePixels();
  return R;
}

PImage applyArea(PImage I, int x, int y, int size, boolean f)
{
  PImage R=I.copy();
  PImage tmp=R.get(x-size/2,y-size/2,size,size);
  
  if(f)
    tmp=lemonFilter(tmp);
  else
    tmp=orangeFilter(tmp);
    
  R.set(x-size/2,y-size/2,tmp);
  return R;
}

void keyPressed()
{
  if ((key=='r')||(key=='R'))
    setup();
    
  if ((key=='+')&&(N<151))
    N+=2;
  if ((key=='-')&&(N>51))
    N-=2;
}