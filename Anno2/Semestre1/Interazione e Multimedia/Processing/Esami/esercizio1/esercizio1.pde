ArrayList<Casa> arr;
Casa c;
void setup(){
  size(500,500);
  background(0);
  arr = new ArrayList<Casa>();
  c = new Casa(50,50,2);
}

void draw(){
  background(0);
  for (Casa c : arr) c.run();
}

void mousePressed(){
  if(mouseButton==LEFT) arr.add(new Casa(random(5,width-5),random(15,height-30),random(2,20)));
  if(mouseButton==RIGHT) arr.add(new Casetta(random(5,width-5),random(15,height-30),random(2,20)));
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
