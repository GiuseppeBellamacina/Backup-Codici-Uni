# Test t per dati accoppiati
# Ipotesi nulla          H_0 : mu_D = 0
# Ipotesi alternativa    H_1 : mu_D > 0
# Test unilatero a destra

# N.B mu_D è la differenza tra i valori accoppiati

# PDF 6, pag 36

import numpy as np
from scipy.stats import t

data = np.array([[265., 240., 258., 295., 251., 245., 287., 314., 260., 279., 283., 240., 238., 225., 247.], 
                 [229., 231., 227., 240., 238., 241., 234., 256., 247., 239., 246., 218., 219., 226., 233.]])

D = data[0,:] - data[1,:]

n = len(D)
D_mean = np.mean(D)
D_std = np.std(D, ddof=1)

T0 = D_mean / D_std * np.sqrt(n)

alpha = 0.05
tt = t.ppf(1-alpha, n-1)
print('T0 =', T0)
print('tt =', tt)

if T0 > tt:
    print('H_0 rifiutata')
else:
    print('H_0 accettata')