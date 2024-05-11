"""
C'è n'azienda che fa lampadine in scatole da 4.
Il 5% delle lampadine è difettoso.
1. Qual è la probabilità che una scatola contenga una lampadina difettosa?
2. Qual è la probabilità che una scatola contenga al massimo 2 lampadine difettose?
3. Se l'azienda produce scatole da 40, qual è la media delle lampadine difettose per scatola?
"""

# La distribuzione binomiale è una distribuzione di probabilità discreta
# che descrive il numero di successi in una sequenza di n prove indipendenti tra loro.

from scipy.stats import binom

# binom.pmf(k, n, p), k = numero di successi, n = numero di prove, p = probabilità di successo

p = 0.05
n_conf = 4

# 1
p1 = binom.pmf(1, n_conf, p)
print(p1)

# 2
p2 = sum([binom.pmf(i, n_conf, p) for i in range(3)])
print(p2)

# 3
n_conf2 = 40
media = n_conf2 * p
print(media)