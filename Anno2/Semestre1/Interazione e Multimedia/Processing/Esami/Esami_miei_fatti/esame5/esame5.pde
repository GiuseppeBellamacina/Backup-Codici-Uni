ArrayList<Smile> arr;

void setup(){
  size(500,500);
  background(0);
  arr = new ArrayList<Smile>();
}

void draw(){
  background(0);
  for (Smile s : arr) s.run();
}

void mousePressed(){
  if(mouseButton==LEFT)
    arr.add(new Smile(random(40,width-40),random(40,height-40),random(2,10)));
  else if(mouseButton==RIGHT){
    arr.add(new MegaSmile(random(40,width-40),random(40,height-40),-random(2,10)));
  }
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
}
