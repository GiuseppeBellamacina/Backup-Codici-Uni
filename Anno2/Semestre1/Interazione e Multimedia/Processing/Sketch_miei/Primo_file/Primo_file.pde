int d = 300;
size(1000,500); // creo una canvas rettangolare di dimensioni date
background(255); // funziona con i valori RGB, se metto un valore va in scala di grigi (replica il valore)
// circle(250,250,500); // x,y del centro e poi il raggio
fill(255,0,0); // per colorare
ellipse(width/2,height/2,width,height); // come circle ma si devono mettere i 2 assi
ellipseMode(CORNERS); // varie modalità 0,1,2,3
/*
  0) CORNER (si sposta l'angolo in alto a sinistra (x,y,d1,d2))
  1) CORNERS (riempie dall'angolo in alto a sinistra fino a in basso a destra (x1,y1,x2,y2))
  2) RADIUS (prima il centro e poi i raggi (x,y,r1,r2))
  3) CENTER (default (x,y,d1,d2))
*/
// fill(#B416D8,100); // il quarto parametro è l'opacità
// noFill(); // senza riempimento
stroke(0,255,0,100); // per il contorno
strokeWeight(10); // per lo spessore del contorno
// ellipse(0,250,500,500);
// In Processing (derivato da Java) ci sono vari tipi: int, float, double, char, string
