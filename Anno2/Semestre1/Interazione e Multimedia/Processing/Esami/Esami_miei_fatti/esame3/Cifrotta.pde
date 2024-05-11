class Cifrotta extends Cifra {
  Cifrotta(float x, float y, float v, String n) {
    super(x, y, v, n);
  }

  void display() {
    textSize(32);
    fill(255);
    text(num, posX, posY);
    noFill();
    stroke(255);
    strokeWeight(2);
    ellipse(posX+8, posY-10, 32, 32);
  }

  void movimento() {
    posY-=velY;
    if (posY<0) {
      posY=height;
      posX=random(0, width-32);
    }
  }
}
