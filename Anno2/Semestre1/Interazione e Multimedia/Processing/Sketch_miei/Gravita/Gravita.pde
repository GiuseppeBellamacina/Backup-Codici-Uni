int l=100;
int a=0;
int y=100;
float v=0;
float g=0.2;
float shX=0.1;

void setup() {
  size(500, 500);
  noStroke();
  rectMode(CENTER);
}

void draw() {
  background(0);
  pushMatrix();
  translate(width/2-100, height/2); // sposta l'origine
  shearX(shX); // effettua una shear
  //scale(shX,2); // cambia le proporzioni
  //rotate(radians(millis()/100)); // ha (0,0) come perno
  fill(255);
  rect(0, 0, l, l);
  popMatrix();
  pushMatrix();
  translate(width/2+100, height/2);
  rotate(radians(millis()/10));
  rect(0, 0, l, l);
  popMatrix();
  rect(width/2, y, 20, 20);
  y+=v;
  v+=g;
  if(y>=height){
    v*=-0.5;
    y=height;
  }
  a+=2;
  shX+=0.01;
  // l+=1 è equivalente ad usare lo scale
}
