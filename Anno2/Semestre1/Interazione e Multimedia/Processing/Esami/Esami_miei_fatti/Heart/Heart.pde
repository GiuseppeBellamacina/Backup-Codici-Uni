float q = 30349;
class Hear {
  float posX, posY;
  float sx, sy;
  boolean vt=true;

  Hear(float x, float y, float sx, float sy) {
    this.posX=x;
    this.posY=y;
    this.sx=sx;
    this.sy=sy;
  }

  void display() {
    noStroke();
    if (vt) fill(255, 0, 0);
    else fill(50);
    beginShape();
    vertex(posX, posY);
    bezierVertex(posX, posY-30, posX+65, posY-30, posX, posY+40);
    vertex(posX, posY);
    bezierVertex(posX, posY-30, posX-65, posY-30, posX, posY+40);
    endShape();
  }
  
  void movimento(){
    if(!vt){
      sx+=0.1+f(q);
    }
    posX+=sx;
    posY+=sy;
  }
  
  float f(float x){
    return (x%21)/80;
  }
  
  boolean ins(){
    if(mouseX<posX+30 && mouseX>posX-30 && mouseY<posY+30 && mouseY>posY-30) return true;
    return false;
  }
  
  void setVt(){
    if(vt) vt=!vt;
  }
}
