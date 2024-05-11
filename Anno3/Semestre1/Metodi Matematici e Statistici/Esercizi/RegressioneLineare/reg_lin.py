# Primo esercizio di regressione lineare
# PDF 7, pag 33

# ATTENZIONE:
# Questo esercizio è giusto, basta guardare le formule
# e fare i calcoli. Non è difficile come sembra.

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import t, norm, probplot

# Prendo i dati
DATA = np.loadtxt("DATA_reg_lin.dat")
# Estraggo le colonne
x = DATA[:,1]
y = DATA[:,2]

# PARTE 1:
# Calcolo la retta di regressione
# Inizio dai coefficienti di regressione y = b0 + b1*x

x_bar = np.mean(x)
y_bar = np.mean(y)
n = len(x)

# Calcolo i vari sigma
sig_xy = np.sum((x - x_bar)*(y - y_bar)) / n
sig_x2 = np.sum((x - x_bar)**2) / n
sig_y2 = np.sum((y - y_bar)**2) / n

# Posso calcolare b0 e b1
b0 = y_bar - (sig_xy / sig_x2)*x_bar
b1 = sig_xy / sig_x2

# Definisco gli array per la retta
xx = np.linspace(min(x), max(x), 1000)
yy = b0 + b1*xx

# Disegno i punti e la retta
plt.plot(xx, yy, 'r')
plt.plot(x, y, 'o', color='b')
plt.xlabel("Peso corporeo")
plt.ylabel("Pressione sistolica")
plt.title("Regressione lineare")
plt.show()

# PARTE 1.5:
# Calcolo dei residui

y_hat = b0 + b1*x
r = y - y_hat

# Disegno i residui
plt.plot(x, r, 'o', color='b')
plt.xlabel("Peso corporeo")
plt.ylabel("Residui")
plt.title("Residui")
plt.show()

# Calcolo s2
s2 = np.sum(r**2) / (n-2)

# PARTE 2:
# Calcolo l'intervallo di confidenza per b0 e b1

alpha = 0.05
T = t.ppf(1-alpha/2, n-2)
b0_int = (b0 - np.sqrt(s2)*np.sqrt(1./n + x_bar**2./(n*sig_x2))*T, b0 + np.sqrt(s2)*np.sqrt(1./n + x_bar**2./(n*sig_x2))*T)
b1_int = (b1 - np.sqrt(s2)/np.sqrt(n*sig_x2)*T, b1 + np.sqrt(s2)/np.sqrt(n*sig_x2)*T)

print("Intervallo di confidenza per b0: ", b0_int)
print("Intervallo di confidenza per b1: ", b1_int)

# PARTE 2.5:
# Si può vedere se i residui sono normalmente distribuiti

probplot(r, dist=norm, plot=plt)
plt.show()

# PARTE 3:
# Test di significatività
# H0 : beta_1 = 0
# H1 : beta_1 <> 0

# T = t.ppf(1-alpha/2, n-2), già calcolato
T1 = np.sqrt(n)*b1*np.sqrt(sig_x2)/np.sqrt(s2)
print("T = ", T)
print("T1 = ", T1)

if abs(T1) >= T:
    print("Rifiuto H0")
else:
    print("Accetto H0")

# PARTE 4:
# Calcolo del coefficiente di determinazione

R2 = sig_xy**2 / (sig_x2*sig_y2)
print("R2 = ", R2)

# Se R2 non è vicino a 1, la retta non è un buon modello