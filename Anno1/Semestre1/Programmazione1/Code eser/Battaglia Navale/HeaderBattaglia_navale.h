#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#define N 10
#define acqua '~'
#define nave 'O'
#define colpito 'X'
#define vuoto  ' '

using namespace std;

int main();

void Init_all(char [][N], char [][N], char [][N]);

void Init_C(char [][N]);

void Rpr_campo(char [][N], char [][N], string, short*, short*);

void Schieramento_Giocatore(char [][N], char [][N], string, short*, short*, short*, unsigned short, unsigned short);

void Schieramento_Nemico(char [][N], short*, short*);

void Cheat(char);

void Attacco(char[][N], char[][N], char [][N], string, short*, short*, unsigned short, unsigned short);

void Contrattacco(char [][N], char [][N], string, short*, short*, unsigned short, unsigned short);

bool Game(short*, short*);

void Fine(string, short*, short*);

int Restart(char);