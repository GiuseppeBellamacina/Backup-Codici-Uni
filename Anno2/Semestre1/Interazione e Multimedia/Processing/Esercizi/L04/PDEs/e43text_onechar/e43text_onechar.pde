//QUALSIASI TASTO DELLA TASTIERA


void setup(){
  size(120,120);
  //quanto sarà grande e allineamento testo
  textSize(64);
  textAlign(CENTER);
}

void draw (){
  background(0);
  text(key, 60,80); //key è una variabile CHAR che contiene il carattere del tasto premuto
  
  }