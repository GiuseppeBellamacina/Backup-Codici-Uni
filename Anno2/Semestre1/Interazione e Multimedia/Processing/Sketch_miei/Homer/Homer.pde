int d=100, x1, x2, y;
color c=color(255, 255, 0);
float dx1, dx2, dy;
PImage donut, homer;
int dim=200;
int dnx, dny=-dim, v;
boolean dn=false;

void setup() {
  donut=loadImage("donut.png");
  homer=loadImage("homer.png");
  //size(600, 600);
  fullScreen();
  x1=width/2-30;
  x2=width/2+50;
  y=height/2;
  //smooth();
}

void draw() {
  background(c);
  //image(homer,650,350,665,821);
  fill(255);
  ellipse(x1, y-5, d, d);
  ellipse(x2, y, d, d);
  fill(0);

  if (dn) {
    dny+=7;
    dnx+=v;
    if (dnx+dim/2<=x1) {
      dx1=map(dnx+dim/2, 0, x1, -25, 0);
      dx2=dx1;
    } else if (dnx+dim/2>x1 && dnx+dim/2<=width/2) {
      dx1=map(dnx+dim/2, x1+1, width/2, 0, 25);
      dx2=-dx1;
    } else if (dnx+dim/2>width/2 && dnx+dim/2<=x2) {
      dx2=map(dnx+dim/2, width/2+1, x2, -25, 0);
      dx1=-dx2;
    } else { // dnx+dim/2>=x2
      dx2=map(dnx+dim/2, x2, width, 0, 25);
      dx1=dx2;
    }
    dy=map(dny+dim/2, 0, height, -25, 25);
    if (dny>height || dnx>width || dnx<-dim) dn=false;
  } else {
    if (mouseX<=x1) {
      dx1=map(mouseX, 0, x1, -25, 0);
      dx2=dx1;
    } else if (mouseX>x1 && mouseX<=width/2) {
      dx1=map(mouseX, x1+1, width/2, 0, 25);
      dx2=-dx1;
    } else if (mouseX>width/2 && mouseX<=x2) {
      dx2=map(mouseX, width/2+1, x2, -25, 0);
      dx1=-dx2;
    } else { // mouseX>=x2
      dx2=map(mouseX, x2, width, 0, 25);
      dx1=dx2;
    }
    dy=map(mouseY, 0, height, -25, 25);
  }

  ellipse(x1+dx1, y+dy, 10, 10);
  ellipse(x2+dx2, y+dy, 10, 10);
  image(donut, dnx, dny, dim, dim);
}

void mousePressed() {
  dny=-dim;
  dnx=(int)random(0, width-dim);
  v=(int)random(-10, 10);
  dn=true;
}
