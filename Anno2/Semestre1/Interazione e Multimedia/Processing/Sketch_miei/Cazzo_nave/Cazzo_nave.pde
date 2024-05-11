void setup() {
  size(500, 700);
  noCursor();
}

int x=-10, y=-10;
int points=0;

void draw() {
  background(0);
  fill(255);
  ellipse(mouseX, mouseY-50, 50, 150);
  ellipse(mouseX-40, mouseY, 50, 50);
  ellipse(mouseX+40, mouseY, 50, 50);
  fill(255,0,0);
  ellipse(250,100,20,20);

  if (keyPressed) {
    if (key == ' ') {
      x=mouseX;
      y=mouseY-125;
    }
  }
  fill(255);
  ellipse(x, y, 10, 10);
  y-=10;
  
  if(dist(x,y,250,100)<10){
    points++;
    println("Punteggio: "+points);
  }
}
