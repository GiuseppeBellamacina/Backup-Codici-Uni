class Casetta extends Casa{
  Casetta(float x, float y, float v){
    super(x,y,v);
  }
  
  void display(){
    stroke(255);
    strokeWeight(2);
    noFill();
    rect(posX,posY,30,30);
    triangle(posX-5,posY,posX+15,posY-15,posX+35,posY);
    fill(255);
    rect(posX+10,posY+20,10,10);
  }
  
  void movimento(){
    posX-=velX;
    if(posX+35<=0) posX=width;
  }
}
