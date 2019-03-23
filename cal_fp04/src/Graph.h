/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <iterator>
#include <deque>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if(this->findVertex(in) == NULL){
		Vertex<T> *v = new Vertex<T>(in);
		this->vertexSet.push_back(v);
		return true;
	}
	return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	Vertex<T> * source = this->findVertex(sourc);
	Vertex<T> * destination = this->findVertex(dest);

	if(source != NULL && destination != NULL){
		source->addEdge(destination, w);
		return true;
	}
	return false;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	this->adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	Vertex<T> * source = this->findVertex(sourc);
	Vertex<T> * destination = this->findVertex(dest);
	if(source != NULL && destination != NULL){
		return source->removeEdgeTo(destination);
	}
	return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T>>::iterator it = this->adj.begin();
	for(it; it != this->adj.end(); it++){
		if(it->dest == d)
		{
			this->adj.erase(it);
			return true;
		}
	}
	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T> *>::iterator it = this->vertexSet.begin();
	Vertex<T> * vertex = this->findVertex(in);
	if(vertex != NULL){
		for(it; it != this->vertexSet.end(); it++){
			this->removeEdge((*it)->info, vertex->info);
		}
		this->vertexSet.erase(std::remove(this->vertexSet.begin(), this->vertexSet.end(), vertex), this->vertexSet.end());
		return true;
	}
	return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T> *>::const_iterator it;
	vector<T> res;
	for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
		(*it)->visited = false;
	}


	for(it  = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
		if(!(*it)->visited){
            dfsVisit(*it, res);
        }
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
    res.push_back(v->info);
    typename vector<Edge<T>>::iterator it = v->adj.begin();
	for(it; it != v->adj.end(); it++){
	    if(!it->dest->visited){
	        dfsVisit(it->dest, res);
	    }
		
	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
    typename vector<Vertex<T> *>::const_iterator it;
    queue<Vertex<T> *> nextVertex;
    vector<T> res;
    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        (*it)->visited = false;
    }

    nextVertex.push(*this->vertexSet.begin());
    while(!nextVertex.empty()){
        Vertex<T> * vertex = nextVertex.front();
        vertex->visited = true;
        nextVertex.pop();
        res.push_back(vertex->info);
        typename vector<Edge<T>>::iterator it = vertex->adj.begin();
        for (it; it != vertex->adj.end(); it++){
            if(!it->dest->visited){
                nextVertex.push(it->dest);
            }
        }

    }
    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    if(this->isDAG())
        return res;
    typename vector<Vertex<T> *>::const_iterator it;
    queue<Vertex<T> *> nextVertex;
    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        (*it)->visited = false;
        (*it)->indegree = 0;
    }

    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        typename vector<Edge<T>>::const_iterator adj;
        for(adj = (*it)->adj.begin(); adj != (*it)->adj.end(); adj++){
            adj->dest->indegree++;
        }
    }

    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++) {
        if((*it)->indegree == 0)
            nextVertex.push(*it);
    }
    while(!nextVertex.empty()){
        Vertex<T> * vertex = nextVertex.front();
        vertex->visited = true;
        nextVertex.pop();
        res.push_back(vertex->info);
        typename vector<Edge<T>>::iterator it = vertex->adj.begin();
        for (it; it != vertex->adj.end(); it++){
            if(--it->dest->indegree == 0)
                nextVertex.push(it->dest);
        }

    }
    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    int max_childs = 0;
    typename vector<Vertex<T> *>::const_iterator it;
    queue<Vertex<T> *> nextVertex;
    vector<T> res;
    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        (*it)->visited = false;
    }

    nextVertex.push(*this->vertexSet.begin());
    while(!nextVertex.empty()){
        Vertex<T> * vertex = nextVertex.front();
        vertex->visited = true;
        nextVertex.pop();
        res.push_back(vertex->info);
        int new_childs = 0;
        typename vector<Edge<T>>::iterator it = vertex->adj.begin();
        for (it; it != vertex->adj.end(); it++){
            if(!it->dest->visited){
                nextVertex.push(it->dest);
                new_childs++;
            }
        }
        if(new_childs > max_childs){
            max_childs = new_childs;
            inf = vertex->info;
        }

    }
	return max_childs;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    typename vector<Vertex<T> *>::const_iterator it;
    deque<Vertex<T> *> nextVertex;
    for(it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){
        (*it)->visited = false;
    }

    nextVertex.push_front(*this->vertexSet.begin());
    while(!nextVertex.empty()){
        Vertex<T> * vertex = nextVertex.front();
        vertex->visited = true;
        nextVertex.pop_front();
        typename vector<Edge<T>>::iterator it = vertex->adj.begin();
        for (it; it != vertex->adj.end(); it++){
            if(!it->dest->visited){
                nextVertex.push_front(it->dest);
            } else if (isVertexInStack(it->dest, nextVertex)){
                return false;
            }
        }

    }
	return true;
}

template <class T>
bool isVertexInStack(Vertex<T> *v, deque<Vertex<T>* > st){
    return find(st.begin(), st.end(), v) == st.end();
}

#endif /* GRAPH_H_ */
