void setup(){
  size(720,360);
  PImage Im = loadImage("ae86.jpg");
  Im.resize(360,360);
  image(Im,0,0);
  PImage Wow = wow(Im);
  image(Wow,Im.width,0);
}

void draw(){}

PImage wow(PImage I){
  int x,y;
  float rnd = random(0,1);
  println(rnd);
  float r,g,b;
  PImage R = I.copy();
  PImage tmp = I.get(I.width/2,0,I.width/2,I.height);
  R.set(0,0,tmp);
  for(y=0; y<round(I.height*rnd); y++){
    for(x=0; x<I.width; x++){
      r=255-red(R.get(x,y));
      g=255-green(R.get(x,y));
      b=255-blue(R.get(x,y));
      R.set(x,y,color(r,g,b));
    }
  }
  for(; y<I.height; y++){
    for(x=0; x<I.width; x++){
      r=red(R.get(x,y));
      g=green(R.get(x,y));
      R.set(x,y,color(r,g,0));
    }
  }
  return R;
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
