void setup() {
  size(1080, 360);
  PImage Im = loadImage("ae86.jpg");
  Im.resize(360, 360);
  image(Im, 0, 0);
  PImage Wow = wow(Im);
  image(Wow, Im.width, 0);
  PImage Mas = mas(wow(Im), int(random(5,15)));
  image(Mas, Im.width+Wow.width, 0);
}
void draw() {
}

PImage wow(PImage I) {
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp = I.get(0, 0, I.width, I.height/2);
  R.set(0, I.height/2, tmp);
  tmp= I.get(0, I.height/2, I.width, I.height/2);
  R.set(0, 0, tmp);
  for (int i=I.width/2; i<I.width; i++) R.set(i, i, color(255));
  return R;
}

PImage mas(PImage I, int n) {
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp;
  float [] arrR = new float[n*n];
  float [] arrG = new float[n*n];
  float [] arrB = new float[n*n];
  float maxR, maxG, maxB;
  int off=n/2;
  for (int x=0; x<I.width; x++) {
    for (int y=0; y<I.height; y++) {
      tmp=I.get(x-off, y-off, n, n);
      tmp.loadPixels();
      for (int i=0; i<tmp.pixels.length; i++) {
        arrR[i] = red(tmp.pixels[i]);
        arrG[i] = green(tmp.pixels[i]);
        arrB[i] = blue(tmp.pixels[i]);
      }
      maxR= max(arrR);
      maxG= max(arrG);
      maxB= max(arrB);
      R.set(x, y, color(maxR,maxG,maxB));
    }
  }
  return R;
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
