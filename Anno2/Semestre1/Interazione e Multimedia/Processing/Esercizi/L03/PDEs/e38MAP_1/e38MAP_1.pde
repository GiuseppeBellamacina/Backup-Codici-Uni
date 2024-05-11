//MAPPATURA DEI VALORI
//scala dei colori fino a 255
//scala posizioni che ad seconda della finestra è ad es 800

//si può fare con una proprorzione es: 400:800=x:255
//diventa x=(400*255)/800
//per fare il cambiamento di range processing ci da la funzione MAP
//MAP(valore,inizioRangeValore,fineRangeValore,inizioRangeObiettivo,fineRangeObiettivo)

void setup(){
  size(700,500);
  background(100);
}

void draw(){
  background(0);
  float x= map(mouseX, 0,width,1,255);
  fill(255,x,0);
  ellipse(255,250,x,x);
}
