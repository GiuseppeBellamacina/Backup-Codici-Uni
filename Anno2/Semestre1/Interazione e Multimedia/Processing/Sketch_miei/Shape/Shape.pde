int y;

void setup(){
  size(500,500);
  noStroke();
}

void draw(){
  background(0);
  
  beginShape();
  fill(255,0,0);
  vertex(180,y+82);
  vertex(207,y+36);
  vertex(214,y+63);
  vertex(407,y+11);
  vertex(412,y+30);
  vertex(219,y+82);
  vertex(226,y+109);
  endShape(CLOSE);
  y++;
}
