PImage I;
float r,g,b;
color c,c1;
int ar;
void setup(){
  I=loadImage("lena.png");
  size(512,512);
  ar=0;
  c=color(255,255,0);
  I.loadPixels();
  for (int i=0;i<I.width;i++){
    I.pixels[pos(i,i,I.width)]=c;
  }
  I.updatePixels();
 
}
void draw(){
  image(I,0,0);
}

void keyPressed(){
  if (key=='r'){
    ar--;
  }
  else if (key=='R'){
    ar++;
  }
  I.loadPixels();
  for (int i=0;i<I.pixels.length;i++){
    c1=I.pixels[i];
    c1=color(red(c1)+ar,green(c1),blue(c1));
    I.pixels[i]=c1;
  }
  I.updatePixels();
  //noterete che appena si supera la soglia per qualche 
  //pixel, non saremo più in grado di recuperare l'imamgine
  //originale
  println(ar);
}

int pos (int x, int y, int w){
  return x+y*w;
}
