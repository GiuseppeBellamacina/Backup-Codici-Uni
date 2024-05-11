PImage i;
color c;
int x, y;

void setup() {
  size(500, 500);
  i = loadImage("Lenna.png");
  i.resize(200, 200);
  c = color(0);
  x = width/2 - i.width/2;
  y = height/2 - i.height/2;
}

void draw() {
  background(c);
  image(i, x, y);
  c = i.get(mouseX-x, mouseY-y);
  println("R: " + red(c) + " -- G: " + green(c) + " -- B: " + blue(c));
  // queste funzioni restituiscono le componenti RGB
}
