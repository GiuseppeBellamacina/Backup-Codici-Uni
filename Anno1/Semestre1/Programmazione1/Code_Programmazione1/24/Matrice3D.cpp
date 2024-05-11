#include <iostream>

using namespace std; 

class Matrice3D{

  private:
    double ***data;
    int d1, d2, d3; 

  public: 
    Matrice3D(int d1=10, int d2=10, int d3=10, double firstValue=0.0){
    	data = new double**[d1];
    		for(int i=0; i<d1; i++){
				data[i] = new double*[d2];
					for(int j=0; j<d2; j++){
						data[i][j] = new double[d3];
	  						for(int z=0; z<d3; z++)
	    						data[i][j][z] = firstValue;  
					}
      		}  
      this->d1 = d1;  
      this->d2 = d2;
      this->d3 = d3;
	}	

    ~Matrice3D(){
      	for(int i=0; i<this->d1; i++){
			for(int j=0; j<this->d2; j++)
	  			delete [] data[i][j];	
		    delete [] data[i];
     	}
      	delete [] data; 
    }

    double &get(int i, int j, int z){
      return data[i][j][z];
    }

    int getDimX(){
      return d1;
    }

    int getDimY(){
      return d2; 
    }

    int getDimZ(){
      return d3; 
    }

    Matrice3D* sommaByPtr(Matrice3D *ptr1, Matrice3D *ptr2){
      if(ptr1->getDimX() != ptr2->getDimX() || ptr2->getDimZ() != ptr1->getDimZ() || ptr2->getDimY() != ptr1->getDimY())
	return NULL; 
	      
      Matrice3D *res = new Matrice3D(ptr1->getDimX(), ptr1->getDimY(), ptr1->getDimZ());

      for(int i=0; i<ptr1->getDimX(); i++)
	for(int j=0; j<ptr1->getDimY(); j++)	  
	  for(int z=0; z<ptr1->getDimZ(); z++)
	    res->data[i][j][z] = ptr1->get(i,j,z) +  ptr2->get(i,j,z);

      return res; 
    }

    Matrice3D &sommaByReference(Matrice3D &m1, Matrice3D &m2){
      if(m1.d1 != m2.d1 || m1.d2 != m2.d2 || m1.d3 != m2.d3){
	 Matrice3D *res = new Matrice3D(1,1,1,-1);
	 return *res; 
      }
	
      Matrice3D *res = new Matrice3D(m1.d1, m1.d2, m1.d3);

      for(int i=0; i<m1.d1; i++)
	for(int j=0; j<m1.d2; j++)	  
	  for(int z=0; z<m1.d3; z++)
	    res->data[i][j][z] = m1.data[i][j][z] +  m2.data[i][j][z];

      return *res; 
    }

    void stampa(){
      for(int i=0; i<getDimX(); i++){
	cout << "[i=" << i << "]" << endl; 
	for(int j=0; j<getDimY(); j++){
	  for(int z=0; z<getDimZ(); z++)
	    cout << data[i][j][z] << " ";
	  cout << endl; 	  
	}
      }
    }
};


using namespace std; 

int main(){

  Matrice3D *p1 = new Matrice3D(10, 10, 10, 1.0);
  Matrice3D *p2 = new Matrice3D(10, 10, 10, 3.0);
  
  Matrice3D p3(10, 10, 10, 9.0);
  Matrice3D &p4 = p3;
  Matrice3D p5(10, 10, 10, 4.0);
  Matrice3D &p6 = p5;

  Matrice3D *res = p2->sommaByPtr(p1, p2);
  Matrice3D &rez = p4.sommaByReference(p4, p6);
  

  res->stampa();
  rez.stampa(); 
  
}
