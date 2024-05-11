from os import system
from random import randint
value = 0
colors = ['\33[1;31m', '\33[1;32m', '\33[1;33m', '\33[1;34m', '\33[1;35m', '\33[1;36m', '\33[1;37m']
colorReset = '\33[0m'

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Cluster:
    def __init__(self, point):
        global value
        self.x = -1
        self.y = -1
        self.totalX = 0
        self.totalY = 0
        self.points = []
        self.numPoints = 0
        self.value = value
        value += 1
        self.addPoint(point)
    
    def setPosition(self, x, y):
        self.x = x
        self.y = y
    
    def addPoint(self, point):
        global colorIndex
        self.points.append(point)
        self.totalX += point.x
        self.totalY += point.y
        self.numPoints += 1
        self.setPosition(self.totalX/self.numPoints, self.totalY/self.numPoints)

def initMat():
    mat = []
    for i in range(0, 100):
        mat.append([])
        for j in range(0, 100):
            mat[i].append(" ")
    return mat

def matValueing(mat, clusters):
    for cluster in clusters:
        for point in cluster.points:
            mat[point.x][point.y] = cluster.value

def matColoring(mat, clusters):
    global colors, colorReset
    index = 0
    for cluster in clusters:
        for point in cluster.points:
            mat[point.x][point.y] = colors[index % len(colors)] + str(cluster.value) + colorReset
        index += 1

def printMat(mat, clusters):
    system('cls')
    matValueing(mat, clusters)
    matColoring(mat, clusters)
    for i in range(0, 100):
        for j in range(0, 100):
            print(mat[i][j], sep=' ', end='')
        print()

def distance(x1, y1, x2, y2):
    return ((x2-x1)**2 + (y2-y1)**2)**0.5

def findMinDist(clusters):
    minDist = 10000000
    ret1 = ret2 = -1
    for i in range(0, len(clusters)):
        for j in range(0, len(clusters)):
            if i == j:
                continue
            dist = distance(clusters[i].x, clusters[i].y, clusters[j].x, clusters[j].y)
            if dist < minDist:
                minDist = dist
                ret1 = i
                ret2 = j
    return ret1, ret2

def combineClusters(clusters):
    i, j = findMinDist(clusters)
    for point in clusters[j].points:
        clusters[i].addPoint(point)
    clusters.pop(j)
    return clusters

def main():
    system('cls')
    mat = initMat()
    points = []
    clusters = []
    
    n_points = 300
    n_clusters = 7
    
    for i in range(n_points):
        points.append(Point(randint(0,99), randint(0,99)))
    
    for point in points:
        clusters.append(Cluster(point))
    
    while len(clusters) > n_clusters:
        clusters = combineClusters(clusters)
        if len(clusters) % n_clusters*5 == 0:
            system('cls')
            print(f'Clusters rimanenti: {len(clusters)}')
    printMat(mat, clusters)
    
main()