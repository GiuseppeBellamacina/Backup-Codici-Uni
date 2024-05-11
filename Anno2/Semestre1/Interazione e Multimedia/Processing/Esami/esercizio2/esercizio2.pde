void setup(){
  size(512,256);
  PImage Im = loadImage("lena.png");
  //PImage Im = loadImage("ae86.jpg");
  Im.resize(256,256);
  image(Im,0,0);
  PImage W = wow(Im);
  image(W,Im.width,0);
}

void draw(){}

PImage wow(PImage I){
  PImage R = createImage(I.width,I.height,RGB);
  //DIVISIONE IMMAGINE
  PImage tmp = I.get(I.width/2,0,I.width/2,I.height);
  R.set(0,0,tmp);
  tmp = I.get(0,0,I.width/2,I.height);
  R.set(I.width/2,0,tmp);
  float rnd = random(0,100);
  println("rnd: "+rnd+" %");
  int x,y;
  float r,g,b;
  //NEGATIVO SUPERIORE
  for(y=0; y<round(R.height*(rnd/100)); y++){
    for(x=0; x<R.width; x++){
      r=255-red(R.get(x,y));
      g=green(R.get(x,y));
      b=255-blue(R.get(x,y));
      R.set(x,y,color(r,g,b));
    }
  }
  //NEGATIVO INFERIORE
  for(; y<R.height; y++){
    for(x=0; x<R.width; x++){
      r=red(R.get(x,y));
      g=255-green(R.get(x,y));
      b=255-blue(R.get(x,y));
      R.set(x,y,color(r,g,b));
    }
  }
  return R;
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
