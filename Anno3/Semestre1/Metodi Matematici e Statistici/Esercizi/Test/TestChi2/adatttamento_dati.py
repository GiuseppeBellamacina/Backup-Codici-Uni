# Esempio di test di adattamento ai dati
# Si tratta comunque di un test del chi-quadro

# ATTENZIONE: st'esercizio non ha molto senso

# PDF 6, pag 46

import numpy as np
from scipy.stats import chi2
from scipy.stats import poisson

data = np.array([584, 398, 165, 35, 15])

m = len(data)
N = np.sum(data)

p = data/N # Frequenze relative

Ind = data * np.array([0, 1, 2, 3, 4])
lambda_ = np.sum(Ind)/N

p0 = np.zeros(5)
for i in range(4):
    p0[i] = poisson.pmf(i, lambda_)
p0[4] = 1 - np.sum(p0) # Così si completa la somma a 1

# Calcolo del chi-quadro
T = N * np.sum((p - p0)**2/p0)
alpha = 0.05
CHI = chi2.ppf(1-alpha, m-1-1)
print("T = ", T)
print("CHI = ", CHI)
if T < CHI:
    print("Accetto l'ipotesi nulla") # In questo caso si accetta
else:
    print("Rifiuto l'ipotesi nulla")