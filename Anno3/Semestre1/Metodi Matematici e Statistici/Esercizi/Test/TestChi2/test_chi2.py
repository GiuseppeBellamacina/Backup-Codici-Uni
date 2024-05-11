# Test del chi-quadro
# Ipotesi nulla:         Il dado è equilibrato
# Ipotesi alternativa:   Il dado non è equilibrato

# PDF 6, pag 41

import numpy as np
from scipy.stats import chi2

data = np.array([20, 7, 12, 18, 20, 23])

N = 100
p = 1/6

E = [N*p for i in range(6)]

T = sum((data - E)**2 / E)

alpha = 0.05
CHI = chi2.ppf(1-alpha, len(data)-1)
print("T: ", T)
print("CHI: ", CHI)

if T > CHI:
    print("Rifiuto l'ipotesi nulla")
else:
    print("Non rifiuto l'ipotesi nulla")

# SECONDA PARTE

Y = np.array([388, 322, 314, 316, 344, 316])

N = sum(Y)
p = 1/6

E = [N*p for i in range(6)]
T = sum((Y - E)**2 / E)

if T > CHI:
    print("Rifiuto l'ipotesi nulla")
else:
    print("Non rifiuto l'ipotesi nulla")

alpha = 0.01
CHI = chi2.ppf(1-alpha, len(Y)-1)
print("T: ", T)
print("CHI: ", CHI)

if T > CHI:
    print("Rifiuto l'ipotesi nulla")
else:
    print("Non rifiuto l'ipotesi nulla")