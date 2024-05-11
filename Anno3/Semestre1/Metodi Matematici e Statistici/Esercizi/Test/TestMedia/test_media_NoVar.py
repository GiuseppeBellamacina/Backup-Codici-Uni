# Test sulla media con varianza sconosciuta
# Ipotesi nulla         H_0 : mu = mu_0
# Ipotesi alternativa   H_1 : mu > mu_0
# Test unilatero a destra

# PDF 6, pag 21

import numpy as np
from scipy.stats import t

data = np.array([19.8, 18.5, 17.6, 16.7, 15.8, 15.4, 14.1, 13.6, 11.9, 11.4, 
                 11.4, 8.8, 7.5, 15.4, 15.4, 19.5, 14.9, 12.7, 11.9, 11.4, 10.1, 7.9])

# Calcolo media, deviazione standard e dimensione campione
mu = np.mean(data)
std = np.std(data, ddof=1)
n = len(data)

# Ho già il valore di riferimento per la media
mu_0 = 10
T_0 = (mu - mu_0) / std * np.sqrt(n)

# Effettuo il test con alpha = 0.05
alpha = 0.05
T = t.ppf(1 - alpha, n-1)
print("T_0:", T_0)
print("T:", T)

# Confronto i valori
if T_0 > T:
    print("Rifiuto H_0") # Si rigetta l'ipotesi nulla
else:
    print("Accetto H_0")

# Ora si calcola il p-value
# Anche per questo calcolo si guarda in che tipo di test si è
# i questo caso è un test unilaterale a destra

p_value = 1 - t.cdf(T_0, n-1)
print("p-value:", p_value)