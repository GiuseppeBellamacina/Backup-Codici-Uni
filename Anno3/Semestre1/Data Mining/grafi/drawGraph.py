from os import system
from random import randint

class Vertex:
    def __init__(self, name):
        self.name = name
        self.edges = []
    
    def addEdge(self, edge):
        self.edges.append(edge)
        
class Edge:
    def __init__(self, vertex1, vertex2):
        self.vertex1 = vertex1
        self.vertex2 = vertex2

class Graph:
    def __init__(self, vertices, edges):
        self.vertices = vertices
        self.edges = edges
    
    def addVertex(self, vertex):
        self.vertices.append(vertex)
        
    def addEdge(self, edge):
        self.edges.append(edge)
        
    def draw(self):
        f = open("graph.dot", "w")
        f.write("graph G {\n")
        f.write("node [shape=circle]\n")
        for vertex in self.vertices:
            f.write("  " + vertex.name + "\n")
        for edge in self.edges:
            f.write("  " + edge.vertex1.name + " -- " + edge.vertex2.name + "\n")
        f.write("}\n")
        f.close()
        system("dot -Tpng graph.dot -o graph.png")
        system("graph.png")
        
    def randomize(self, numVertices, numEdges):
        for i in range(numVertices):
            self.addVertex(Vertex(str(i)))
        for i in range(numEdges):
            vertex1 = self.vertices[randint(0, numVertices - 1)]
            vertex2 = self.vertices[randint(0, numVertices - 1)]
            self.addEdge(Edge(vertex1, vertex2))
    
    def complete(self, numVertices):
        for i in range(numVertices):
            self.addVertex(Vertex(str(i)))
        for i in range(numVertices):
            for j in range(i + 1, numVertices):
                self.addEdge(Edge(self.vertices[i], self.vertices[j]))

def main():
    graph = Graph([], [])
    graph.complete(5)
    graph.draw()

main()