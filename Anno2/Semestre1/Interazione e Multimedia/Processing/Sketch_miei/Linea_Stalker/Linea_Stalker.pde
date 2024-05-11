
ConstLenLine lin;
void setup() {
  size(640, 480, P2D);
  background(250);
  stroke(0);
  smooth();
  lin = new ConstLenLine();
}
void draw() {
  background(250);
  lin.update();
  lin.draw();
}
class ConstLenLine {
  float len = 50; // length of the line
  PVector A, B, eq;
  ConstLenLine() {
    A = new PVector(mouseX, mouseY);
    B = new PVector(A.x, A.y+len);
    eq = new PVector(0, 0);
  }
  void update() {
    A = new PVector(mouseX, mouseY);
    if (round(A.dist(B))>len)
      eq.add(PVector.sub(A, B));
    if (round(A.dist(B))<len)
      eq.sub(PVector.sub(A, B));
    eq.normalize();
    int count=0;
    while (round (A.dist (B)) != len) {
      //how to do it without this lame loop, just with computing
      B.add(eq);
      if (count>1000)
        break; // just for sure, I don't like infinite loops
      count++;
    }
  }
  void draw() {
    pushStyle();
    strokeWeight(len/20);
    line(A.x, A.y, B.x, B.y);
    popStyle();
  }
}
