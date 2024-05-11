import matplotlib.pyplot as plt
from os import system
from random import randint

class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class Cluster:
    def __init__(self, point):
        self.centroid = Point(point.x, point.y, point.z)
        self.totalX = 0
        self.totalY = 0
        self.totalZ = 0
        self.points = []
        self.numPoints = 0
        self.addPoint(point)
    
    def setCentroid(self, x, y, z):
        self.centroid.x = x
        self.centroid.y = y
        self.centroid.z = z

    def addPoint(self, point):
        self.points.append(point)
        self.totalX += point.x
        self.totalY += point.y
        self.totalZ += point.z
        self.numPoints += 1
        self.setCentroid(self.totalX/self.numPoints, self.totalY/self.numPoints, self.totalZ/self.numPoints)

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
    return ((point2.x - point1.x)**2 + (point2.y - point1.y)**2 + (point2.z - point1.z)**2)**0.5

def plotClusters(clusters, vista):
    plt.figure()
    plt.title('Clustering')
    if vista == 'xy': # davanti
        plt.xlabel('x')
        plt.ylabel('y')
    elif vista == 'zy': # destra
        plt.xlabel('z')
        plt.ylabel('y')
    elif vista == 'xz': # sopra
        plt.xlabel('x')
        plt.ylabel('z')
    else:
        print('Vista non valida')
        return
    colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k', 'orange', 'purple', 'brown', 'pink', 'gray', 'olive', 'lime', 'teal', 'navy']
    for i, cluster in enumerate(clusters):
        if vista == 'xy':
            x = [point.x for point in cluster.points]
            y = [point.y for point in cluster.points]
            plt.scatter(cluster.centroid.x, cluster.centroid.y, c=colors[i % len(colors)], marker='x')
        elif vista == 'zy':
            x = [point.z for point in cluster.points]
            y = [point.y for point in cluster.points]
            plt.scatter(cluster.centroid.z, cluster.centroid.y, c=colors[i % len(colors)], marker='x')
        else:
            x = [point.x for point in cluster.points]
            y = [point.z for point in cluster.points]
            plt.scatter(cluster.centroid.x, cluster.centroid.z, c=colors[i % len(colors)], marker='x')
        plt.scatter(x, y, c=colors[i % len(colors)], label=f'Cluster {i + 1}')
    #plt.legend()
    plt.show(block=False)

def main():
    system('cls')
    n_points = 300
    n_clusters = 16
    
    points = [Point(randint(0, 99), randint(0, 99), randint(0, 99)) for _ in range(n_points)]
    clusters = [Cluster(point) for point in points]

    while len(clusters) > n_clusters:
        clusters = combineClusters(clusters)
        if len(clusters) % n_clusters*5 == 0:
            system('cls')
            print(f'Clusters rimanenti: {len(clusters)}')

    viste = ['xy', 'zy', 'xz']
    for vista in viste:
        plotClusters(clusters, vista)
    plt.show()

if __name__ == "__main__":
    main()