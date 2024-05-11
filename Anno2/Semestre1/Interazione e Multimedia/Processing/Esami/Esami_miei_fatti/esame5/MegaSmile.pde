class MegaSmile extends Smile{
  MegaSmile(float x, float y, float v){
    super(x,y,v);
  }
  
  void display(){
    noFill();
    stroke(255);
    strokeWeight(2);
    pushMatrix();
    scale(1.5);
    ellipse(posX,posY,50,50);
    line(posX-15,posY+10,posX+15,posY+10);
    line(posX-5,posY-5,posX-5,posY-15);
    line(posX+5,posY-5,posX+5,posY-15);
    popMatrix();
  }
  
  void movimento(){
    posX+=velX;
    if(posX+25<=0) posX=width+25;
  }
}
