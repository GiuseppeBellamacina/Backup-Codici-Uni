namespace alpha{
  
  class ClasseX{
    int alpha; 

    public:
      ClasseX(int a); 
      int getAlpha();
  };
}

//eventualmente in un file .cpp
int alpha::ClasseX::getAlpha(){
  return alpha; 
}

alpha::ClasseX::ClasseX(int a){
  this->alpha = a; 
}
