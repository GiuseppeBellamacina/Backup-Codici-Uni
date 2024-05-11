int dd = 30;

void setup() {
  size(500, 500);
  noStroke();
}

void draw() {
  background(0);
  for (int d=width; d>=50; d-=dd) {
    fill(random(255), random(255), random(255));
    ellipse(width/2, height/2, d, d);
  }
  // se le metto nel draw sono altamente interattive
}

void mousePressed() {
  println("Premuto");
  noLoop();
}

void mouseReleased(){
  println("Rilasciato");
  loop();
}

void mouseClicked(){
  println("Cliccato");
}
