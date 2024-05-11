# Metodo di inversione della funzione di ripartizione
# di una variabile aleatoria binomiale

# PDF 8, pag 9

import numpy as np

# Si consideri una variabile aleatoria binomiale X ~ B(1, p)
# vale a dire una distribuzione di Bernoulli.
# Scelgo p con un valore arbitrario

p = 0.3

# Metodo di inversione della funzione di ripartizione
def rand_binom(p):
    U = np.random.rand()
    if U < p:
        return 1
    else:
        return 0

# Generiamo 10^5 valori casuali
N = 10**5
X = np.zeros(N)
for i in range(N):
    X[i] = rand_binom(p)

# Frequenze osservate
N_succ = np.sum(X)
N_fail = N - N_succ

# Probabilità empiriche
P_succ = N_succ / N
P_fail = N_fail / N

print('Probabilita\' teorica di successo:', p)
print('Probabilita\' empirica di successo:', P_succ)
print('Probabilita\' teorica di fallimento:', 1-p)
print('Probabilita\' empirica di fallimento:', P_fail)

# I risultati sono in accordo con le probabilità teoriche