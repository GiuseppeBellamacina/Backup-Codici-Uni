#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#define N 100

using namespace std;

template <class T>
class Node{
    public:
        T data;
        int index;
        vector<Node<T>*> adj;
        Node(){}
        Node(int index, T data){
            this->index = index;
            this->data = data;
        }
};

template <class T>
class Graph{
    public:
        int numNodes;
        int nIndex;
        Node<T> **nodes; // array di puntatori a nodi
        int **weights; // matrice di adiacenza
        Graph(){}
        Graph(int n) : numNodes(n){
            nodes = new Node<T>*[numNodes];
            weights = new int*[numNodes];
            for(int i = 0; i < numNodes; i++){
                weights[i] = new int[numNodes];
                for(int j = 0; j < numNodes; j++){
                    weights[i][j] = INT_MAX;
                }
            }
        }
        Graph<T>* addNode(T data){
            if (nIndex == numNodes){
                cout << "Numero massimo di nodi raggiunto" << endl;
                return this;
            }
            nodes[nIndex] = new Node<T>(nIndex, data);
            weights[nIndex][nIndex] = 0;
            nIndex++;
            return this;
        }
        int findIndex(T data){
            for(int i = 0; i < numNodes; i++){
                if(nodes[i]->data == data){
                    return i;
                }
            }
            return -1;
        }
        Graph<T>* addEdge(T a, T b, int weight){
            int i = findIndex(a);
            int j = findIndex(b);
            nodes[i]->adj.push_back(nodes[j]);
            nodes[j]->adj.push_back(nodes[i]);
            weights[i][j] = weight;
            weights[j][i] = weight;
            return this;
        }
        void adjPrint(){
            cout << "\t";
            for(int i = 0; i < numNodes; i++)
                cout << i << "\t";
            cout << endl;
            for(int i=0; i<numNodes; i++){
                cout << i << "\t";
                for(int j=0; j<numNodes; j++){
                    if (weights[i][j] == INT_MAX)
                        cout << "inf\t";
                    else
                        cout << weights[i][j] << "\t";
                }
                cout << endl;
            }
        }
        void gPrint(){
            for(int i = 0; i < numNodes; i++){
                cout << nodes[i]->data << ": ";
                for(int j = 0; j < nodes[i]->adj.size(); j++){
                    cout << nodes[i]->adj[j]->data << " ";
                }
                cout << endl;
            }
        }
};

template <class T>
int dijkstra(Graph<T>* g, T a, T b){
    int i = g->findIndex(a);
    int j = g->findIndex(b);
    int *d = new int[g->numNodes];
    int *p = new int[g->numNodes];
    bool *s = new bool[g->numNodes];
    for(int k = 0; k < g->numNodes; k++){
        d[k] = INT_MAX;
        p[k] = -1;
        s[k] = false;
    }
    d[i] = 0;
    p[i] = -1;
    s[i] = true;
    int u = i;
    while(u != j){
        for(int k = 0; k < g->nodes[u]->adj.size(); k++){
            int v = g->nodes[u]->adj[k]->index;
            if(!s[v] && d[v] > d[u] + g->weights[u][v]){
                d[v] = d[u] + g->weights[u][v];
                p[v] = u;
            }
        }
        int min = INT_MAX;
        for(int k = 0; k < g->numNodes; k++){
            if(!s[k] && d[k] < min){
                min = d[k];
                u = k;
            }
        }
        s[u] = true;
    }
    return d[j];
}



int main(){
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    for(int i=0; i<N; i++){
        int nodes, edges;
        in >> nodes >> edges;
        string type;
        in >> type;
        if (type == "int"){
            Graph<int> *g = new Graph<int>(nodes);
            for(int j=0; j<nodes; j++){
                int data;
                in >> data;
                g->addNode(data);
            }
            for(int j=0; j<edges; j++){
                int a, b, weight;
                char tmp;
                in >> tmp >> a >> b >> weight >> tmp;
                g->addEdge(a, b, weight);
            }
            int x, y;
            in >> x >> y;
            out << dijkstra(g, x, y) << endl;
        }
        if (type == "double"){
            Graph<double> *g = new Graph<double>(nodes);
            for(int j=0; j<nodes; j++){
                double data;
                in >> data;
                g->addNode(data);
            }
            for(int j=0; j<edges; j++){
                double a, b;
                int weight;
                char tmp;
                in >> tmp >> a >> b >> weight >> tmp;
                g->addEdge(a, b, weight);
            }
            double x, y;
            in >> x >> y;
            out << dijkstra(g, x, y) << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}