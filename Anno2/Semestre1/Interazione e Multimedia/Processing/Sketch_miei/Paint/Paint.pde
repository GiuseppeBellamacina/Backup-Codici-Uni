void setup() {
  size(500, 500);
  background(255);
  strokeWeight(5);
}

void draw() {
  if (mousePressed) {
    line(pmouseX, pmouseY, mouseX, mouseY);
  }
}

void keyPressed(){
  if(key=='r' || key=='R') stroke(255,0,0);
  if(key=='g' || key=='G') stroke(0,255,0);
  if(key=='b' || key=='B') stroke(0,0,255);
  if(key=='n' || key=='N') stroke(0,0,0);
  if(key=='c' || key=='C') stroke(random(255),random(255),random(255));
  if(key=='e' || key=='E') setup(); // si azzera lo sketch
}
