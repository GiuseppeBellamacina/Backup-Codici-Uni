// setup e draw sono 2 funzioni vuote di cui si deve eseguire l'overloading
int i=0;
void setup(){
  println("Sono nel setup");
  frameRate(1); // modifico il frameRate
}

void draw(){ // è un ciclo infinito chiamato 60 volte al secondo di deafult
 println("Sono nel draw, e sono al frame " + frameCount);
}
// millis() sono i millisecondi passati
