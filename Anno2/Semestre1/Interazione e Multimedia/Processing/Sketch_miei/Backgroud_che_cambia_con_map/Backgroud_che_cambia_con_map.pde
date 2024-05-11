// map(cosa,StartIn,EndIn,StartOut,EnOut)
// serve a mappare
// in pratica modula i valori in un certo range in proporzione

int d=50;

void setup() {
  size(500, 500);
}

void draw() {
  background(map(mouseX,0,width,0,255),map(mouseY,0,height,0,255),0);
  fill(0, 0, 0);
  ellipse(width/2, height/2, d, d);
}
