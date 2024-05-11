# Test sulla propagazione
# Ipotesi nulla         H_0 : p = p0
# Ipotesi alternativa   H_1 : p < p0

# PDF 6, pag 28

import numpy as np
from scipy.stats import norm

p0 = 0.05
n = 200
k = 4
p = k/n

Z_0 = (p - p0) / np.sqrt(p0 * (1 - p0)) * np.sqrt(n)

alpha = 0.05
PHI = norm.ppf(alpha)
print('Z_0 =', Z_0)
print('PHI =', PHI)

if Z_0 > PHI:
    print('Rifiuto H_0')
else:
    print('Accetto H_0')

p_star = 0.03
beta = 0.1

dim_camp = ((norm.ppf(beta)*np.sqrt(p_star*(1-p_star)) + norm.ppf(alpha)*np.sqrt(p0*(1-p0))) / (p_star - p0))**2
print('dim_camp =', dim_camp)