#include <iostream>
#include <cstdlib>
#include <typeinfo>
#define DIM 50
using namespace std;

class A{
	private:
		char *str;
		short len;
	public:
		A(short w,char c1,char c2):len(w){
			this->str=new char[len];
			for(int i=0;i<len;i++)
			str[i]=c1+ rand()%(c2-c1+1);
		}
		
		virtual short f(short k)=0;
		
		virtual ostream& print(ostream &os){
			os<<typeid(*this).name()<<")"<<"str=[";
			for(int i=0;i<len;i++)
			os<<str[i];
			os<<"]";
			return os;
		}
		
		string operator()(int i1,int i2){
			string sub="";
			for(int i=i1;i<=i1;i++)
			sub+=str[i];
			return sub;
		}
		
		
		protected:
		string extract(short k){
			string ss3="";
			if(k>=len){
				for(int i=0;i<len;i++)
				ss3+=str[i];
				return ss3;
			}
			else{
				for(int i=len-1;i>=len-k;i--)
				ss3+=str[i];
				return ss3;
			}
			
		}
		
};

ostream& operator<<(ostream &os,A &obj){
	return obj.print(os);
}

class B:public A{
	private:
		char z;
	public:
		B(short m,char c1,char c2):A(m,c1,c2){
			string s=extract(m/2+1);
			this->z= s[rand()%s.length()];
		}
		
		short f(short k){
			string s1=extract(k);
			short c=0;
			for(int i=0;i< s1.length();i++){
				if(s1[i]<=z)
				c++;
			}
			return c;
		}
		
		ostream& print(ostream &os){
			A::print(os);
			os<<",z="<<z;
			return os;
		}
};

template <typename T>
class C:public A{
	private:
		T ss;
	public:
		C(short w,char c1,char c2):A(w,c1,c2){
			string ex= extract(w/2+1);
			if(typeid(ss)==typeid(string)){
				for(int i=0;i<ex.length();i++)
				this->ss+=ex[i];
			}
			else
			this->ss=w;
		}
		short f(short k){
			string s2= extract(k);
			for(int i=0;i< s2.length();i++){
				if(s2[i]>='A'&& s2[i]<='Z')
				return 1;
			}
			return 0;
		}
		
		T foo(short x){
			T ssx=ss;
		    for(int i=0;i<x;i++)
			ssx+=ssx;
			return ssx;
		}
		
		ostream& print(ostream &os){
			A::print(os);
			os<<",ss="<<ss;
			return os;
		}
			
};


int main(){
	srand(12345678);
	A* vec[DIM];

for(unsigned int i=0; i<DIM; i++){
    int r = rand(); 
    cout<<"i="<<i<<endl;
    if(r%3==0){ // B 
    cout<<"iB="<<i<<endl;
      vec[i] = new B(rand()%10+5, '0', '9');
      
  }
    else if(r%3==1){
      vec[i] = new C<string>(rand()%10+5, 'a', 'z');
      cout<<"i:"<<i;
  }
    else
      vec[i] = new C<short>(rand()%20+10, 'A', 'Z');
  }
  
  //PUNTO 1:
cout<<"ES.1:"<<endl;
for(int i=0;i<DIM;i++)
cout<<*vec[i]<<endl;

//PUNTO 2:
int c=0;
short sum=0;
for(int i=0;i<DIM;i++){
	if(vec[i]->f(5)>=4)
	c++;
}

cout<<"numero f(5):"<<c<<endl;

//PUNTO 3:
cout<<"vec(1,5):"<<(*vec[3])(1,5)<<endl;
(*vec[3])(1,5)= "hello";
cout<<"vec(1,5):"<<(*vec[3])(1,5)<<endl;

  

	
}
