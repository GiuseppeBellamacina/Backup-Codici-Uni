PImage Im;

void setup() {
  size(1080, 360);
  Im = loadImage("ae86.jpg");
  Im.resize(360, 360);
  image(Im, 0, 0);
  PImage Rev = rev(Im);
  image(Rev, Im.width, 0);
  PImage Med = med(Im, 9);
  image(Med, Im.width+Rev.width, 0);
}

void draw() {
}

PImage rev(PImage I) {
  PImage R = createImage(I.width, I.height, RGB);
  PImage i1 = I.get(0, 0, I.width/2, I.height);
  PImage i2 = I.get(I.width/2, 0, I.width/2, I.height);
  R.set(0, 0, i2);
  R.set(I.width/2, 0, i1);
  for (int i=0; i<R.width; i++) R.set(i, i, color(255, 255, 0));
  return R;
}

PImage med(PImage I, int n) {
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp;
  float [] matRed = new float[n*n];
  float [] matGreen = new float[n*n];
  float [] matBlue = new float[n*n];
  int offset=n/2;
  float medRed,medGreen, medBlue;
  for (int i=0; i<I.width; i++) {
    for (int j=0; j<I.height; j++) {
      tmp=I.get(i-offset, j-offset, n, n);
      tmp.loadPixels();
      for (int k=0; k<tmp.pixels.length; k++) {
        matRed[k] = red(tmp.pixels[k]);
        matGreen[k] = green(tmp.pixels[k]);
        matBlue[k] = blue(tmp.pixels[k]);
      }
      medRed=findMed(matRed);
      medGreen=findMed(matGreen);
      medBlue=findMed(matBlue);
      R.set(i, j, color(medRed,medGreen,medBlue));
    }
  }
  return R;
}

float findMed(float[] arr) {
  sort(arr);
  if (arr.length%2==1) return arr[arr.length/2];
  return (arr[arr.length/2]+arr[arr.length/2+1])/2;
}
