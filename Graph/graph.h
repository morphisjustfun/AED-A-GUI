#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename TV, typename TE> struct Edge;

template <typename TV, typename TE> struct Vertex;

template <typename TV, typename TE> class Graph;

//////////////////////////////////////////////////////

template <typename TV, typename TE> struct Edge {
  Vertex<TV, TE> *vertexes[2];
  TE weight;
};

template <typename TV, typename TE> struct Vertex {
  TV data;
  std::list<Edge<TV, TE> *> edges;
  // inline bool operator==(const Vertex& rhs) {
  //     return this->data == rhs.data;
  // }
  // inline bool operator<(const Vertex& rhs){
  //     return this->data < rhs.data;
  // }
};

template <typename TV, typename TE> class Graph {
public:
  int count_edge = 0;
  int count_vertex = 0;
  std::unordered_map<string, Vertex<TV, TE> *> vertexes;
  virtual bool insertVertex(string id, TV vertex) = 0;
  virtual bool createEdge(string id1, string id2, TE w) = 0;
  virtual bool deleteVertex(string id) = 0;
  virtual bool deleteEdge(string start, string end) = 0;
  virtual TE &operator()(string start, string end) = 0;
  virtual float density() = 0;
  virtual bool isDense(float threshold = 0.5) = 0;
  virtual bool isConnected() = 0;
  virtual bool isStronglyConnected() throw() = 0;
  bool empty() { return vertexes.empty(); }
  void clear() { vertexes.clear(); }

  virtual void displayVertex(string id) = 0;
  virtual bool findById(string id) = 0;
  virtual void display() = 0;

  Vertex<TV, TE> *findVertex(string id) { return this->vertexes[id]; }
  Edge<TV, TE> *findEdge(string start, string end) {
    for (auto it = this->vertexes[start]->edges.begin();
         it != this->vertexes[start]->edges.end(); ++it) {
      if ((*it)->vertexes[1] == this->vertexes[end]) {
        return *it;
      }
    }
  };
  Vertex<TV,TE>* findDifferent(Edge<TV,TE>* edge, Vertex<TV,TE>* current){
      if (edge->vertexes[0]->data == current->data) return edge->vertexes[1];
      return edge->vertexes[0];
  }
  Edge<TV, TE> *findEdge(Vertex<TV, TE> *start, Vertex<TV, TE> *end) {
    for (auto it = start->edges.begin(); it != start->edges.end(); ++it) {
      if ((*it)->vertexes[1] == end) {
        return *it;
      }
    }
  };
};

#endif
