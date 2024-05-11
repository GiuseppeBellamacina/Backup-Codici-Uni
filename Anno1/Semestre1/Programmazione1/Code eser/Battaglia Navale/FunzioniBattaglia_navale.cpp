#include "HeaderBattaglia_navale.h"

void Init_all(char A[][N], char B[][N], char C[][N]) {
	system("cls");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = acqua;
			B[i][j] = acqua;
			C[i][j] = acqua;
		}
	}
}

void Init_C(char C[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = acqua;
		}
	}
}

void Rpr_campo(char A[][N], char B[][N], string nome, short* n, short* n1) {
	system("cls");
	cout << setw(31) << "EXTREME BATTLESHIP" << setw(23) << "LEGENDA:" << endl << setw(31) << "==================" << setw(65) << "O (NAVE), X (NAVE COLPITA), ~ (ACQUA),   (VUOTO)\n\n";
	cout << setw(28) << "LE TUE NAVI" << setw(47) << "LE TUE MOSSE\n" << endl;
	cout << "    0   1   2   3   4   5   6   7   8   9     |     0   1   2   3   4   5   6   7   8   9" << endl;
	for (int i = 0; i < N; i++) {
		cout << i;
		for (int j = 0; j < N; j++) {
			cout << setw(4) << A[i][j];
		}
		cout << setw(3) << "   " << i << " | " << i;
		for (int j = 0; j < N; j++) {
			cout << setw(4) << B[i][j];
		}
		cout << setw(4) << i << "\n";
	}
	cout << "    0   1   2   3   4   5   6   7   8   9     |     0   1   2   3   4   5   6   7   8   9" << endl;
	cout << endl << "Navi " << nome << ": " << *n << setw(51) << "Navi NEMICO: " << *n1 << "\n\n";
}

void Schieramento_Giocatore(char A[][N], char B[][N], string nome, short* n, short* n1, short* p, unsigned short x, unsigned short y) {
	*p = *n;
	*n = 0;
	for (int i = 0; i < *p; i++) {
		cout << "Inserisci le coordinate delle tue navi (0-9, 0-9):\n";
		cout << "X" << i << ": ";
		cin >> x;
		while (x < 0 || x > 9 || cin.fail()) {
			cerr << "Coordinata non valida, riprovare.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "X" << i << ": ";
			cin >> x;
		}
		cout << "Y" << i << ": ";
		cin >> y;
		while (y < 0 || y > 9 || cin.fail()) {
			cerr << "Coordinata non valida, riprovare.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Y" << i << ": ";
			cin >> y;
		}
		if (A[y][x] == nave) {
			cout << "Hai gia' schierato una nave qui\n";
			i--;
			system("pause");
			Rpr_campo(A, B, nome, n, n1);
		}
		else {
			A[y][x] = nave;
			*n+=1;
			Rpr_campo(A, B, nome, n, n1);
		}
	}
}

void Schieramento_Nemico(char C[][N], short* n, short* n1) {
	for (int i = 0; i < *n; i++) {
		srand(time(0) + i);
		C[rand() % N][rand() % N] = nave;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (C[i][j] == nave) {
				*n1 +=1;
			}
		}
	}
	if (*n1 != *n) {
		Init_C(C);
		Schieramento_Nemico(C, n, n1);
	}
}

void Cheat(char A[][N], char B[][N], char C[][N], string nome, short* n, short* n1) {
	system("cls");
	cout << "\nATTENZIONE: il Radar Tecnico-Tattico ha effettuato una scansione:" << endl;
	cout << endl;
	cout << "    0   1   2   3   4   5   6   7   8   9\n";
	for (short i = 0; i < N; i++) {
		cout << i;
		for (short j = 0; j < N; j++) {
			cout << setw(4) << C[i][j];
		}
		cout << setw(3) << "   " << i << endl;
	}
	cout << "    0   1   2   3   4   5   6   7   8   9\n";
	cout << endl;
	system("pause");
	Rpr_campo(A, B, nome, n, n1);
}

void Attacco(char A[][N], char B[][N], char C[][N], string nome, short* n, short* n1, unsigned short x, unsigned short y) {
	cout << "Scegli le coordinate del tuo bersaglio\n" << "X: ";
	cin >> x;
	while (x < 0 || x>9 || cin.fail()) {
		if (x == 1234) {
			Cheat(A, B, C, nome, n, n1);
		}
		cout << "Coordinata non valida, riprovare.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "X: ";
		cin >> x;
	}
	cout << "Y: ";
	cin >> y;
	while (y < 0 || y>9 || cin.fail()) {
		cout << "Coordinata non valida, riprovare.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Y: ";
		cin >> y;
	}
	Rpr_campo(A, B, nome, n, n1);
	//controllo stato casella
	switch (C[y][x]) {
	case acqua:
		cout << nome << ": " << "Nessuna traccia del nemico qui\n";
		C[y][x] = vuoto;
		B[y][x] = vuoto;
		break;
	case vuoto:
		cout << nome << ": " << "Hai gia' sparato qui, non c'era nulla prima e ora non e' cambiato niente\n";
		break;
	case colpito:
		cout << nome << ": " << "Hai gia' distrutto questa nave, non infierire\n";
		break;
	case nave:
		cout << nome << ": " << "Nave colpita e affondata\n";
		*n1 -= 1;
		C[y][x] = colpito;
		B[y][x] = colpito;
	}
}

void Contrattacco(char A[][N], char B[][N], string nome, short* n, short* n1, unsigned short x, unsigned short y) {
	if (*n1 != 0) { //se il nemico non ha navi non può contrattaccare ovviamente
		srand(time(0));
		x = rand() % 9;
		y = rand() % 9;
		switch (A[y][x]) {
		case acqua:
			cout << "NEMICO: Il nemico ha fatto un buco nell'acqua\n";
			break;
		case colpito:
			Contrattacco(A, B, nome, n, n1, x, y);
			break;
		case nave:
			cout << "NEMICO: Una tua nave e' stata colpita e affondata, non mollare!\n";
			*n -= 1;
			A[y][x] = colpito;
		}
	}
	cout << endl;
	system("pause");
	Rpr_campo(A, B, nome, n, n1);
}

bool Game(short* n, short* n1) {
	if (*n1 == 0 || *n == 0)
		return false;
	else
		return true;
}

void Fine(string nome, short* n, short* n1) {
	if (*n1 == 0)
		cout << "SEEEE HAI VINTO " << nome << endl;
	if (*n == 0)
		cout << "E NIENTE " << nome << ", IL NEMICO TI HA DEMOLITO";
}

int Restart(char risposta) {
	cout << "\nVuoi giocare un'altra partita? (Y/N)\n";
	cin >> risposta;
	cout << endl;
	switch (risposta) {
	case 'Y':
		return main();
		break;
	case 'y':
		return main();
		break;
	case 'N':
		cout << "Va bene, allora addios...";
		break;
	case 'n':
		cout << "Va bene, allora addios...";
		break;
	default:
		cout << "Non ho capito bene, ma nel dubbio ti saluto...";
		break;
	}
}