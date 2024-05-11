int q=10;
int d;

void setup(){
  size(500,500);
  d=width/q;
  noStroke();
  colorMode(RGB,width);
}

void draw(){
  background(width);
  for(int y=d/2; y<=height; y+=d){
    for(int x=d/2; x<=width; x+=d){
      if(dist(x,y,mouseX,mouseY)<d/2)
        fill(x,y,width);
      else
        fill(x,y,0);
      ellipse(x,y,d,d);
    }
  }
}
