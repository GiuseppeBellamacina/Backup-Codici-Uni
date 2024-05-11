from random import randint

def color(string):
    colors = ['\033[1;31m', '\033[1;32m', '\033[1;33m', '\033[1;34m', '\033[1;35m', '\033[1;36m']
    reset = '\033[0m'
    return colors[randint(0, 5)] + string + reset

def metodi(n):
    if n < 4:
        n = 4
    saltino = int(n / 2 - 1)
    print(color('*'), ' ' * saltino, sep='', end='')
    for i in range(int(n / 2 + 1)):
        print(color('*'), sep='', end='')
    print()
    for i in range(saltino):
        print(color('*'), ' ' * saltino, color('*'), sep='')
    for i in range(n):
        print(color('*'), sep='', end='')
    print()
    for i in range(saltino):
        print(' ' * (saltino + 1), color('*'), sep='', end='')
        print(' ' * saltino, color('*'), sep='')
    for i in range(int(n / 2 + 1)):
        print(color('*'), sep='', end='')
    print(' ' * saltino, color('*'), sep='')

metodi(17)