# Determinare la distribuzione stazionaria della matrice assegnata

# PDF 9, pag 16

# 1->2, 1->3
# 2->2, 2->3
# 3->1, 3->3
# 1->2->3->1 (per la proprietà transitiva)
# Tutti gli stati comunicano tra loro, quindi la catena è irriducibile.
# Inoltre p_22>0, p_33>0 e quindi per il criterio di regolarità essa è regolare.
# Per il Teorema di Markov la catena ha un'unica distribuzione stazionaria.
#
# D'altra parte la catena è irriducibile e l'insieme degli stati è finito.
# Quindi esiste un'unica distribuzione stazionaria.

import numpy as np

P = np.array([[0, 1/4, 3/4],[0, 1/2, 1/2],[3/4, 0, 1/4]])
print("Matrice di transizione")
print(P, "\n")

# Abbbiamo visto che la catena è irriducibile perchè
# tutti gli stati comunicano tra loro.
# Inoltre la catena è regolare perchè esistono degli
# elementi della diagonale che sono maggiori di 0.

# Dunque per il Teorema di Markov la catena ha un'unica
# distribuzione stazionaria.

# Se calcolo P^2 vedo che tutti gli elementi sono maggiori di 0
# e quindi ho un'altra conferma che la catena è regolare.

P2 = np.dot(P,P)
print("P^2")
print(P2, "\n")

# Calcolo la distribuzione stazionaria
# Metodo analitico

lam , V = np.linalg.eig(P.T)
print("Autovalori")
print(lam, "\n")
print("Autovettori")
print(V, "\n")

# ATTENZIONE:
# Si seve scegliere come indice quello con
# autovalore pari a 1
# In alternativa si può usare np.argmax(lam)
v = V[:,1] / np.sum(V[:,1])
print("Distribuzione stazionaria")
print(v, "\n")

# Metodo Monte Carlo

n = 3 # dimensione della matrice
F = np.zeros(n)
N = 10**5

j = np.random.randint(n)
F[j] = 1

for i in range(N):
    j_multi = np.random.multinomial(1,P[j,:])
    j = np.nonzero(j_multi)[0][0]
    F[j] += 1

vv = F / N
print("Distribuzione stazionaria")
print(vv, "\n")