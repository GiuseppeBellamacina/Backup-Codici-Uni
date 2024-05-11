# Generazione numeri random con distribuzione multinomiale

# PDF 8, pag 10

import numpy as np
import matplotlib.pyplot as plt

def rand_mult(F):
    U = np.random.rand() # U ~ U(0,1)
    # X = np.nonzero(U < F)[0][0]
    for i in range(len(F)-2, -1, -1):
        if U > F[i]:
            return i+1
    return 0

"""
Essenzialmente la funzione di sopra fa questo:
prende l'array delle probabilità p e ne calcola la somma cumulativa F,
poi torna il primo indice in cui il numero random U è minore di F.
"""

p = [1/4, 1/2, 1/4]

N = 10000
X = np.zeros(len(p))
F = np.cumsum(p)
for i in range(N):
    x = rand_mult(F)
    for j in range(len(X)):
        X[j] += (x == j) # somma 1 se x == j

# ----------------------------------
# rando = np.random.multinomial(N, p)
# print(rando)
# plt.bar(range(len(p)), rando/N)
# ----------------------------------

F = X/N
plt.bar(range(len(p)), F)
plt.show()