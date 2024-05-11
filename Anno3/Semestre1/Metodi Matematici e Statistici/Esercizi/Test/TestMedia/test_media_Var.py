# Test sulla media con varianza nota (Z-test)

# PDF 6, pag 18

import numpy as np
from scipy.stats import norm

data = np.array([51.0, 50.2, 49.5, 48.7, 50.2, 50.5, 49.6, 51.1, 50.6, 49.1, 53.1, 50.4, 
                 49.3, 48.9, 50.3, 51.8, 51.3, 48.5, 49.3, 55.1, 53.1, 52.5, 55.1, 50.6])

sig = 2 # deviazione standard
mu_0 = 50

# Calcolo la media e la dimensione del campione
mu = np.mean(data)
n = len(data)

# Calcolo il valore di Z
Z = (mu - mu_0) / sig * np.sqrt(n)
print('Z =', Z)
print('Media campionaria =', mu)

"""
A questo punto, per valutare se accettare o rifiutare l'ipotesi nulla,
calcoliamo il valore critico di Z e confrontiamolo con il valore calcolato.

Devi vedere se si tratta di un test bilaterale o unilaterale.
Queste cose si vedono nel pdf, ma in generale:
- bilaterale: H0: mu = mu_0, H1: mu != mu_0
- unilaterale: H0: mu = mu_0, H1: mu > mu_0 oppure H1: mu < mu_0
N.B. il test unilaterale vuole che ci sia una certa differenza tra mu e mu_0
In questo caso, il test è bilaterale perché la differenza tra mu e mu_0 è poca.
"""

# Test bilaterale con alpha = 0.05
alpha = 0.05
PHI = norm.ppf(1 - alpha/2)
print('PHI =', PHI)
if -PHI < Z < PHI: # |Z| < PHI -> accetto H0
    print('Accetto H0')
else:
    print('Rifiuto H0') # |Z| > PHI -> rifiuto H0

# In queso caso si rigetta l'ipotesi nulla, perché |Z| > PHI

# Test bilaterale con alpha = 0.01
alpha = 0.01
PHI = norm.ppf(1 - alpha/2)
print('PHI =', PHI)
if -PHI < Z < PHI: # |Z| < PHI -> accetto H0
    print('Accetto H0')
else:
    print('Rifiuto H0')
# In questo caso si accetta l'ipotesi nulla, perché |Z| < PHI

# Si deve calcolare il p-value
# La formula per calcolare il p-value dipende dal tipo di test (bilateral o unilaterale)
# In questo caso, il test è bilaterale, quindi il p-value è:
p_value = 2 * (1 - norm.cdf(np.abs(Z)))
print('p-value =', p_value)

"""
L'ultima parte dell'esercizio chiede di supporre che si voglia
impostare il test in modo che la media differisca da 50 per al più 1
e che il test affermi con probabilità del 90% e significatività del 5%
che la media sia diversa da 50.
"""

alpha = 0.05
beta = 0.1 # 1 - 0.9
delta = 1

PHI = norm.ppf(1 - alpha/2)
Z_90 = -PHI-delta/sig*np.sqrt(n)
print('Z_90 =', Z_90)

# Infine si chiede di calcolare la dimensione del campione per ottenere beta = 0.1
# Anche in questo caso, la formula dipende dal tipo di test (bilateral o unilaterale)
# In questo caso, il test è bilaterale, quindi la formula è:
PHI_B = norm.ppf(1 - beta)
dim = (PHI_B + PHI)**2 * sig**2 / delta**2
print('Dimensione del campione =', dim)