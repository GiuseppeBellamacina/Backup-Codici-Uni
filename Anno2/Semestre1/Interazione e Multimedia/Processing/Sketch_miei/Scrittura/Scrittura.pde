PFont f;
int i=0;
String input="";
String [] s={"Tano è babbo", "Porcabuttano", "Mi sono rotto le palle"};
void setup(){
  size(500,500);
  f=createFont("Star Jedi",32);
  textFont(f);
  textSize(50);
  fill(255,255,0);
}

void draw(){
    background(0);
    text(s[i],0,50, width, 300);
    text(input,0,200, width, 300);
}

void mousePressed(){
  if(mouseButton==RIGHT && i<2) i++;
}

void keyPressed(){
  if(key==' ' && i>0) i--;
  else if(key=='\n') input="";
  else if(key==BACKSPACE && input.length()>0)
    input = input.substring(0,input.length()-1);
  else input+=key;
}
