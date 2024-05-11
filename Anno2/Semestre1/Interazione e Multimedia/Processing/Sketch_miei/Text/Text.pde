PFont f;
String [] s={"Tano è babbo", "Porcabuttano", "Mi sono rotto le palle"};
// posso anche usare Crea Font nei Tools e allega il font al progetto, nel caso in cui si utilizzino font personalizzati
void setup(){
  size(500,500);
  background(0);
  println(PFont.list()); // lista font
  f=createFont("Star Jedi",32);
  //textSize(50);
  textFont(f); // renderizza il font
  fill(255,255,0); // con fill si cambia il colore
  text("Tano conti ha il covid",0,50, width, 300); // il colore di default è il bianco che è lo stesso del fill
  // dopo il testo i parametri sono il punto di inizio del testo, ci sono anche le dimensioni del rettangolo, infatti
  // il testo è inserito in un rettangolo con un po' di padding (spaziatura) ai margini
}

void draw(){}
