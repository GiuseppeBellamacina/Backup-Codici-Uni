# Test sulla varianza

# PDF 6, pag 25

import numpy as np
from scipy.stats import chi2

data = np.array([2.05, 2.04, 1.98, 1.96, 2.03, 2.01, 1.97, 1.99, 2.01, 2.05,
                1.96, 1.95, 2.04, 2.01, 1.97, 1.96, 2.02, 2.04, 1.98, 1.94])

# Ho già sigma_0, calcolo anche la dimensione del campione
sigma_0 = 0.05
n = len(data)

# Calcolo la varianza campionaria
s2 = np.var(data, ddof=1)

# Calcolo la statistica del test
W_0 = (n - 1) * s2 / sigma_0**2

# Il livello di significatività è già dato
# Calcolo la soglia critica e anche qui dipende dal tipo di test
# In questo caso è un test unilaterale sinistro
alpha = 0.05
CHI = chi2.ppf(alpha, df=n-1)
print("Soglia critica:", CHI)
print("Statistiche del test:", W_0)

if W_0 > CHI:
    print("Accetto H0")
else:
    print("Rifiuto H0")