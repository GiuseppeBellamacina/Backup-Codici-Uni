# Intervallo di confidenza senza la deviazione standard
# Si usa la distribuzione t di Student

# PDF 5
# Esercizio con i MegaPascal

import numpy as np
from scipy.stats import t, norm, probplot
import matplotlib.pyplot as plt

data = np.array([19.8, 10.1, 14.9, 7.5, 15.4, 15.4, 15.4, 18.5, 7.9, 12.7, 11.9, 11.4, 
                 11.4, 14.1, 17.6, 16.7, 15.8, 19.5, 8.8, 13.6, 11.9, 11.4])

# Calcolo della media
media = np.mean(data)

# Calcolo della deviazione standard
std = np.std(data, ddof=1) # ddof=1 per avere la deviazione standard campionaria

# L'esercizio chiede di verificare che i dati siano distribuiti normalmente
# Si fa un grafico di probabilità
probplot(data, dist=norm, plot=plt)
plt.show() # I dati sembrano distribuiti normalmente

# Passiamo al calcolo dell'intervallo di confidenza

# Dimensione del campione
n = len(data)

# Gradi di libertà
df = n - 1 # n - 1 perché si usa la deviazione standard campionaria

# Funzione per il calcolo dell'intervallo di confidenza
def conf_int(avg, std, df, n, conf):
    alpha = 1 - conf
    phi = t.ppf(1 - alpha/2, df)
    lower = avg - phi * std / np.sqrt(n)
    upper = avg + phi * std / np.sqrt(n)
    return lower, upper

"""
L'intervallo di confidenza si calcola come per la versione con la
distributione normale, ma si usa la distribuzione t di Student,
quindi includendo i gradi di libertà.
"""

# Intervallo di confidenza al 95%
conf = 0.95
lower, upper = conf_int(media, std, df, n, conf)
print(f"Intervallo di confidenza al {conf*100}%: [{lower:.2f}, {upper:.2f}]")