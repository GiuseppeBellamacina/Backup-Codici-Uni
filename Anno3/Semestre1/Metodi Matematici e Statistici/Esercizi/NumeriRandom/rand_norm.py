# Numeri pseudo-casuali con distribuzione normale

# PDF 8, pag 17

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm, probplot

N = 10**5
X = np.random.rand(N)

xi1 = X[0:int(N/2)]
xi2 = X[int(N/2):N]
eta1 = np.sqrt(-2*np.log(xi1)) * np.cos(2*np.pi*xi2)
eta2 = np.sqrt(-2*np.log(xi1)) * np.sin(2*np.pi*xi2)

Y = np.concatenate((eta1, eta2)) # Y = N(0, 1)
Y = 1 + np.sqrt(2)*Y # Y = N(1, 2)

"""
Per avere Y = N(1, 2):
Y = 1 + np.sqrt(2)*Y
Ste cose sono nelle slide
E poi si fa yy = norm.pdf(xx, 1, np.sqrt(2))
"""

xx = np.linspace(-5, 5, 1000)
yy = norm.pdf(xx, 0, 1)
yy2 = norm.pdf(xx, 1, np.sqrt(2))


plt.hist(Y, bins=100, density=True)
plt.plot(xx, yy, 'r', label='N(0, 1)')
plt.plot(xx, yy2, 'g', label='N(1, 2)')
plt.title('Distribuzione normale')
plt.legend()
plt.show()

probplot(Y, dist=norm, plot=plt)
plt.show()