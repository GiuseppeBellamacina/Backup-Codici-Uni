PImage im;
void setup(){
  size(600,600);
  im=loadImage("lena.png");
  println("Larghezza: "+im.width);
  println("Altezza: "+im.height);
}
void draw(){
  background(0);
  image(im,0,0);
}

void mousePressed(){
  im.resize(im.width/2,im.height/2);
}

void keyTyped(){
  if (key=='s' || key=='S'){
    println(savePath("lenaPiccola.png"));
    im.save(savePath("lenaPiccola.png"));
  }
  if (key=='c' || key=='C'){
    println("Salvo la canvas...");
    saveFrame("lenaCanvas.png");
  }
}
