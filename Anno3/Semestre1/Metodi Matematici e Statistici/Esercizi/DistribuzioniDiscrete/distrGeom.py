"""
Lancio di un dado non truccato.
1. Qual è la probabilità che esca 6 per la prima volta al lancio numero 3?
2. Sapendo che nei primi 3 lanci non si è avuto alcun 6, qual è la probabilità che esca 6 per la prima volta al lancio numero 5?
"""

# La distribuzione geometrica è una distribuzione di probabilità discreta
# che descrive il numero di prove necessarie per ottenere il primo successo.

from scipy.stats import geom

# geom.pmf(k, p), k = tempo di primo successo, p = probabilità di successo

# 1
p = 1/6
p1 = geom.pmf(3, 1/6)
print(p1)

# 2
p2 = geom.pmf(5-3, 1/6) # 5-3 perché il successo deve avvenire al lancio numero 5, quindi dopo 5-3 = 2 lanci
print(p2)