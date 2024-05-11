//Esercizio in cui si implementa un metodo che applica un operatore solo ad una sottoimmagine. Il metodo prende in input le coordinate del
//centro della sottoimmagine e la dimensione della sottoimmagine.
//Nello sketch si usa il mouse per applicare l'operazione, mostrando anche un quadrato che delimita la zona da elaborare
//Con + e - si possono variare le dimensioni dell'area da elaborare.

PImage Im,IL;
int K=75;
void setup()
{
  Im=loadImage("lena.png");
  IL=Im.copy();
  size(512,512);
  image(Im,0,0);
}

void draw()
{
  image(IL,0,0);
  
  noFill();
  strokeWeight(3);
  stroke(0,255,0);
  rectMode(CENTER);
  
  rect(mouseX,mouseY,K,K);
  

}


void mousePressed()
{
    //L'ultimo parametro indica l'operazione. 
    //Abbiamo associato a 0 il negativo, a 1 il logaritmo e a 2 gamma.
    IL=applyOperator(IL,mouseX,mouseY,K,2);
}

void keyPressed()
{
  if((key=='+')&&(K<511))
   K+=2;
  if((key=='-')&&(K>3))
   K-=2;
}
PImage applyOperator(PImage I, float x, float y, int n, int s)
{
  PImage res=I.copy();
  
  PImage tmp;
  tmp=I.get(int(x)-n/2,int(y)-n/2,n,n);
  
  switch(s)
  {
    case 0:res.set(int(x)-n/2,int(y)-n/2,negativo(tmp)); break;
    case 1:res.set(int(x)-n/2,int(y)-n/2,logaritmo(tmp)); break;
    case 2:res.set(int(x)-n/2,int(y)-n/2,gamma(tmp,2)); break;
    default:;
  }
  return res;
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
