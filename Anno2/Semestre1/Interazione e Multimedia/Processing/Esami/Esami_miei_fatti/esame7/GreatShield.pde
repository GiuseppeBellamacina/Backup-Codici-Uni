class GreatShield extends Shield {
  float scale=0.5;
  float ds=0.05;

  GreatShield(float x, float y, float v) {
    super(x, y, v);
  }

  void display() {
    stroke(255,255,0);
    strokeWeight(5);
    fill(255, 0, 0);
    triangle(posX, posY, posX+25*scale, posY-50*scale, posX+50*scale, posY);
  }

  void movimento() {
    posX+=sx;
    scale+=ds;
    println(scale);
    if(scale>2.0 || scale<0.5) ds=-ds;
    if (posX>width) posX=-50*scale;
    if (posX+50*scale<0) posX=width;
  }
}
