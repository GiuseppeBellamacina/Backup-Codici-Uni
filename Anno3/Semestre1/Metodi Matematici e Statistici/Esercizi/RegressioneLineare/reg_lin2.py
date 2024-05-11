# Secondo esercizio sulla regressione lineare
# PDF 7, pag 34

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import t, norm, probplot

DATA = np.array([[0., 19.5],[1., 22.1],[2., 24.3],[3., 25.7],[4., 26.1],[5., 28.5], 
                 [6., 30.],[7., 32.1],[8., 32.7],[9., 32.7],[10., 35.]])
x = DATA[:,0]
y = DATA[:,1]

x_bar = np.mean(x)
y_bar = np.mean(y)
n = len(x)

sig_xy = np.sum((x - x_bar)*(y - y_bar)) / n
sig_x2 = np.sum((x - x_bar)**2) / n
sig_y2 = np.sum((y - y_bar)**2) / n

b0 = y_bar - (sig_xy / sig_x2)*x_bar
b1 = sig_xy / sig_x2

xx = np.linspace(min(x), max(x), 1000)
yy = b0 + b1*xx

plt.plot(xx, yy, 'r')
plt.plot(x, y, 'o', color='b')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Regressione lineare")
plt.show()

y_hat = b0 + b1*x
r = y - y_hat

plt.plot(x, r, 'o', color='b')
plt.xlabel("x")
plt.ylabel("Residui")
plt.title("Residui")
plt.show()

s2 = np.sum(r**2) / (n-2)

probplot(r, dist="norm", plot=plt)
plt.show()

alpha = 0.05
T = t.ppf(1-alpha/2, n-2)
T1 = np.sqrt(n)*b1*np.sqrt(sig_x2)/np.sqrt(s2)
print("T = ", T)
print("T1 = ", T1)

if abs(T1) >= T:
    print("Rifiuto H0")
else:
    print("Accetto H0")

R2 = sig_xy**2 / (sig_x2*sig_y2)
print("R2 = ", R2)