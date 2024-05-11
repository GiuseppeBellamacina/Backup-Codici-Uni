#include <string>

namespace beta{
  
  class ClasseX{
    std::string beta; 

    public:
      ClasseX(std::string s); 
      std::string getBeta();
  };
}

//eventualmente in un file 
// cpp separato 
std::string beta::ClasseX::getBeta(){
  return beta;
}

beta::ClasseX::ClasseX(std::string s){
  this->beta = s;
}

