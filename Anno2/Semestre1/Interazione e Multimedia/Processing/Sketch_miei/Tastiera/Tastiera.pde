int dd = 30, x,y;

void setup() {
  size(500, 500);
  x=width/2;
  y=height/2;
  noStroke();
}

void draw() {
  background(0);
  for (int d=width; d>=50; d-=dd) {
    fill(random(255), random(255), random(255));
    ellipse(x, y, d, d);
  }
  if (keyPressed && key==CODED) {
    if (keyCode==LEFT) x-=3;
    if (keyCode==RIGHT) x+=3;
    if (keyCode==UP) y-=3;
    if (keyCode==DOWN) y+=3;
  }
}

void keyPressed() {
  println("Premuto il tasto " + key);
}

void keyReleased() {
  println("Rilasciato il tasto " + key);
}

void keyTyped() {
  println("Digitata la lettera " + key);
}
