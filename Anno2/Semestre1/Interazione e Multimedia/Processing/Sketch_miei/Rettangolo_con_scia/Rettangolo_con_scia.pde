int l=100;
int a=0;

void setup() {
  background(0);
  size(500, 500);
  noStroke();
}

void draw() {
  fill(0,25);
  rect(0,0,width,height);
  translate(width/2-l/2, height/2-l/2); // sposta l'origine
  rotate(radians(a)); // ha (0,0) come perno
  stroke(255,0,0);
  strokeWeight(2);
  fill(255);
  rect(0, 0, l, l);
  noStroke();
  a++;
}
