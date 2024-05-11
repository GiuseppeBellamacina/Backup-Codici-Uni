void setup(){
  size(500,500);
 
  rectMode(CENTER);
  
}

void draw(){
  translate(width/2,height/2);
  rotate(radians(frameCount%360));
  
  translate(50,50);
  rotate(radians(frameCount*10%360));
  
  fill(frameCount * 3 % 255, frameCount * 5 % 255,
      frameCount * 7 % 255);
  rect(0,0,100,100);
 
  
}