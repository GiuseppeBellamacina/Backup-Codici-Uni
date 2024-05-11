# Numeri pseudo-casuali distribuiti uniformemente

# PDF 8, pag 15

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import uniform, probplot

a = 1
b = 3
N = 10**4
X = np.random.rand(N) # N numeri casuali distribuiti uniformemente tra 0 e 1

Y = a + X * (b - a)

xx = np.linspace(a, b, 1000)
yy = uniform.pdf(xx, a, b - a)

plt.hist(Y, density=True)
plt.plot(xx, yy, 'r')
plt.title('Distribuzione uniforme')
plt.show()

probplot(Y, dist=uniform, plot=plt)
plt.show()