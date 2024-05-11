int q=20;
int d;

void setup(){
  size(500,500);
  d=width/q;
  noStroke();
  noLoop();
}

void draw(){
  background(0);
  for(int y=0; y<=height; y+=d){
    for(int x=0; x<=width; x+=d){
      if(x<width/2 && y<height/2)
        fill(255,0,0);
      else if(x>width/2 && y<height/2)
        fill(0,0,255);
      else if(x>width/2 && y>height/2)
        fill(255,255,0);
      fill(random(255),130);
      rect(x+random(-5,5),y+random(-5,5),d,d);
    }
  }
}
