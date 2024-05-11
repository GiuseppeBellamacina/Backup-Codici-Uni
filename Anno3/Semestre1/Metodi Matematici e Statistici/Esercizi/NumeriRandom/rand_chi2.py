import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chi2, probplot

# X^2(1)

N = 10**5
X = np.random.rand(N)

xi1 = X[0:int(N/2)]
xi2 = X[int(N/2):N]
eta1 = np.sqrt(-2*np.log(xi1)) * np.cos(2*np.pi*xi2)
eta2 = np.sqrt(-2*np.log(xi1)) * np.sin(2*np.pi*xi2)

Y = np.concatenate((eta1, eta2))
Y = Y**2

xx = np.linspace(0, 10, 1000)
yy = chi2.pdf(xx, 1)

plt.hist(Y, bins=100, density=True)
plt.plot(xx, yy, 'r')
plt.title('Distribuzione chi2')
plt.show()

probplot(Y, dist=chi2, sparams=(1,), plot=plt)
plt.show()