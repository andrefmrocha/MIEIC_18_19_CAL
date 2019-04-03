/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits.h>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
    void addEdge(Vertex<T> *d, Vertex<T> * s, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, Vertex<T> * s, double w) {
	adj.push_back(Edge<T>(d, s, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	Vertex<T> * src;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, Vertex<T>* s, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};
template <class T>
Edge<T>::Edge(Vertex<T> *d, Vertex<T>* s, double w): dest(d), weight(w) , src(s){}
template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,v1, w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for(Vertex<T>* v: this->vertexSet){
        v->visited = false;
        v->dist = INF;
        v->path = NULL;
    }
    Vertex<T>* v = this->findVertex(origin);
    v->dist = 0;
    MutablePriorityQueue<Vertex<T>> queue;
    queue.insert(v);

    while (!queue.empty()){
        Vertex<T>* v= queue.extractMin();

        for(Edge<T> edge: v->adj){
            if(edge.dest->dist > v->getDist() + edge.weight){
                edge.dest->dist = v->getDist() + edge.weight;
                edge.dest->path = v;
                if(queue.find(edge.dest)){
                	queue.decreaseKey(edge.dest);
                } else{
                	queue.insert(edge.dest);
                }
            }
        }

    }
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	Vertex<T> * v = this->findVertex(dest);
	while ((v->getInfo()) != origin){
		res.push_back(v->getInfo());
		v = v->getPath();
	}
	res.push_back(v->getInfo());
	std::reverse(res.begin(), res.end());
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for(Vertex<T>* v: this->vertexSet){
        v->visited = false;
        v->dist = INF;
        v->path = NULL;
    }
    Vertex<T>* v = this->findVertex(orig);
    v->dist = 0;
    queue<Vertex<T> *> nextVertex;
    nextVertex.push(v);

    while (!nextVertex.empty()){
        Vertex<T>* v = nextVertex.front();
        nextVertex.pop();
        for(Edge<T> edge: v->adj){
            if(edge.dest->dist == INF){
                edge.dest->dist = v->getDist() + 1;
                edge.dest->path = v;
                nextVertex.push(edge.dest);
            }
        }

    }
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    vector<Edge<T>> edgeSet;
    for(Vertex<T> * v: this->vertexSet){
        v->dist = INF;
        v->path = NULL;
        for(Edge<T> t: v->adj)
            edgeSet.push_back(t);
    }
    Vertex<T> * v = this->findVertex(orig);
    v->dist = 0;
    for(int i = 1; i < this->vertexSet.size(); i++){
        for(Edge<T> t: edgeSet){
            if(t.dest->getDist() > t.src->getDist() + t.weight){
                t.dest->dist = t.src->getDist() + t.weight;
                t.dest->path = t.src;
            }
        }
    }


}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    int dist[this->vertexSet.size()][this->vertexSet.size()];
    for (int i = 0; i < this->vertexSet.size(); i++)
        for (int j = 0; j < this->vertexSet.size(); j++)
            dist[i][j] = 0;
    for(int k = 0; k < this->vertexSet.size(); k++){
        for(int i = 0; i < this->vertexSet.size(); i++){
            for(int j = 0; j < this->vertexSet.size(); j++){
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
