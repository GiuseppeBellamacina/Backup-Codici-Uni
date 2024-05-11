class Casa{
  float posX, posY;
  float velX;
  
  Casa(float x, float y, float v){
    this.posX=x;
    this.posY=y;
    this.velX=v;
  }
  
  void display(){
    stroke(255,255,0);
    strokeWeight(2);
    noFill();
    rect(posX,posY,30,30);
    triangle(posX-5,posY,posX+15,posY-15,posX+35,posY);
  }
  
  void movimento(){
    posX+=velX;
    if(posX+35>=width || posX-5<=0) velX=-velX;
  }
  
  void run(){
    display();
    movimento();
  }
}
