void setup(){
  size(240,120);
}
//ALL'AUMENTARE DEL MOUSEX(VERSO DX) MOLTO DISORDINE
void draw(){
  background(200);
  //METTIAMO CICLO FOR PER FARE 20 LINEE OGNI VOLTA CHE ENTRA NEL DRAW(60 VOLTE)
  for (int x=20; x<width; x+=20){
    println(mouseX);
    //RUMORE DEVE DIPENDERE DA X
    float rum=mouseX/10;
    float rumi= random(-rum,+rum);
    float rumf= random(-rum,+rum);
    line (x+rumi,20,x+rumf,100);
  }
  //println(random(mouseX));
}
//NUMERI RANDOM QUANDO VALORI BASSI x

//QUANDO MOUSE 0 FA 20 LINEE ORDINATE