//Esempio curva di bezier con punti di controllo disegnati e interattivi

float P1x;
float P1y;

float P2x;
float P2y;

float P3x;
float P3y;

float P4x;
float P4y;


void setup()
{
 size(600,600);
 background(0);
 ellipseMode(CENTER);
 frameRate(60);
 
 P1x=150;
 P1y=250;
 
 P2x=130;
 P2y=350;
 
 P3x=450;
 P3y=350;
 
 P4x=420;
 P4y=250;
}


void draw()
{
  
  if ((mousePressed)&&(dist(pmouseX,pmouseY,P1x,P1y)<4))
    {
      P1x=mouseX;
      P1y=mouseY;
    }
   else if ((mousePressed)&&(dist(pmouseX,pmouseY,P2x,P2y)<4))
    {
      P2x=mouseX;
      P2y=mouseY;
    }
  else if ((mousePressed)&&(dist(pmouseX,pmouseY,P3x,P3y)<6))
    {
      P3x=mouseX;
      P3y=mouseY;
    }
  else if ((mousePressed)&&(dist(pmouseX,pmouseY,P4x,P4y)<6))
    {
      P4x=mouseX;
      P4y=mouseY;
    }
  
  //Cancella
  background(0);
  
  //Curva
  strokeWeight(3);
  stroke(255);
  noFill();
  bezier(P1x,P1y,P2x,P2y,P3x,P3y,P4x,P4y);
  
  // Punti
  noStroke();
  fill(255,0,0);
  ellipse(P1x,P1y,6,6);
  fill(0,0,255);
  ellipse(P2x,P2y,6,6);
  fill(0,255,255);
  ellipse(P3x,P3y,6,6);
  fill(255,255,0);
  ellipse(P4x,P4y,6,6);
  
  //Linee
  strokeWeight(1);
  stroke(128,128,128);
  line(P1x,P1y,P2x,P2y);
  line(P2x,P2y,P3x,P3y);
  line(P3x,P3y,P4x,P4y);
}
