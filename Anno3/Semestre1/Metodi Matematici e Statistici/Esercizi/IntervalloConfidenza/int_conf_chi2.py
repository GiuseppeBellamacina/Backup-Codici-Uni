# Intervallo di confidenza per il limite superiore
# si usa la distribuzione chi2

"""
ATTENZIONE:
St'esercizio non ha senso
"""

# PDF 5
# Esercizio delle bottiglie

import numpy as np
from scipy.stats import chi2

data = np.array([2.05, 2.04, 1.98, 1.96, 2.03, 2.01, 1.97, 1.99, 2.01, 2.05, 
                 1.96, 1.95, 2.04, 2.01, 1.97, 1.96, 2.02, 2.04, 1.98, 1.94])

n = len(data)

# Calcolo la varianza
var = np.var(data, ddof=1) # ddof=1 per avere la varianza campionaria

alpha = 0.05
chi = chi2.ppf(1-alpha, df=20)
sig2 = (n-1)*var/chi
sig = np.sqrt(sig2)