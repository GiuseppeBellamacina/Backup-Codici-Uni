//MAPPATURA DEI VALORI

void setup(){
  size(500,500);
  
}

void draw(){
  float x= map(mouseX, 0,width,150,250);
  float y= map(mouseY, 0,height,100,200);
  ellipse(x,y,40,40);
}
