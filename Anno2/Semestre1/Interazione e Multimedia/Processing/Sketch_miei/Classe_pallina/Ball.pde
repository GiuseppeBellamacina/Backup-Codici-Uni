class Ball{
  float posX, posY, size;
  float sx, sy;
  
  Ball(float x, float y, float s, float sx, float sy){
    posX=x;
    posY=y;
    size=s;
    this.sx=sx;
    this.sy=sy;
  }
  
  Ball(float x, float y, float s){
    this(x,y,s,0,0); // è interpretato come un costruttore
  }
  
  void display(){
    fill(255,255,0);
    noStroke();
    ellipse(posX,posY,size,size);
  }
  
  void move(){
    posX+=sx;
    posY+=sy;
  }
  
  void bounce(){
    if(posY<=size/2 || posY>=height-size/2){
      sy=-sy;
    }
    if(posX<=size/2 || posX>=width-size/2){
      sx=-sx;
    }
  }
  
  void gravity(){
    sy+=0.2;
  }
  
  void run(){
    gravity();
    bounce();
    move();
    display();
  }
}
