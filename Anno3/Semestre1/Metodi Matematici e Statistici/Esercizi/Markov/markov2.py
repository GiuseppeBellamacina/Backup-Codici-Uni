# Passeggiata aleatoria su un grafo

# PDF 9, pag 21

# k_1 = 3, k_2 = 3, k_3 = 3, k_4 = 3, k_5 = 4
# Matrice di transizione
# p_11 = 0, p_12 = 1/3, p_13 = 0, p_14 = 1/3, p_15 = 1/3
# p_21 = 1/3, p_22 = 0, p_23 = 1/3, p_24 = 0, p_25 = 1/3
# p_31 = 0, p_32 = 1/3, p_33 = 0, p_34 = 1/3, p_35 = 1/3
# p_41 = 1/3, p_42 = 0, p_43 = 1/3, p_44 = 0, p_45 = 1/3
# p_51 = 1/4, p_52 = 1/4, p_53 = 1/4, p_54 = 1/4, p_55 = 0
#
# Distribuzione stazionaria
# k = 3+3+3+3+4 = 16
# v_1 = v_2 = v_3 = v_4 = 3/16, v_5 = 4/16 = 1/4

import numpy as np

P = np.array([[0, 1/3, 0, 1/3, 1/3],[1/3, 0, 1/3, 0, 1/3],[0, 1/3, 0, 1/3, 1/3],
             [1/3, 0, 1/3, 0, 1/3], [1/4, 1/4, 1/4, 1/4, 0]])
print("Matrice di transizione")
print(P, "\n")

# Metodo analitico

lam, V = np.linalg.eig(P.T)
print("Autovalori")
print(lam, "\n")
print("Autovettori")
print(V, "\n")

v = np.real(V[:,np.argmax(lam)]) / np.sum(np.real(V[:,np.argmax(lam)]))
print("Distribuzione stazionaria")
print(v, "\n")

# Si dimostra che la catena è regolare
print("P^2")
print(np.dot(P,P), "\n")

# Metodo Monte Carlo

n = 5
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