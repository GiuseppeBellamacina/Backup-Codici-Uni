ArrayList<Cifra> arr;

void setup(){
  size(500,500);
  arr = new ArrayList<Cifra>();
  background(0);
}

void draw(){
  background(0);
  for (Cifra c : arr) c.run();
}

void keyPressed(){
  if(key>='0' && key<='4')
    arr.add(new Cifra(random(0, width-32),random(0,height-32),random(2,10),str(key)));
  else if(key>='5' && key<='9')
    arr.add(new Cifrotta(random(0, width-32),random(0,height-32),random(2,10),str(key)));
}

void mousePressed(){
  if(mouseButton==RIGHT) setup();
}
