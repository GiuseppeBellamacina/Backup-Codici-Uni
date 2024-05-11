# Intervallo di confidenza con Varianza Conosciuta
# Si usa la distribuzione normale

# PDF 5
# Esercizio della misurazione del voltaggio

import numpy as np
from scipy.stats import norm # si usa la distribuzione normale

data = np.array([11., 13.2, 12.3, 10.9, 13., 10.5, 12.3, 13., 13.15])

# Calcolo della media
avg = np.mean(data)

# Deviazione standard conosciuta
sigma = 1

# Dimensione del campione
n = len(data)

# Funzione per il calcolo dell'intervallo di confidenza
def conf_int(avg, sigma, n, conf):
    alpha = 1 - conf
    phi = norm.ppf(1 - alpha/2)
    lower = avg - phi * sigma / np.sqrt(n)
    upper = avg + phi * sigma / np.sqrt(n)
    return lower, upper

"""
Per calcolare l'intervallo di confidenza ho bisogno della media,
della deviazione standard, della dimensione del campione e del
livello di confidenza (con cui calcolare alpha).
"""

# Calcolo dell'intervallo di confidenza al 95%
conf = 0.95
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")

# Calcolo dell'intervallo di confidenza al 99%
conf = 0.99
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")

# Ripetiamo con sigma = 1.4
sigma = 1.4

conf = 0.95
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")

conf = 0.99
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")

# Riportiamo sigma = 1 ma mettiamo n = 20
sigma = 1
n = 20

conf = 0.95
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")

conf = 0.99
lower, upper = conf_int(avg, sigma, n, conf)
print(f"L'intervallo di confidenza al {conf*100}% è [{lower:.2f}, {upper:.2f}]")