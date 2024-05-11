void setup(){
  size(500,500);
}

void draw(){
  background(255,255,0);
  strokeWeight(1);
  stroke(0);
  fill(255,255,0);
  bezier(50,height/2,100,100,mouseX,mouseY,450,height/2);
  stroke(0,0,255);
  strokeWeight(2);
  line(50,height/2,100,100);
  line(mouseX,mouseY,450,height/2);
  stroke(255,0,0);
  strokeWeight(10);
  point(50,height/2);
  point(450,height/2);
  stroke(0,255,0);
  point(100,100);
  point(mouseX,mouseY);
}
