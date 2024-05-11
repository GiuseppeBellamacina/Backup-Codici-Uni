/*
  Gli angoli si misurano in radianti
  ci sono delle costanti come PI, HALF_PI...  
  0 è a destra e si gira in senso orario
------------------------------------------------------
  Si puo' mettere un ulteriore parametro sulle
  figure geometriche per ottenere una smussatura degli
  angoli e si puo' specificare per ogni angolo
*/

int x;
int o=90;
int v=5; // la velocità si misura in pixel/frame
int dir=1;
int a=30;
int va=2;
int dira=-1;
void setup(){
  //fullScreen();
  size(1200,500);
  x=75;
  noStroke();
  //noLoop();
}

void draw(){
  background(0);
  if(dir>0){
    fill(255,255,0);
    arc(x,height/2,150,150,radians(a),radians(360-a));
    // ha modalità di chiusura PIE (default), CHORD, OPEN
    fill(36,229,234);
    ellipse(o,height/2-40,20,20);
  }
  else{
    fill(255,255,0);
    arc(x,height/2,150,150,radians(180+a),radians(540-a));
    fill(36,229,234);
    ellipse(o,height/2-40,20,20);
  }
  if(x<75 | x>=width-75)
    dir=-dir;
  if(a>30 || a<=0)
    dira=-dira;
  x+=v*dir;
  o+=v*dir;
  a+=va*dira;
}
