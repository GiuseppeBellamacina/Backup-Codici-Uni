# Numeri pseudo-casuali con distribuzione esponenziale

# PDF 8, pag 16

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import expon, probplot

l = 2
N = 10**5
X = np.random.rand(N)

Y = -np.log(X) / l

xx = np.linspace(0, 5, 1000)
yy = expon.pdf(xx, 0, scale=1/l)

plt.hist(Y, bins=100, density=True)
plt.plot(xx, yy, 'r')
plt.title('Distribuzione esponenziale')
plt.show()

probplot(Y, dist=expon, plot=plt)
plt.show()