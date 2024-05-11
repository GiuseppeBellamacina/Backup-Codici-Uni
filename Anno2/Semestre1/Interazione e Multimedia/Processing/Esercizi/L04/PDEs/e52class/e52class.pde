Ball b;
Ball b2;
int K;
Ball[] bs;

ArrayList<Ball> abs;
void setup()
{
  background(0);
  size(1000,500);
  K=10;
  
  bs=new Ball[K];
  abs=new ArrayList<Ball>();
  
  for(int i=0;i<K;i++)
  {
    bs[i]=new Ball(random(50,450),random(50,450),random(25,70),random(1,10),random(1,10));
  }
  
  /*
  for(int i=0;i<K;i++)
  {
    abs.add(new Ball(random(50,450),random(50,450),random(25,70),random(1,10),random(1,10)));
  }
  */
  
}

void draw()
{
  //background(0);
  fill(0,40);
  rect(0,0,width,height);
  
  
  for(int i=0; i<K;i++)
  {
    //bs[i].run();
  }
  
  /*
  for(int i=0; i<abs.size();i++)
  {
    abs.get(i).run();
  }
  */
  
  for(Ball b:abs)
    b.run();
  
}

void keyPressed()
{
  if((key=='N')||(key=='n'))
    abs.add(new Ball(random(50,450),random(50,450),random(25,70),random(1,10),random(1,10)));
}