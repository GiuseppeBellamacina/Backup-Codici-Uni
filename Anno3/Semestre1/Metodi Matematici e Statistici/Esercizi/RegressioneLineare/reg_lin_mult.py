# Esericizo sulla regressione lineare multipla
# PDF 7, pag 45

"""
ATTENZIONE:
Alcune formule sono le stesse della versione semplice, altre no,
in più qui si deve fare il modello quadratico, di cui mancano le formule.
"""

import numpy as np
from scipy.stats import t, norm, probplot
import matplotlib.pyplot as plt

# Importo i dati
DATA = np.loadtxt("DATA_reg_lin_2.dat")
x = DATA[:, 0]
y = DATA[:, 1]

# Passo al calcolo dei coefficienti di regressione
n = len(x)
x_bar = np.mean(x)
y_bar = np.mean(y)
sig_xy = np.sum((x - x_bar) * (y - y_bar)) / n
sig_x2 = np.sum((x - x_bar)**2) / n
sig_y2 = np.sum((y - y_bar)**2) / n

b0 = y_bar - sig_xy / sig_x2 * x_bar
b1 = sig_xy / sig_x2

# -----------------------------------------------------
y_hat = b0 + b1 * x
r = y - y_hat
s2 = np.sum(r**2) / (n-2)
R2 = sig_xy**2 / (sig_x2*sig_y2)
print("Il coefficiente di determinazione è R2 = ", R2)
# -----------------------------------------------------

# Questi sono i coefficienti di regressione lineare semplice
# A noi servono quelli della regressione lineare multipla

x1 = np.ones(n) # Vettore di 1
x2 = x # Vettore delle x
X = np.zeros((n, 2))
X[:, 0] = x1
X[:, 1] = x2

XX = np.linalg.pinv(X) # Pseudo-inversa di X
b = np.dot(XX, y) # Coefficienti di regressione
y_hat = np.dot(X, b) # Valori stimati

# Creo il grafico
xx = np.linspace(min(x), max(x), 100)
yy = b[0] + b[1] * xx

plt.plot(x, y, 'o')
plt.plot(xx, yy, 'r')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Regressione lineare multipla')
plt.show()

# Calcolo il coefficiente di determinazione
R2 = np.sum((y_hat - y_bar)**2) / np.sum((y - y_bar)**2)
print("Il coefficiente di determinazione è R2 = ", R2)

# Test di indipendenza
# H0 : b1 = 0
# H1 : b1 <> 0

# ATTENZIONE:
# quando si parla di n-k, n è il numero di osservazioni e k è il numero di parametri per ogni n
# in questo caso n = 10 e k = 2

M = np.linalg.inv(np.dot(X.T, X))
m = M[1, 1] # perché si considera M[i,i] con i che va da 1 a k
r = y - y_hat
s2 = np.sum(r**2) / (n - 2) # n - k
T1 = b[1] / np.sqrt(s2 * m)

alpha = 0.05
tt = t.ppf(1 - alpha / 2, n - 2)
print("T1 = ", T1)
print("tt = ", tt)

if abs(T1) >= tt:
    print("H0 è da rifiutare")
else:
    print("H0 non è da rifiutare")

# Vediamo se i residui sono normalmente distribuiti
probplot(r, plot=plt)
plt.title('Residui')
plt.show()

#-------------------------------------------------
# Da qui in poi le formule non sono nelle slide
#-------------------------------------------------

# Adottiamo il modello quadratico
# y = b0 + b1 * x + b2 * x^2 + e

X2 = np.zeros((n, 3))
X2[:, 0] = x1
X2[:, 1] = x2
X2[:, 2] = x2**2

XX2 = np.linalg.pinv(X2) # Pseudo-inversa di X2
b2 = np.dot(XX2, y) # Coefficienti di regressione
y_hat2 = np.dot(X2, b2) # Valori stimati
# E fino a qui è più o meno uguale a prima

# Facciamo il grafico
xx = np.linspace(min(x), max(x), 100) # Stesso di prima
yy = b[0] + b[1]*xx # Stesso di prima
yy2 = b2[0] + b2[1]*xx + b2[2]*xx**2 # Nuovo

fig, (ax1, ax2) = plt.subplots(1, 2)
ax1.plot(x, y, 'o')
ax1.plot(xx, yy, 'r')
ax1.set_xlabel('x')
ax1.set_ylabel('y')
ax1.set_title('Regressione lineare multipla')

ax2.plot(x, y, 'o')
ax2.plot(xx, yy2, 'r')
ax2.set_xlabel('x')
ax2.set_ylabel('y')
ax2.set_title('Regressione quadratica')
plt.show()

# Calcoliamo il coefficiente di determinazione
R2 = np.sum((y_hat2 - y_bar)**2) / np.sum((y - y_bar)**2)
print("Il coefficiente di determinazione è R2 = ", R2)
# Si nota che R2 è maggiore rispetto al caso lineare, quindi il modello quadrato è migliore

# Test di indipendenza
# H0 : b1 = 0
# H1 : b1 <> 0

M2 = np.linalg.inv(np.dot(X2.T, X2))
m1 = M2[1, 1]
m2 = M2[2, 2]
r2 = y - y_hat2
s22 = np.sum(r2**2) / (n - 3) # n - k

T1_2 = b2[1] / np.sqrt(s22 * m1)
T2_2 = b2[2] / np.sqrt(s22 * m2)

tt = t.ppf(1 - alpha / 2, n - 3)

print("T1_2 = ", T1_2)
print("T2_2 = ", T2_2)
print("tt = ", tt)

if abs(T2_2) >= tt or abs(T1_2) >= tt:
    print("H0 è da rifiutare")
else:
    print("H0 non è da rifiutare")