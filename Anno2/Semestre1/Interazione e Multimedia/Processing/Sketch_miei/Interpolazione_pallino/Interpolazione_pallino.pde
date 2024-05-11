// EASING è il nome di questo movimento decelerato

float x, y;

void setup() {
  size(500, 500);
  background(0);
  noStroke();
  //noCursor();
}

void draw() {
  //background(0); // non si puo' mettere l'alpha nel background
  fill(0,30); // si possono vedere 8 pallini (255/30=8) perchè se sommo 8 rettangoli ottengo un nero coprente
  rect(0,0,width,height);
  x=lerp(x,mouseX,0.05);
  y=lerp(y,mouseY,0.05);
  fill(255);
  ellipse(x, y, 50, 50);
}
