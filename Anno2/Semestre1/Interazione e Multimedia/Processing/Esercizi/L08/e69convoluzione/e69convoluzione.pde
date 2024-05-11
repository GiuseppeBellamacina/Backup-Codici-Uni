//Operatori locali - Convoluzione
//IMPORTANTISSIMO! Ricordiamo che PImage usa le coordinate invertite rispetto alle normali matrici
//Cioè I.get(i,j) è uguale a I[j][i]. 
//Dobbiamo quindi usare le coppie I.get(i,j) e I[j][i] o I.get(j,i) e I[i][j] per riferirci alla stessa locazione.
PImage Im, In3, In5, Il, Is, IsX;
//creo i kernel
float n3=1/9.0;
float[][] nbox3={{n3, n3, n3},
                 {n3, n3, n3},    
                 {n3, n3, n3}};

float n5=1.0/25;              
float[][] nbox5={{n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5}};
                 
float[][] lapl={ {-1,0,-1},
                 {0,4,0},
                 {-1,0,-1}};
                 
float[][] sobX={ {-1,-2,-1},
                 {0,0,0},
                 {1,2,1}};

float[][] sharp={{-1,0,-1},
                 {0,5,0},
                 {-1,0,-1}};
                 
float[][] random={{2,-2,-3},
                 {5,-1,0.5},
                 {-1,4,2}};
           
void setup()
{
  size(1024,1024);
  Im=loadImage("lena.png");
  Im.filter(GRAY); 
  
  //convoluzione su matrici e conversione in PImage
  In3=converti(convoluzione(Im,nbox3));
  In5=converti(convoluzione(Im,nbox5));
  Il=converti(convoluzione(Im,lapl));
  Is=converti(convoluzione(Im,sharp));
  IsX=converti(convoluzione(Im,sobX));
  
  image(Im,0,0);
  image(In5,512,0);
  image(IsX,0,512);
  image(Is,512,512);
  
  

}

void draw()
{
}

float[][] convoluzione(PImage I, float[][] K)
{
  float[][] R=new float[I.height][I.width];
  
  int N=K[0].length;
  int M=K.length;
  PImage tmp;
  float res;
  
  for(int x=0; x<I.width; x++)
  {
    for(int y=0; y<I.height;y++)
    {
      
      tmp=I.get(x-N/2, y-M/2, N, M);
      
      res=0;
      
      for(int p=0; p<N; p++)
      {
        for(int q=0; q<M;q++)
        {
          res=res+green(tmp.get(p,q))*K[q][p];//attenzione agli indici
        }
      }
      
      R[y][x]=res;     
      
    }
  }
  
  return R;
}

PImage converti(float[][] F)
{
  PImage R=createImage(F[0].length,F.length,RGB);
  
  float res=0;
  for(int x=0; x<R.width;x++)
  {
    for(int y=0; y<R.height;y++)
    {
      res=constrain(F[y][x],0,255);
      R.set(x,y,color(res));
    }
  }
  
  return R;
}
