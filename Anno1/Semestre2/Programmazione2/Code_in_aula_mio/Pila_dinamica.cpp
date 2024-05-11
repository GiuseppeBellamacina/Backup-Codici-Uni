#include <iostream>
using namespace std;

class Nodo{
	public:
		int valore;
		Nodo* succ;
};

class Stack{
	private:
		Nodo* top;
	public:
		Stack();
		~Stack();
		void push(int);
		int pop();
		int peek();
		
		friend
		ostream& operator<<(ostream& out, const Stack& s);		
};

Stack::Stack(){top=nullptr;}

Stack::~Stack(){
	while(top!=nullptr){
		Nodo* tmp = top;
		top = top->succ;
		delete tmp;
	}
}

void Stack::push(int n){
	Nodo* ptr = new Nodo;
	ptr->valore = n;
	ptr->succ = top;
	top = ptr;
}

int Stack::pop(){
	if(top==nullptr){
		cout << "Pila vuota" << endl;
		exit(-1);
	}
	Nodo* tmp = top;
	int val = top->valore;
	top = top->succ;
	delete tmp;
	return val;
}

int Stack::peek(){
	if(top==nullptr)
		return top->valore;
	cout << "Pila vuota" << endl;
		exit(-1);
}

ostream& operator<<(ostream& out, const Stack& s){
	Nodo* iter = s.top;
	while(iter!=nullptr){
		out << "[" << iter->valore << "]" << endl;
		iter = iter->succ;
	}
	out << endl;
	return out;
}


int main(){
	Stack st;
	st.push(12);
	st.push(20);
	st.push(13);
	st.push(33);
	
	cout << st;
	st.pop();
	st.pop();
	cout << st;
	
	return 0;
}
