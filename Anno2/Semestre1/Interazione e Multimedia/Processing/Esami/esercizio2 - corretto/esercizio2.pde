float rnd;

void setup(){
  size(768,256);
  //PImage Im = loadImage("lena.png");
  PImage Im = loadImage("ae86.jpg");
  Im.resize(256,256);
  rnd = random(0,100);
  image(Im,0,0);
  PImage W = wow(Im);
  image(W,Im.width,0);
  PImage Wcorrect = wowC(Im);
  image(Wcorrect,Im.width+W.width,0);
}

void draw(){}

PImage wow(PImage I){
  PImage R = createImage(I.width,I.height,RGB);
  //DIVISIONE IMMAGINE
  PImage tmp = I.get(I.width/2,0,I.width/2,I.height);
  R.set(0,0,tmp);
  tmp = I.get(0,0,I.width/2,I.height);
  R.set(I.width/2,0,tmp);
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

PImage wowC(PImage I){
  PImage R = createImage(I.width,I.height,RGB);
  //DIVISIONE IMMAGINE
  PImage tmp = I.get(I.width/2,0,I.width/2,I.height);
  R.set(0,0,tmp);
  tmp = I.get(0,0,I.width/2,I.height);
  R.set(I.width/2,0,tmp);
  println("rnd: "+rnd+" %");
  int x,y;
  float r,g,b;
  //NEGATIVO SUPERIORE
  for(y=0; y<round(R.height*(rnd/100)); y++){
    for(x=0; x<R.width; x++){
      r=red(R.get(x,y));
      g=green(R.get(x,y));
      b=blue(R.get(x,y));
      R.set(x,y,color(b,g,r));
    }
  }
  //NEGATIVO INFERIORE
  for(; y<R.height; y++){
    for(x=0; x<R.width; x++){
      r=red(R.get(x,y));
      g=green(R.get(x,y));
      b=blue(R.get(x,y));
      R.set(x,y,color(r,b,g));
    }
  }
  return R;
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
