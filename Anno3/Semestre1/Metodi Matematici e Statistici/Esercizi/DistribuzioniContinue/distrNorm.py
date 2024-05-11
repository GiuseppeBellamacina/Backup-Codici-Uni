"""
Un lago riceve acqua da due immissari e alimenta un emissario.
Misurando la portata in base alla variazione di quota dell'acqua,
i due immissari immettono con legge X1 ~ (1,1) e X2 ~ (2,2)
mentre l'emissario viene alimentato con legge X3 ~ (3/2, 3).
1. Si determini la legge seguita dall'altezza dell'acqua.
2. Qual è la probabilità che la quota superi il livello di guardia pari a 2?
3. Qual è la probabilità che la quota sia inferiore a 0.5?
"""

# La distribuzione normale è una distribuzione continua dove
# la media e la varianza si influenzano sommandosi tra loro

from scipy.stats import norm
import numpy as np

# norm.cdf(x, media, deviazione) -> ripartizione
# norm.sf(x, media, deviazione) -> sopravvivenza
# deviazione = np.sqrt(varianza) <-- IMPORTANTE

"""
Apriamo una digressione sulla differenza tra queste notazioni:
P(X=x) -> è la densità di probabilità discreta o continua
P(X<=x) -> è la funzione di ripartizione cumulativa
P(X>x) -> è la funzione di sopravvivenza
"""

# 1.
# Calcolo la media e la varianza sapendo che
# Y = X1 + X2 - X3

m1 = 1
m2 = 2
m3 = 1.5

media = m1 + m2 - m3

var1 = 1
var2 = 2
var3 = 3

varianza = var1 + var2 + var3 # la varianza si somma a prescindere

print(f"Y ~ N({media}, {varianza})")

# ---------------------------------------
# 2.
# P(Y>2) = 1 - P(Y<=2)
# Posso usare la sf oppure (1 - cdf)

# sf
res = norm.sf(2,media,np.sqrt(varianza))
print(res)

# 1 - cdf
# res = 1 - norm.cdf(2,media,np.sqrt(varianza))
# print(res)

# -----------------------------
# 3.

res = norm.cdf(0.5,media,np.sqrt(varianza))
print(res)