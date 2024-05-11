PImage I;
float r,g,b;
color c;
int ar;

void setup(){
  I = loadImage("Lenna.png");
  size(512,512);
  I.loadPixels(); // creo una matrice linearizzata
  for(int i=0; i<I.width; i++){
    I.pixels[pos(i,i,I.width)] = color(255,255,0); // sto modificando l'immagine
  }
  I.updatePixels(); // si salva il nuovo stato dei pixels, perchè la matrice è pesante
}

void draw(){
  image(I,0,0);
}

void keyTyped(){
  if(key == 'r')
    ar--;
  else if(key == 'R')
    ar++;
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    c = I.pixels[i];
    r = red(c);
    g = green(c);
    b = blue(c);
    c = color(r+ar,g,b);
    I.pixels[i] = c; // così si sfasciano i colori perchè partono da valori diffrenti
  }
  I.updatePixels();
  println(ar);
}

int pos(int x, int y, int w){
  return x+y*w;
}
