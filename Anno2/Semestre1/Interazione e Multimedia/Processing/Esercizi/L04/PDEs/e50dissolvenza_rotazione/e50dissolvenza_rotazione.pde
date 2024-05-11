float rotAngle = 10;//angle of rotation

void setup(){
size(600,600);//window size

}

void draw(){
  frameRate(10);
  fill(255,50);//            semi-transparent
  rect(0,0,width,height);//   background
  translate(width/2,height/2);//move grid to center
  
  
  rotate(radians(rotAngle));//rotate the grid clockwise
  noStroke();
  fill(255,0,0);//red
  ellipse(250,0,20,20);
  rotAngle += 20;

}
