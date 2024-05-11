PImage I;
float r,g,b=0;
color c;
void setup(){
  I=createImage(500,500,RGB);
  size(500,500);
  
  for (int y=0;y<I.height;y++){
    for (int x=0;x<I.width;x++){
      r=lerp(0,255,float(x)/I.width);
      g=lerp(0,255,float(y)/I.height);
      c=color(r,g,b);
      I.set(x,y,c);
    }
  }
  
}
void draw(){
  image(I,0,0);
}
