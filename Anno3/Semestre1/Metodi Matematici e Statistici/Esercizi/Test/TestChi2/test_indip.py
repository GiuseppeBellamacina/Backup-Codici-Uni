# Test del chi-quadro per l'indipendenza

# PDF 6, pag 50

import numpy as np
from scipy.stats import chi2

data = np.array([[44, 10], [81, 35]])

n = np.sum(data)

# Probabilità empiriche del trattamento
p = np.array([54, 116]) / n

# Probabilità empiriche della guarigione
q = np.array([125, 45]) / n

# Probabilità congiunta
pi = data / n

# Statistica del chi-quadro
T = 0
for h in range(2):
    for k in range(2):
        T += (p[h] * q[k] - pi[h, k])**2 / pi[h, k]
T *= n

alpha = 0.05
CHI = chi2.ppf(1 - alpha, (2 - 1) * (2 - 1)) # 2-1 perchè si fa m-1 e r-1 dove m e r sono le dimensioni della tabella
print("T: ", T)
print("CHI: ", CHI)

if T > CHI:
    print("GLi effetti NON sono indipendenti")
else:
    print("Gli effetti sono indipendenti")