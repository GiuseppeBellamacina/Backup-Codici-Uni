import matplotlib.pyplot as plt # pip install matplotlib
from os import system
from random import randint

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Cluster:
    def __init__(self, point):
        self.centroid = Point(point.x, point.y)
        self.totalX = 0
        self.totalY = 0
        self.points = []
        self.numPoints = 0
        self.addPoint(point)
    
    def setPosition(self, x, y):
        self.centroid.x = x
        self.centroid.y = y

    def addPoint(self, point):
        self.points.append(point)
        self.totalX += point.x
        self.totalY += point.y
        self.numPoints += 1
        self.setPosition(self.totalX/self.numPoints, self.totalY/self.numPoints)

def combineClusters(clusters):
    i, j = findMinDist(clusters)
    for point in clusters[j].points:
        clusters[i].addPoint(point)
    clusters.pop(j)
    return clusters

def findMinDist(clusters):
    minDist = float('inf')
    ret1 = ret2 = -1
    for i in range(len(clusters)):
        for j in range(len(clusters)):
            if i == j:
                continue
            dist = distance(clusters[i].centroid, clusters[j].centroid)
            if dist < minDist:
                minDist = dist
                ret1 = i
                ret2 = j
    return ret1, ret2

def distance(point1, point2):
    return ((point2.x - point1.x)**2 + (point2.y - point1.y)**2)**0.5

def plotClusters(clusters):
    plt.figure()
    plt.title('Clustering')
    plt.xlabel('X')
    plt.ylabel('Y')
    colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k', 'orange', 'purple', 'brown', 'pink', 'gray', 'olive', 'lime', 'teal', 'navy']
    for i, cluster in enumerate(clusters):
        x = [point.x for point in cluster.points]
        y = [point.y for point in cluster.points]
        plt.scatter(x, y, c=colors[i % len(colors)], label=f'Cluster {i + 1}')
        plt.scatter(cluster.centroid.x, cluster.centroid.y, c=colors[i % len(colors)], marker='x')
    #plt.legend()
    plt.show()

def main():
    system('cls')
    n_points = 300
    n_clusters = 16
    
    points = [Point(randint(0, 99), randint(0, 99)) for _ in range(n_points)]
    clusters = [Cluster(point) for point in points]

    while len(clusters) > n_clusters:
        clusters = combineClusters(clusters)
        if len(clusters) % n_clusters*5 == 0:
            system('cls')
            print(f'Clusters rimanenti: {len(clusters)}')

    plotClusters(clusters)

if __name__ == "__main__":
    main()