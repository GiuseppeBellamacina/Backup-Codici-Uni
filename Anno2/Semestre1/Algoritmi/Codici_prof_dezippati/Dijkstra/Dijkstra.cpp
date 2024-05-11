#include "Graph.cpp"
#include "Heap.cpp"

using namespace std;

template <class T> class PairMinHeap : public MinBinaryHeap<T>
{
public:
	PairMinHeap(int size) : MinBinaryHeap<T>(size) {}
	PairMinHeap(T** A, int size) : MinBinaryHeap<T>(A, size) {}
	double compare(T* a, T* b)
	{
		return (double)( ((*b).second) - ( (double) (*a).second) );
	}
	void printKey(int i) const
	{
		cout << (*(this->getPriorityQueue())[i]).first << " " << (*(this->getPriorityQueue())[i]).second << endl;
	}

	int findIndex(int index)
	{
		for (int i = 1; i <= this->size(); i++)
		{
			if((*(this->getPriorityQueue())[i]).first == index)
			  return i;
		}
		return -1;
	}
};




template <class H, class T> int Dijkstra(Graph<H, T>* graph, H keysrc, T*& distances, int*& predecessors)
{
	int src = graph->findIndex(keysrc);
	if (src == -1)
		return 0;
	int V = graph->getCurrentNodeNumber();
	distances = new T[V];
	predecessors = new int[V];	
	PairMinHeap<pair<int,T>>*q  = new PairMinHeap<pair<int,T>>(V);
	// Initially distance is for each node // manage the usage of the flag
	for (int i = 0; i < V; i++)
	{
		if (i == src)		
			distances[i] = 0;		
		else		
			distances[i] = INT_MAX;
		predecessors[i] = -1;		
		q->enqueue(pair<int, T>(i, distances[i]));
	}	
	while (q->size())
	{
		pair<int, T> top = *(q->extractMin());
		if (top.second == INT_MAX)
			break;
		int tmp = top.first;
		for (int i = 0; i < V; i++) //looking for neighboors
		{
			if (graph->getGraphIndexMatrix()[tmp][i] == 1)
			{
				T newval = distances[tmp] + graph->getGraphWeightMatrix()[tmp][i];
				if (newval < distances[i])
				{
					distances[i] = newval;
					predecessors[i] = tmp;
					int index = q->findIndex(i);
					q->decreaseKey(index, pair<int,T>(i,newval));
				}
			}
		}
	}
    delete q;
	return 1;
}





template <class H, class T> void printDistances(Graph<H, T>* graph, H key, T* distances, int* predecessors)
{
	cout << "Printing Dijkstra distances" << endl;
	if (predecessors == NULL || graph->findIndex(key) < 0)
		return;	
	int src = graph->findIndex(key);
	int V = graph->getCurrentNodeNumber();
	for (int i = 0; i < V; i++)
		if (i != src)
		{
			cout << "Distance from " << key << " to " << *(graph->getKey(i)) << " is ";
			if (distances[i] != INT_MAX)
				cout << distances[i] << endl;
			else
				cout << "INF" << endl;
		}
	cout << "Printing predecessor list" << endl;
	for (int i = 0; i < V; i++)
	{
	  if(i!=src)
		if (predecessors[i] > -1 )
			cout << "The predecessor of " << *(graph->getKey(i)) << " is " << *(graph->getKey(predecessors[i])) << endl;
		else 
			cout<< *(graph->getKey(i)) << " is unreacheable" << endl;		
	}
	return;
}


int main()
{
	Graph<char, int>* g = new Graph<char, int>(5);
	g->addNode('A')->addRootNode('C')->addRootNode('B')->addNode('D')->addNode('E');
	g->addEdge('C', 'B', 4)->addEdge('C', 'A', 19)->addEdge('B', 'A', 1)->addEdge('B', 'D', 2)->addEdge('A', 'D', 9)->addEdge('D', 'E', 3)->addEdge('B', 'E', 8)->addEdge('E', 'C', 1);
	g->print();
	int* distances = NULL;
	int* predecessors = NULL;
	if (Dijkstra(g, 'B', distances, predecessors))
		printDistances(g, 'B', distances, predecessors);
	return 1;
}