"""
La memoria di un computer è cmposta da 30 hard disk,
ognuno dei quali contiene 100 file.
Un programma dovrà accedere a 28 di questi file (tutti diversi).
1. Qual è la probabilità che non ci siano file provenienti dall'hard disk 1?
2. Qual è la probabilità del punto 1 nel caso in cui i file possano ripetersi?
"""

# La distribuzione ipergeometrica è una distribuzione di probabilità discreta
# che descrive il numero di successi in un campione di dimensione fissa senza sostituzione.

from scipy.stats import hypergeom, binom

# hypergeom.pmf(k, N, n, K), k = numero di successi, N = numero di elementi totali, n = numero di successi nel campione, K = numero di prove
# binom.pmf(k, n, p), k = numero di successi, n = numero di prove, p = probabilità di successo

# 1
k = 0
N = 30*100
n = 100
K = 28

p1 = hypergeom.pmf(k, N, n, K)
print(p1)

# 2
p = 1/30
p2 = binom.pmf(0, 28, p)
print(p2)