float rnd;

void setup() {
  rnd = random(0, 1);
  println("Random: "+rnd);
  size(1536, 512);
  textSize(17);
  PImage originale = loadImage("ae86.jpg");
  PImage lin = originale.copy();
  lin.resize(512,512);
  originale.resize(256, 256);
  image(originale, 0, 0);
  text("Originale", 0, 20);
  PImage neg = negativo(originale);
  image(neg, originale.width, 0);
  fill(0);
  text("Negativo", originale.width, 20);
  PImage gam = gamma(originale, 2.4);
  image(gam, 0, originale.height);
  fill(255);
  text("Gamma", 0, originale.height+20);
  PImage log = logaritmo(originale);
  image(log, originale.width, originale.height);
  fill(0);
  text("Logaritmo", originale.width, originale.height+20);
  PImage mas = massimo(originale, 9);
  image(mas, 2*originale.width, 0);
  fill(255);
  text("Massimo", 2*originale.width, 20);
  PImage min = minimo(originale, 9);
  image(min, 3*originale.width, 0);
  text("Minimo", 3*originale.width, 20);
  PImage med = mediano(originale, 9);
  image(med, 2*originale.width, originale.height);
  text("Mediano", 2*originale.width, originale.height+20);
  PImage smi = sminchia(originale);
  image(smi, 3*originale.width, originale.height);
  text("Sminchiata", 3*originale.width, originale.height+20);
  // lin sta sopra
  lin = lineaDiStoCactus(lin);
  image(lin, 4*originale.width, 0);
  text("Linea di sto cactus", 4*originale.width, 20);
}

void draw() {
}

PImage negativo(PImage I) {
  //PImage R=createImage(I.width, I.height, RGB);
  PImage R=I.copy();
  R.loadPixels();
  float r, g, b;
  for (int i=0; i<R.pixels.length; i++) {
    r=255-red(R.pixels[i]);
    g=255-green(R.pixels[i]);
    b=255-blue(R.pixels[i]);
    R.pixels[i]=color(r, g, b);
  }
  R.updatePixels();
  return R;
}

PImage gamma(PImage I, float gm) {
  PImage R=I.copy();
  R.loadPixels();
  float r, g, b;
  float C=1/pow(255, gm-1);
  for (int i=0; i<R.pixels.length; i++) {
    r=C*pow(red(R.pixels[i]), gm);
    g=C*pow(green(R.pixels[i]), gm);
    b=C*pow(blue(R.pixels[i]), gm);
    R.pixels[i]=color(r, g, b);
  }
  R.updatePixels();
  return R;
}

PImage logaritmo(PImage I) {
  PImage R=I.copy();
  R.loadPixels();
  float r, g, b;
  float C=255/log(256);
  for (int i=0; i<R.pixels.length; i++) {
    r=C*log(1+red(R.pixels[i]));
    g=C*log(1+green(R.pixels[i]));
    b=C*log(1+blue(R.pixels[i]));
    R.pixels[i]=color(r, g, b);
  }
  R.updatePixels();
  return R;
}

PImage massimo(PImage I, int N) {
  PImage R=createImage(I.width, I.height, RGB);
  PImage tmp;
  int off=N/2;
  float[] arrR, arrG, arrB;
  arrR = new float[N*N];
  arrG = new float[N*N];
  arrB = new float[N*N];
  for (int x=0; x<I.width; x++) {
    for (int y=0; y<I.height; y++) {
      tmp=I.get(x-off, y-off, N, N);
      tmp.loadPixels();
      for (int i=0; i<tmp.pixels.length; i++) {
        arrR[i]=red(tmp.pixels[i]);
        arrG[i]=green(tmp.pixels[i]);
        arrB[i]=blue(tmp.pixels[i]);
      }
      R.set(x, y, color(max(arrR), max(arrG), max(arrB)));
    }
  }
  return R;
}

PImage minimo(PImage I, int N) {
  PImage R=createImage(I.width, I.height, RGB);
  PImage tmp;
  int off=N/2;
  int xs, ys;
  float[] arrR, arrG, arrB;
  for (int x=0; x<I.width; x++) {
    for (int y=0; y<I.height; y++) {
      xs=x-off;
      ys=y-off;
      tmp=I.get(max(0, xs), max(0, ys), min(N, min(N+xs, I.width-xs)), min(N, min(N+ys, I.height-ys)));
      tmp.loadPixels();
      arrR=new float[tmp.pixels.length];
      arrG=new float[tmp.pixels.length];
      arrB=new float[tmp.pixels.length];
      for (int i=0; i<tmp.pixels.length; i++) {
        arrR[i]=red(tmp.pixels[i]);
        arrG[i]=green(tmp.pixels[i]);
        arrB[i]=blue(tmp.pixels[i]);
      }
      R.set(x, y, color(min(arrR), min(arrG), min(arrB)));
    }
  }
  return R;
}

PImage mediano(PImage I, int N) {
  PImage R=createImage(I.width, I.height, RGB);
  PImage tmp;
  int off=N/2;
  float medR, medG, medB;
  float[] arrR, arrG, arrB;
  arrR = new float[N*N];
  arrG = new float[N*N];
  arrB = new float[N*N];
  for (int x=0; x<I.width; x++) {
    for (int y=0; y<I.height; y++) {
      tmp=I.get(x-off, y-off, N, N);
      tmp.loadPixels();
      for (int i=0; i<tmp.pixels.length; i++) {
        arrR[i]=red(tmp.pixels[i]);
        arrG[i]=green(tmp.pixels[i]);
        arrB[i]=blue(tmp.pixels[i]);
      }
      arrR=sort(arrR);
      arrG=sort(arrG);
      arrB=sort(arrB);
      if ((N*N)%2==1) {
        medR=arrR[(N*N)/2];
        medG=arrG[(N*N)/2];
        medB=arrB[(N*N)/2];
      } else
      {
        medR=(arrR[(N*N)/2]+arrR[(N*N)/2-1])/2;
        medG=(arrG[(N*N)/2]+arrG[(N*N)/2-1])/2;
        medB=(arrB[(N*N)/2]+arrB[(N*N)/2-1])/2;
      }
      R.set(x, y, color(medR, medG, medB));
    }
  }
  return R;
}

PImage sminchia(PImage I) {
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp = I.get(I.width/2, 0, I.width/2, I.height);
  R.set(0, 0, tmp);
  tmp = I.get(0, 0, I.width/2, I.height);
  R.set(I.width/2, 0, tmp);
  return R;
}

PImage lineaDiStoCactus(PImage I) {
  PImage R = I.copy();
  int x, y;
  float r,g,b;
  for (y=0; y<round(I.height*rnd); y++) {
    for (x=0; x<I.width; x++) {
      r=red(I.get(x,y));
      g=green(I.get(x,y));
      b=blue(I.get(x,y));
      R.set(x,y,color(b,g,r));
    }
  }
  /*for (; y<I.height; y++) {
    for (x=0; x<I.width; x++) {
      r=red(I.get(x,y));
      g=green(I.get(x,y));
      b=blue(I.get(x,y));
      R.set(x,y,color(r,b,g));
    }
  }*/
  return R;
}

void keyPressed() {
  if (key=='r' || key=='R') setup();
}
