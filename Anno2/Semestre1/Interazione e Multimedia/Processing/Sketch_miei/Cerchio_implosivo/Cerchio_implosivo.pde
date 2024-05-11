// map(cosa,StartIn,EndIn,StartOut,EnOut)
// serve a mappare

int d=50;

void setup() {
  size(500, 500);
}

void draw() {
  background(255);
  fill(map(d,50,width,0,255), 0, 0);
  ellipse(width/2, height/2, d, d);
  if (dist(mouseX, mouseY, width/2, height/2)<d/2) {
    d+=3;
  } else if (d>50)
    d-=3; // ATTENZIONE: se il diametro è negativo implode e ricresce dopo
}
