PImage I, H;
PImage subI;
String url;

void setup(){
  size(512,512);
  url = "https://static.wikia.nocookie.net/adventuretimewithfinnandjake/images/8/81/BMO.png";
  I=loadImage(url,"png");
  
  subI=I.get(I.width/2, height/2, 150, 150);
  I.filter(GRAY);  //-> BMO in toni di grigio
  imageMode(CENTER);
  I.resize(int(I.width/2.5), int(I.height/2.5));
  image(I,width/2,height/2);  
  image(subI, width/2, height/2);
  subI.save(savePath("BMOPorzione.png"));

}
void draw(){
  
}
