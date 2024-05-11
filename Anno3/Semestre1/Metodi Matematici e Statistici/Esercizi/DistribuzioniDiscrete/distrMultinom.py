"""
Calcolare la probabilità che lanciando 4 volte un dado non truccato:
Esca 3 volte il numero 6 e 1 volta il numero 2.
"""

# La distribuzione multinomiale è una distribuzione di probabilità discreta
# che descrive il numero di successi in un numero fisso di prove, in cui
# ciascuna prova può avere più di due esiti possibili.
# Si tratta di una generalizzazione della distribuzione binomiale.

from scipy.stats import multinomial

# multinomial.pmf(x, n, p), x = lista di esiti, n = numero di prove, p = lista delle probabilità di successo

"""
x si crea nel seguente modo:
- 0 volte il numero 1
- 1 volta il numero 2
- 0 volte il numero 3
- 0 volte il numero 4
- 0 volte il numero 5
- 3 volte il numero 6
"""

x = [0, 1, 0, 0, 0, 3]
n = 4
p = [1/6]*6

res = multinomial.pmf(x, n, p)
print(res)