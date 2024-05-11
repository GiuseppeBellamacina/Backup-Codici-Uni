int q=20;
int d;

void setup(){
  size(500,500);
  d=width/q;
  noStroke();
  noLoop();
}

void draw(){
  background(0,255,0);
  for(int y=0; y<=height; y+=d){
    for(int x=0; x<=width; x+=d){
      fill(random(255),130);
      rect(x+random(-5,5),y+random(-5,5),d,d);
    }
  }
}
