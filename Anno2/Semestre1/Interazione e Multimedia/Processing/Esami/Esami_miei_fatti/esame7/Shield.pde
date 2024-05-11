class Shield{
  float posX, posY;
  float sx;
  
  Shield(float x, float y, float v){
    this.posX=x;
    this.posY=y;
    this.sx=v;
  }
  
  void display(){
    noStroke();
    fill(0,255,0);
    triangle(posX,posY,posX+25,posY-50,posX+50,posY);
  }
  
  void movimento(){
    posX+=sx;
    if(posX>width) posX=-50;
    if(posX+50<0) posX=width;
  }
  
  void run(){
    display();
    movimento();
  }
}
