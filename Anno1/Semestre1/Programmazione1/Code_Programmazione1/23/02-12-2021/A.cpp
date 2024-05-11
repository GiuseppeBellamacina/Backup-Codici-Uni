#include "A.h"

void A::setX(double y) {
	x = 2 * y;  //variabile istanza di x
}

void A::setX2(double y){
	this->x = 3 * y;  //variabile istanza di x
	//(*this).x = 3 * y;
}

A::A(double init) {
	setX(init);
}