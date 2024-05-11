int d=50, x1, x2, y;
color c=color(255, 255, 0);
int w=60, h=30;
int xr, yr;

void setup() {
  size(500, 500);
  x1=width/2-30;
  x2=width/2+30;
  y=height/2;
  xr=(int)random(0, width-w);
  yr=(int)random(0, height-h);
}

void draw() {
  background(c);
  fill(255);
  ellipse(x1, y, d, d);
  ellipse(x2, y, d, d);
  fill(0);
  float dx=map(mouseX, 0, width, -15, 15);
  float dy=map(mouseY, 0, height, -15, 15);
  ellipse(x1+dx, y+dy, 5, 5);
  ellipse(x2+dx, y+dy, 5, 5);
  fill(255);
  rect(xr, yr, w, h);
}

void mousePressed() {
  if (mouseX>xr && mouseX<xr+w && mouseY>yr && mouseY<yr+h) {
    c=color(random(255), random(255), random(255));
    xr=(int)random(0, width-w);
    yr=(int)random(0, height-h);
  }
}
