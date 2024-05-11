size(300,500);
background(0);
stroke(0,255,0);
strokeWeight(2);
line(0,0,width,height); // crea una linea da punto a punto
line(width,0,0,height);
strokeWeight(30);
stroke(0,0,255);
point(width/2,height/2); // crea un punto
// rectMode();
/*
  CORNER (default)
  CENTER
  CORNERS
*/
rect(0,height/2,width,height/2); // coordinate dell'angolo in alto a sinistra, larghezza e altezza
// quad(...); // per i quadrilateri
noStroke();
fill(100);
triangle(width/2,0,width,height,0,height); // per i triangoli
