void setup(){
  size(1080,360);
  PImage Im = loadImage("ae86.jpg");
  Im.resize(360,360);
  image(Im,0,0);
  float gamma = random(1.5,4);
  println("Gamma: " + gamma);
  PImage i1 = gammaOp(Im,gamma);
  image(i1,Im.width,0);
  int L = int(random(50,250));
  int T = int(random(3,15));
  PImage i2 = gammaOp(Im,gamma,L,T);
  println("L: " + L + "\nT: " + T);
  image(i2,Im.width+i1.width,0);
}

void draw(){}

PImage gammaOp(PImage I, float gm){
  PImage R = I.copy();
  float r,g,b;
  R.loadPixels();
  float C = 1/pow(255,gm-1);
  for(int i=0; i<R.pixels.length; i++){
    r=C*pow(red(R.pixels[i]),gm);
    g=C*pow(green(R.pixels[i]),gm);
    b=C*pow(blue(R.pixels[i]),gm);
    R.pixels[i]=color(r,g,b);
  }
  R.updatePixels();
  return R;
}

PImage gammaOp(PImage I, float gm, int L, int T){
  PImage R = gammaOp(I,gm);
  PImage rt = createImage(L+2*T,L+2*T,RGB);
  rt.loadPixels();
  for(int i=0; i<rt.pixels.length; i++) rt.pixels[i] = color(255,0,255);
  color c;
  R.set(R.width/2-L/2-T,R.height/2-L/2-T,rt);
  for(int x=R.width/2-L/2; x<R.width/2+L/2; x++){
    for(int y=R.height/2-L/2; y<R.height/2+L/2; y++){
      c=I.get(x,y);
      R.set(x,y,c);
    }
  }
  return R;
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
