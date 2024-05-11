"""
Il numero di pezzi guasti di una fornitura
segue una legge B(2,p) ove p è una variabile aleatoria
di legge U([0.5, 1]).
Qual è la probabilità che un solo pezzo sia guasto?
"""

# La distribuzione uniforme è una distribuzione continua
# in un intervallo [a, b] dove a e b sono i parametri e
# la funzione di densità di probabilità è f(x) = 1/(b-a)

from scipy.stats import uniform, binom
from scipy.integrate import quad

# uniform.pdf(x, a, b-a), x è il valore, a è il limite inferiore, b-a è l'ampiezza
# N.B. x deve essere compreso tra a e b

# binom.pmf(k, n, p), k è il numero di successi, n è il numero di tentativi, p è la probabilità di successo

# quad(funzione, a, b) calcola l'integrale definito della funzione tra a e b

a = 0.5
b = 1

"""
St'esercizio è più bastardo degli altri perché dice che
il numero di pezzi guasti segue una legge B(2,p) dove p
si calcola con una distribuzione uniforme.
B(2,p) è una distribuzione binomiale con 2 tentativi e p
probabilità di successo (in questo caso di guasto).
Per calcolare la probabilità che un solo pezzo sia guasto
bisogna calcolare l'integrale definito della funzione di
densità di probabilità della distribuzione uniforme tra
a e b, moltiplicato per la funzione di massa di probabilità
della distribuzione binomiale con k=1, n=2 e p=x.
k è 1 perché vogliamo calcolare la probabilità che un solo
pezzo sia guasto. n è 2 perché abbiamo due tentativi.
In parole povere, per calcolare la probabilità che un solo
pezzo sia guasto bisogna calcolare l'integrale definito tra
a e b della funzione data dalla distribuzione uniforme e dalla
distribuzione binomiale. Si moltiplicano le due distribuzioni per via
della regola della probabilità totale.
"""

def funzione(x):
    return binom.pmf(1, 2, x)*uniform.pdf(x, a, b-a)

# res = quad(lambda x: binom.pmf(1, 2, x)*uniform.pdf(x, a, b-a), a, b)
res = quad(funzione, a, b)[0] # quad restituisce una tupla, il primo elemento è il valore dell'integrale, il secondo è l'errore
print(res)