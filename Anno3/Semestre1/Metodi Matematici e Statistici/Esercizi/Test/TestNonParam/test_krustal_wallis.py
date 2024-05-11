# Test di Kruskal-Wallis
# Ipotesi nulla: Il mescolamento non influisce sulla resistenza alla trazione (mu_1=mu_2=mu_3=mu_4)
# Ipotesi alternativa: Il mescolamento influisce sulla resistenza alla trazione

# PDF 6, pag 63

# ATTENZIONE: guardare bene le slide anche qui

import numpy as np
from scipy.stats import rankdata, chi2

# Prendo i dati

X_1 = np.array([3129., 3000., 2865., 2890.])
X_2 = np.array([3200., 3000., 2975., 3150.])
X_3 = np.array([2800., 2900., 2985., 3050.])
X_4 = np.array([2600., 2700., 2600., 2765.])

m = 4 # numero di gruppi
n = np.array([X_1.size, X_2.size, X_3.size, X_4.size]) # numero di osservazioni per gruppo

N = n.sum() # numero totale di osservazioni

# Mi conviene fare un unico array con tutti i dati
Y = np.concatenate([X_1, X_2, X_3, X_4])

# Calcolo i ranghi
R = rankdata(Y)

# Calcolo la statistica S2
S2 = (np.sum(R**2.)-N*(N+1)**2./4.) / (N-1)

# Calcolo la somma dei ranghi per gruppo
RR = np.zeros(m)
for i in range(m):
    RR[i] = np.sum(R[m*i:m*(i+1)])

# Calcolo la statistica H
H = (np.sum(RR**2. / n)-N*(N+1)**2./4.)/S2

# ATTENZIONE:
# avrei potuto usare anche l'altra formula per H
# se avessi soddisfatto una delle 2 condizioni
# in questo caso m > 3, ma ni < 5 per tutti i gruppi

# Calcolo il valore critico
alpha = 0.05
CHI = chi2.ppf(alpha, m-1)
print("H = ", H)
print("CHI = ", CHI)

if H > CHI:
    print("Rifiuto l'ipotesi nulla")
else:
    print("Non rifiuto l'ipotesi nulla")