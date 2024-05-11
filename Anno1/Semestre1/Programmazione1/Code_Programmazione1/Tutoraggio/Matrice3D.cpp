#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrice3D {

	private:
		int ***M;
		int x, y, z;

		void printCiao() {
			cout << "Ciao sono una Matrice3D" << endl;
		}

	public:
		Matrice3D(int x = 5, int y = 5, int z = 5, int k = 5) { // costruttore per inizializzare con valori specificati dall'utente
			this->x = x;
			this->y = y;
			this->z = z;
			M = new int **[this->x];
			for (int i = 0; i < this->x; i++) {
				M[i] = new int *[this->y];
				for (int j = 0; j < this->y; j++) {
					M[i][j] = new int[this->z];
					for (int l = 0; l < this->z; l++) {
						M[i][j][l] = k;
					}
				}
			}
		}

		int getDimX() { return x; }

		int getDimY() { return y; }

		int getDimZ() { return z; }

		void Stampa() {
			cout << "Stampa della Matrice3D:" << endl;
			for (int i = 0; i < this->z; i++) {
				cout << "Dimensione " << i << endl;
				for (int j = 0; j < this->x; j++) {
					for (int k = 0; k < this->y; k++) {
						cout << M[j][k][i] << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
		}

		int& getElement(int i, int j, int k) {
			if (i < this-> x && j < this->y && k < this->z) {
				return M[i][j][k];
			}
			return *(new int(-1));
		}

		int getValue(int i, int j, int k) {
			if (i < this-> x && j < this->y && k < this->z) {
				return M[i][j][k];
			}
			return -1;
		}

		void DistruggiMatrice() {
			for (int i = 0; i < this->x; i++) {
				for (int j = 0; j < this->y; j++) {
					delete[] M[i][j];
				}
				delete[] M[i];
			}
			delete[] M;
		}

		Matrice3D* sommaByPtr(Matrice3D* m1, Matrice3D* m2) {
			if(
				m1->getDimX() != m2->getDimX() ||
				m1->getDimY() != m2->getDimY() ||
				m1->getDimZ() != m2->getDimZ()
			) return NULL;
			Matrice3D* m = new Matrice3D(m1->getDimX(), m1->getDimY(), m1->getDimZ(), 0);
			for (int i = 0; i < m->getDimX(); i++) {
				for (int j = 0; j < m->getDimY(); j++) {
					for (int k = 0; k < m->getDimZ(); k++) {
						m->getElement(i, j, k) = (
							m1->getValue(i, j, k) + 
							m2->getValue(i, j, k)
						);
					}
				}
			}
			return m;
		}

		Matrice3D* sommaByPtr(Matrice3D* m1) {
			if(
				m1->getDimX() != x ||
				m1->getDimY() != y ||
				m1->getDimZ() != z
			) return NULL;
			Matrice3D* m = new Matrice3D(m1->getDimX(), m1->getDimY(), m1->getDimZ(), 0);
			for (int i = 0; i < m->getDimX(); i++) {
				for (int j = 0; j < m->getDimY(); j++) {
					for (int k = 0; k < m->getDimZ(); k++) {
						m->getElement(i, j, k) = (
							m1->getValue(i, j, k) + 
							M[i][j][k]
						);
					}
				}
			}
			return m;
		}

		Matrice3D& sommaByReference(Matrice3D &m1, Matrice3D &m2) {
			if(
				m1.getDimX() != m2.getDimX() ||
				m1.getDimY() != m2.getDimY() ||
				m1.getDimZ() != m2.getDimZ()
			) return m1;
			Matrice3D* m = new Matrice3D(m1.getDimX(), m1.getDimY(), m1.getDimZ(), 0);
			for (int i = 0; i < m->getDimX(); i++) {
				for (int j = 0; j < m->getDimY(); j++) {
					for (int k = 0; k < m->getDimZ(); k++) {
						m->getElement(i, j, k) = (
							m1.getValue(i, j, k) + 
							m2.getValue(i, j, k)
						);
					}
				}
			}
			return *m;
		}

		void somma3D(Matrice3D &m1, Matrice3D &m2, Matrice3D *m3) {
			if(
				m1.getDimX() != m2.getDimX()  ||
				m2.getDimX() != m3->getDimX() ||
				m1.getDimY() != m2.getDimY()  ||
				m2.getDimY() != m3->getDimY() ||
				m1.getDimZ() != m2.getDimZ()  ||
				m2.getDimZ() != m3->getDimZ()
			) return;
			for (int i = 0; i < m3->getDimX(); i++) {
				for (int j = 0; j < m3->getDimY(); j++) {
					for (int k = 0; k < m3->getDimZ(); k++) {
						m3->getElement(i, j, k) = (
							m1.getValue(i, j, k) + 
							m2.getValue(i, j, k)
						);
					}
				}
			}
		}
};

int main() {
	Matrice3D *p1 = new Matrice3D(5, 3, 4);
	Matrice3D *p2 = new Matrice3D(5, 3, 4);
	p1->Stampa();
	cout << "Dimensione x della Matrice3D: " << (*p1).getDimX() << endl;
	cout << "Dimensione y della Matrice3D: " << (*p1).getDimY() << endl;
	cout << "Dimensione z della Matrice3D: " << (*p1).getDimZ() << endl;
	//Somma passando alla funzione i puntatori
	p1 = p1->sommaByPtr(p1, p2);
	//Somma passando alla funzioni le reference
	*p2 = p1->sommaByReference(*p1, *p2);
	cout << endl << "Somma della matrice p1 + p2 e salvata su p1" << endl; 
	p1->Stampa();
	p2->getElement(1, 2, 1) = 0;
	cout << endl << "Somma della matrice p1 + p2 e salvata su p2" << endl; 
	p2->Stampa();
	//Somma passando due Matrici3D per reference e una per puntatore
	p1->somma3D(*p1, *p2, p1);
	cout << endl << "Somma della matrice p1 + p2 e salvata su p1" << endl; 
	p1->Stampa();
	p1->DistruggiMatrice();
	p2->DistruggiMatrice();
	delete p1;
	delete p2;
	return 0;
}
