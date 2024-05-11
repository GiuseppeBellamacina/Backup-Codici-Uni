# Metodo del rigetto

# PDF 8, pag 25

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import probplot, norm, uniform, expon, chi2 # bastava importare probplot

def f(x):
    return (1 + np.cos(x)) / (2 * np.pi)

def max_f(f, a, b):
    x = np.linspace(a, b, 1000)
    return max(f(x))

def rigetto(f, a, b, M, N):
    ret = []
    while len(ret) < N:
        x = np.random.uniform(a, b)
        y = np.random.uniform(0, M)
        if 0 <= y and y < f(x):
            ret.append(x)
    return ret

a = -np.pi
b = np.pi
N = 10**5

M = max_f(f, a, b)
X = rigetto(f, a, b, M, N)

xx = np.linspace(a, b, 1000)
yy = f(xx)

plt.hist(X, bins=100, density=True)
plt.plot(xx, yy, 'r')
plt.show()

# Sta parte non centra con l'esercizio, ma può essere utile

fig, ax = plt.subplots(2, 2)
probplot(X, dist=norm, plot=ax[0, 0])
probplot(X, dist=uniform, plot=ax[0, 1])
probplot(X, dist=expon, plot=ax[1, 0])
probplot(X, dist=chi2, sparams=(2,), plot=ax[1, 1])
ax[0, 0].set_title('Normal')
ax[0, 1].set_title('Uniform')
ax[1, 0].set_title('Exponential')
ax[1, 1].set_title('Chi2')
plt.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
plt.show()