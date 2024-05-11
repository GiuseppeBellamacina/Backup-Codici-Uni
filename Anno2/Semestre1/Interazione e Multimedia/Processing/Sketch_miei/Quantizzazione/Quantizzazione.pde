// QUANTIZZAZIONE
PImage Im, Iq;
int k=2;

void setup() {
  Im=loadImage("Lenna.png");
  Im.filter(GRAY);
  size(1024, 512);
  image(Im, 0, 0);

  Iq=quant(Im, k);
  image(Iq, 512, 0);
}

void draw() {
  
}

PImage quant(PImage I, int kk) {
  PImage R=I.copy();
  R.loadPixels();

  int q;
  // si usa un for se non ci interessa la posizione del pixel, come per le operazioni puntuali
  // si usano 2 for per le operazioni locali in cui ci interessa la posizione dei pixels
  for (int i=0; i<R.pixels.length; i++) { // uso un for sulla matrice linearizzata
    q=floor(red(R.pixels[i])*kk/256); // prendo il red ma è uguale perchè la foto è i scala di grigi, rgb sono uguali
    q=int(float(q)/(kk-1)*255);
    // q=int(lerp(0,255,float(q)/(kk-1)); è equivalente
    
    R.pixels[i]=color(q);
  }

  R.updatePixels();
  return R;
}

void keyPressed(){
  if(key=='+' && k<256)
    k++;
  if(key=='-' && k>2)
    k--;
  println(k);
  setup();
}
