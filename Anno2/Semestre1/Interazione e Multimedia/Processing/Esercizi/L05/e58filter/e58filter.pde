PImage I;
String url="https://i.pinimg.com/originals/e7/5f/46/e75f4650c2ff00c9317860782391be82.jpg";
int g=0;
void settings(){
  I=loadImage(url);
  size(I.width,I.height);
}
void draw(){
  image(I,0,0);
}

void keyTyped(){
  if (key=='+'){
    g++;
    I.filter(BLUR, g);
    println("Blur: "+g);
  }
  if (key=='r' || key=='R'){
    I=loadImage(url);
    g=0;
  }
  
}
  
