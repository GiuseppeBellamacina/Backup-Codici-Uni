class Cifra{
  float posX, posY;
  float velY;
  String num;
  
  Cifra(float x, float y, float v, String n){
    this.posX=x;
    this.posY=y;
    this.velY=v;
    this.num=n;
  }
  
  void display(){
    textSize(32);
    fill(255,255,0);
    text(num,posX,posY);
  }
  
  void movimento(){
    posY+=velY;
    if(posY>height){
      posY=0;
      posX=random(0,width-32);
    }
  }
  
  void run(){
    display();
    movimento();
  }
}
