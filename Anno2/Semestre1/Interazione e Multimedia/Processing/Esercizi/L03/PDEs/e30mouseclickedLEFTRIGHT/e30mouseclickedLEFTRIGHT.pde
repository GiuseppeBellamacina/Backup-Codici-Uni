float [] r=new float[50];
void setup(){
size(800,800);
for(int i=0; i<r.length;i++){
r[i]=(i+1)*100;
}

}
void draw(){
  for(int i=r.length-1; i>0;i--){
    fill(random(255),random(255),random(255));
    ellipse(width/2,height/2,r[i],r[i]);
  }

}

void mouseClicked(){

  
  if(mouseButton==LEFT){
    loop();
  }
    if(mouseButton==RIGHT){
    noLoop();
}
}