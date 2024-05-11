# Test sulla mediana
# Ipotesi nulla          H_0 : mu = 2000
# Ipotesi alternativa    H_1 : mu <> 2000

# PDF 6, pag 57

"""
ATTENZIONE:
Questo tipo di esercizi varia a seconda del test che si vuole fare.
Controllare sempre le slide.
"""

import numpy as np
from scipy.stats import binom

data = np.loadtxt('Dataset_motore.dat')

n = len(data)
mu = 2000

# Creo l'array delle differenze
diff = data - mu

# Devo contare gli r+, cioè i valori positivi
r_p = 0
for i in range(n):
    if diff[i] > 0:
        r_p += 1

print("r+ = ", r_p)

k = range(r_p, n+1)
Y = binom.pmf(k, n, 0.5)
p_value = 2 * np.sum(Y)

print("p_value = ", p_value)
alpha = 0.05

if p_value <= alpha:
    print("H_0 rifiutata")
else:
    print("H_0 accettata")