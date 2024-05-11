// Si usa la funzione lerp() che serve a effettuare
// l'interpolazione lineare
// lerp(vi, vf, %x) il terzo parametro va da 0 a 1 ed è la strada tra vi e vf

int x1=50;
int y1=50;
int x2=450;
int y2=400;
int q=20;

void setup(){
  size(500,500);
  line(x1,y1,x2,y2);
  strokeWeight(10);
  stroke(255,0,0);
  for(int i=0; i<=q; i++){
    float x = lerp(x1,x2,(float)i/q);
    float y = lerp(y1,y2,(float)i/q);
    point(x,y);
  }
}

void draw(){
  
}
