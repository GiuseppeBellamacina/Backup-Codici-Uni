PImage im;

void setup(){
  size(600,600);
  im = loadImage("Lenna.png");
  println("Width: " + im.width);
  println("Height: " + im.height);
}

void draw(){
  background(0);
  image(im,0,0);
  // saveFrame("anim\\lena-###.png"); // i # servono a definire i numeri dei frames
  // poi si può usare Movie Maker per i video
}

void mousePressed(){
  im.resize(im.width/2, im.height/2); // serve a ridimensionare l'immagine
}

void keyTyped(){
  if(key == 's'){
    // println(savePath("data\\LennaPiccola.png")); // stampa il path dove viene salvato
    im.save(savePath("data\\LennaPiccola.png")); // serve a salvare nella cartella "data"
    // la funzione di save effettua anche le conversioni png, jpg, gif...
  }
  if(key == 'c'){
    saveFrame("canvas.png");
  }
}
