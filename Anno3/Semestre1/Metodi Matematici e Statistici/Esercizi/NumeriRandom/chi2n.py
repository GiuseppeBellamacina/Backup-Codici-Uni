import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chi2, probplot

# X^2(df)

df = 5

N = 10**5

def chi2_gen(N, df):
    X = np.zeros(N)
    for i in range(int(N/2)):
        eta = 0
        for j in range(df):
            x1 = np.random.rand()
            x2 = np.random.rand()
            eta += (np.sqrt(-2*np.log(x1)) * np.cos(2*np.pi*x2))**2
        X[i] = eta
    for i in range(int(N/2), N):
        eta = 0
        for j in range(df):
            x1 = np.random.rand()
            x2 = np.random.rand()
            eta += (np.sqrt(-2*np.log(x1)) * np.sin(2*np.pi*x2))**2
        X[i] = eta
    return X

X = chi2_gen(N, df)

xx = np.linspace(0, 10, 1000)
yy = chi2.pdf(xx, df)

plt.hist(X, bins=100, density=True)
plt.plot(xx, yy, 'r')
plt.title('Distribuzione chi2')
plt.show()

probplot(X, dist=chi2, sparams=(df,), plot=plt)
plt.show()