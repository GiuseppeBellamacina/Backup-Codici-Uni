float shX,shY;
float scale;
void setup()
{
  background(255);  
  fill(0,255,0);
  stroke(255,0,0);
  strokeWeight(5);
  rectMode(CENTER);
  size(500,500);
  shX=0.1;
  shY=0.1;
  scale=0.2;
}

void draw()
{
  background(255);
  pushMatrix();
  translate(150,250);
  shearX(shX);
  shearY(shY);
  //scale(scale);
  rect(0,0,50,50);
  popMatrix(); 

  shX+=0.01;
  shY+=0.01;
  //scale+=0.1;
}
