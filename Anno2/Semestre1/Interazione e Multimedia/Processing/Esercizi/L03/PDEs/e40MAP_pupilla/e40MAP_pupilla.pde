//MAPPATURA DEI VALORI
//scala dei colori fino a 255
//scala posizioni che ad seconda della finestra è ad es 800

//si può fare con una proprorzione es: 400:800=x:255
//diventa x=(400*255)/800=127,5
//per fare il cambiamento di range processing ci da la funzione MAP
//MAP(valore,inizioRangeValore,fineRangeValore,inizioRangeObiettivo,fineRangeObiettivo)
//valore che vuoi trasformare, che va da 0 a 800 e voglio trasformarlo in modo che vada da 0 a 255
//è una funzione che restituisce un numero

void setup(){
  size(500,500);
  
}

void draw(){
  background(100);
  fill(255);
  ellipse(width/2,height/2,50,50);
  float x= map(mouseX, 0,width,-15,15);
  float y= map(mouseY, 0,height,-15,15);
  fill(0);
  ellipse(x+width/2,y+height/2,5,5);
}