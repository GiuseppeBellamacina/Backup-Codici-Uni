int q = 100;
size(500,500);
colorMode(RGB,width);
background(width);
noStroke();
int d = width/q;
for(int y=0; y<=height; y+=d){
  for(int x=0; x<=width; x+=d){
    fill(x,y,width);
    rect(x,y,d,d);
  }
}
