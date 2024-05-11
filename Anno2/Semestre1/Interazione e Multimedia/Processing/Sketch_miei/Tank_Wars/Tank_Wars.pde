Tank t;

void setup() {
  noStroke();
  size(800, 800);
  t = new Tank(20, 30, 5);
  cursor(CROSS);
}

void draw() {
  background(0);
  t.run();
}

void keyPressed() {
}
