class Smile{
  float posX, posY;
  float velX;

  Smile(float x, float y, float v){
    this.posX=x;
    this.posY=y;
    this.velX=v;
  }
  
  void display(){
    noFill();
    stroke(255,255,0);
    strokeWeight(2);
    ellipse(posX,posY,50,50);
    line(posX-15,posY+10,posX+15,posY+10);
    line(posX-5,posY-5,posX-5,posY-15);
    line(posX+5,posY-5,posX+5,posY-15);
  }
  
  void movimento(){
    posX+=velX;
    if(posX+25>=width || posX-25<=0)
      velX=-velX;
  }
  
  void run(){
    display();
    movimento();
  }
}
