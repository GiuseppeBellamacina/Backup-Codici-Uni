"""
PDF 5
Esercizio sul monitoraggio delle polveri sottili.
Calcolare la funzione di ripartizione empirica e 
i quantili per determinati livelli di probabilità.
"""

import numpy as np
import matplotlib.pyplot as plt

# Definizione dei dati
data = np.array([0, 0.5, 1, 1.5, 2])
freq = np.array([10, 8, 6, 3])

# Calcolo della CDF empirica
cdf = np.cumsum(freq) / np.sum(freq)
cdf = np.insert(cdf, 0, 0) # Aggiunta del valore iniziale

# Calcolo dei quantili per determinati livelli di probabilità
alpha = np.array([0.25, 0.5, 0.75])
q_alpha = np.interp(alpha, cdf, data) # Interpolazione lineare

# Plot della CDF empirica e dei quantili
plt.plot(data, cdf, label='F(x)')
plt.scatter(q_alpha, alpha, color='red', label='q_alpha')
plt.scatter(data, cdf, color='blue', label='data')
plt.xlabel('valore polveri')
plt.ylabel('funzione di ripartizione empirica')
plt.title('Indagine polveri sottili')
plt.legend()
plt.show()