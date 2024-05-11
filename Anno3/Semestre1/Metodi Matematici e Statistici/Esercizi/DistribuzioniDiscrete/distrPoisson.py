"""
In un libro di 500 pagine sono distribuiti a caso
300 errori di stampa.
Qual è la probabilità che una data pagina contnga almeno 2 errori?
"""

# La distribuzione di Poisson è una distribuzione di probabilità discreta
# che si usa con uno schema di tipo successo-insuccesso, in cui il numero
# in cui si ha un alto numero di prove ed una bassa probabilità
# di successo in ciascuna prova.

from scipy.stats import poisson

# poisson.pmf(k, mu), k = numero di successi, mu = numero atteso di successi

# Devo calcolare P(X >= 2) = 1 - P(X < 2) = 1 - (P(X = 0) + P(X = 1))
p = 1 - sum([poisson.pmf(k, 300/500) for k in range(2)])
print(p)