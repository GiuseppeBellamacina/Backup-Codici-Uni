# Metodo Hit or Miss
# Serve a calcolare l'integrale definito di
# una funzione f(x) in un intervallo [a,b]

# PDF 8, pag 33

import numpy as np
from scipy.stats import norm

def f(x):
    return norm.pdf(x, loc=0, scale=1)

def max_f(f, a, b):
    x = np.linspace(a, b, 1000)
    return max(f(x))

def hit_or_miss(f, a, b, M, N):
    NS = 0
    for i in range(N):
        x = np.random.uniform(a, b)
        y = np.random.uniform(0, M)
        if f(x) > y:
            NS += 1
    p = NS / N
    I = p * M * (b - a)
    return I

a = 0.5
b = 2

N = 10**5

M = max_f(f, a, b)
I = hit_or_miss(f, a, b, M, N)
print("Hit or Miss: ", I)

# Si può confrontare con il valore esatto
# dell'integrale definito
I_esatto = norm.cdf(b, loc=0, scale=1) - norm.cdf(a, loc=0, scale=1)
print("Integrale esatto: ", I_esatto)