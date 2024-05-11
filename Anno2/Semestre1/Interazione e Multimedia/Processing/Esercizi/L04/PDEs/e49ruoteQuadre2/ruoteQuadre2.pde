int a=0;
int x=0;
void setup(){
  size(500,500);
  rectMode(CENTER);
}

void draw(){
  background(0);
  fill(255);
  pushMatrix();
  translate(x,100);
  rotate(millis()/1000.0*TWO_PI);
  rect(0,0,50,50);
  popMatrix();
  
  pushMatrix();
  translate(x+150,100);
  rotate(millis()/1000.0*-TWO_PI);
  fill(255,255,0);
  rect(0,0,50,50);
  popMatrix();
  x++;
  
}
