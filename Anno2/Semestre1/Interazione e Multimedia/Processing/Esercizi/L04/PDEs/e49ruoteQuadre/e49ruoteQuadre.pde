int x=0;
void setup(){
  size(500,500);
  rectMode(CENTER);
}
void draw(){
  //background(255);
  pushMatrix();
  translate(x+300,200); 
  rotate(frameCount%360);
  fill(0,255,0);
  rect(0,0,40,40);
  popMatrix();
  pushMatrix();
  translate(x+100,200);
  rotate(frameCount%360);
  fill(0,0,255);
  rect(0,0,40,40);
  popMatrix();
  x++;
}
