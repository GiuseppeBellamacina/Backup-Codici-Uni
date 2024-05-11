PImage I;
float r, g=0, b=0;
color c;

void setup() {
  size(600, 600);
  I = createImage(500, 500, RGB);
  for (int y=0; y<I.height; y++) {
    for (int x=0; x<I.width; x++) {
      r = lerp(0, 255, float(x)/I.width);
      b = lerp(0, 255, float(y)/I.height);
      c = color(r,g,b);
      I.set(x,y,c); // vedi sta funzione
      // è più conveniente rispetto alla matrice
    }
  }
}

void draw() {
  image(I,0,0);
  I.set(mouseX, mouseY, color(255));
}
