size(250,250);
background(0);
smooth();
noStroke();
fill(255,0,0);
beginShape();
scale(2);
vertex(50, 15);
bezierVertex(50, -5, 90, 5, 50, 40);
vertex(50, 15);
bezierVertex(50, -5, 10, 5, 50, 40);
endShape();
strokeWeight(2);
stroke(255);
point(90,5);
point(10,5);
