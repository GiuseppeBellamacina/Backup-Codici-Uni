# Test sulla media delle coppie di popolazioni
# Ipotesi nulla         H_0 : mu_1 = mu_2
# Ipotesi alternativa   H_1 : mu_1 > mu_2
# Test unilatero a destra

# PDF 6, pag 33

"""
ATTENZIONE:
Dato che ho capito solo ora come funziona la roba del rigetto
o dell'accettazione dell'ipotesi nulla, potrei aver fatto un po' di
casino prima (anche se ricontrollando non mi è parso).
Nel dubbio guardare SEMPRE le slide quando si fanno ste robe.
"""

import numpy as np
from scipy.stats import norm
# Questo è un test unilatero a destra

X1 = 121
X2 = 112
n1 = n2 = 10
sig1 = sig2 = 8

Z_0 = (X1 - X2) / np.sqrt(sig1**2/n1 + sig2**2/n2)

alpha = 0.05
PHI = norm.ppf(1-alpha)
print("Z_0 = ", Z_0)
print("PHI = ", PHI)

if Z_0 > PHI:
    print("Rigetto H0")
else:
    print("Accetto H0")

# St'esercizio calcola se il primo materiale si essicca
# dopo del secondo. Dato che rigetto H0, allora il primo
# effettivamente si essicca dopo il secondo.

# Ora si calcola l'intervallo di confidenza per la differenza
# ma si ottiene un solo valore k, perchè l'intervallo sarà
# ]k, +inf[. Vuol dire che il primo materiale si essicca
# almeno dopo k minuti rispetto al secondo.

k = X1 - X2 - PHI * np.sqrt(sig1**2/n1 + sig2**2/n2)
print("k = ", k)