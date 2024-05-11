PImage I, L;
String url;

void setup(){
  size(800,800);
  url = "https://www.pngmart.com/files/13/Adventure-Time-BMO-PNG-Photos.png";
  I = loadImage(url, "png"); // così si accede alle immagini da internet
  L = I.get(0,0,200,280); // prendo un pezzo di immagine mettendo il punto di inizio (immagine) e le dimensioni
  // get con 2 parametri mi torna il contenuto in formato colore di un pixel
  I.filter(GRAY); // è un filtro sui toni di grigio
  imageMode(CENTER);
}

void draw(){
  background(255,255,0);
  image(I,width/2,height/2);
  image(L,width/2,height/2); // sistema la posizione
}
