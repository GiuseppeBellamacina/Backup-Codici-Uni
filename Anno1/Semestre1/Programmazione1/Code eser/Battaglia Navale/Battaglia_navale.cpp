#include "HeaderBattaglia_navale.h"

int main() {
	string nome = "Giocatore";
	unsigned short i = 0, j = 0, x = 0, y = 0;
	short n = 0, n1 = 0, p = 0;
	char A[N][N], B[N][N], C[N][N], D[N][N], risposta = ' ';

	Init_all(A, B, C);

	cout << "Inserire nome giocatore: ";
	cin >> nome;
	cout << "BENVENUTO/A " << nome << endl;
	system("pause");

	Rpr_campo(A, B, nome, &n, &n1);

	cout << "Quante navi vuoi schierare? (max 16)\n";
	cin >> n;
	while (n <= 0 || n > 16 || cin.fail()) {
		cerr << "Valore non valido, riprovare." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> n;
	}

	Rpr_campo(A, B, nome, &p, &n1);
	Schieramento_Giocatore(A, B, nome, &n, &n1, &p, x, y);
	Schieramento_Nemico(C, &n, &n1);
	Rpr_campo(A, B, nome, &n, &n1);

	cout << "Bene, bene, anche il tuo avversario ha schierato " << n << " navi... che la battaglia abbia inizio!\n";
	system("pause");
	Rpr_campo(A, B, nome, &n, &n1);

	while (Game(&n, &n1)) {
		Attacco(A, B, C, nome, &n, &n1, x, y);
		Contrattacco(A, B, nome, &n, &n1, x, y);
	}

	Fine(nome, &n, &n1);
	Restart(risposta);
	cout<<endl;
	cin >> risposta;
}