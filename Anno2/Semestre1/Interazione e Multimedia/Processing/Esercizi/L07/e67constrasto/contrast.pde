PImage Im, Is, Ie;
float [] H1,H2,H3;
void setup(){
  size(1536,512);
  Im=loadImage("lena.png");
  Im.filter(GRAY);
    
  Is=stretching(Im);
  Ie=equalizza(Im);
  
  H1=istogramma(Im);
  H2=istogramma(Is);
  H3=istogramma(Ie);
  
  image(Im, 0,0);
  image(Is,512,0);
  image(Ie,1024,0);
  
  for (int i=0;i<256;i++){
    println(i+": "+H1[i]+"\t\t\t"+H2[i]+"\t\t\t"+H3[i]);
  }
}

void draw(){
}

PImage equalizza(PImage I){
  PImage R=I.copy();
  float [] H =istogramma(I);
  
  //Istogramma cumulativo
  for (int i=1;i<256;i++){
    H[i]=H[i-1]+H[i];
  }
  
  R.loadPixels();
  
  for (int i=0;i<R.pixels.length;i++){
    R.pixels[i]=color(255*H[int(red(R.pixels[i]))]);
  }
  
  R.updatePixels();
  return R;
  
}

PImage stretching(PImage I){
  PImage R=I.copy();
  float max, min;
  R.loadPixels();
  max=red(R.pixels[0]);
  min=red(R.pixels[0]);
  
  for (int i=0;i<R.pixels.length;i++){
    if (red(R.pixels[i])<min){
      min=red(R.pixels[i]);
    }
    if (red(R.pixels[i])>max){
      max=red(R.pixels[i]);
    }
  }
  
  for (int i=0;i<R.pixels.length;i++){
    R.pixels[i]=color(255*(red(R.pixels[i])-min)/(max-min));
  }
  R.updatePixels();
  return R;
  
}


float [] istogramma(PImage I){
  float[] H= new float[256];
  for (int i=0; i<256;i++){
    H[i]=0;
  }
  
  I.loadPixels();
  
  for (int i=0;i<I.pixels.length;i++){
    H[int(red(I.pixels[i]))]++;
  }
  
  for (int i=0; i<256;i++){
    H[i]=H[i]/I.pixels.length;
  }
  
  return H;
  
  
}
