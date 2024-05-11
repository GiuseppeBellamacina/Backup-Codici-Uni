ArrayList<Shield> arr;

void setup(){
  size(512,512);
  background(0);
  arr = new ArrayList<Shield>();
}

void draw(){
  background(0);
  for (Shield s : arr) s.run();
}

void keyPressed(){
  if(key=='r' || key=='R') setup();
  if(key=='s' || key=='S'){
    arr.add(new Shield(random(0,width-50),random(50,height/2),random(-5,5)));
    arr.add(new GreatShield(random(0,width-50),random(height/2+50,height),random(-5,5)));
  }
}
