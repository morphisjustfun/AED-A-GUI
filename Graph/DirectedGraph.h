#include "Graph/Algorithms/dfs.h"
#include "graph.h"
#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H #include "dfs.h" #include "graph.h"
#include <iostream>

template <typename TV, typename TE> class DirectedGraph : public Graph<TV, TE> {
public:
  DirectedGraph() = default;

  bool insertVertex(string id, TV vertex) override {
    auto *newVertex = new Vertex<TV, TE>;
    newVertex->data = vertex;
    if (this->vertexes.find(id) != this->vertexes.end()) {
      return false;
    } else {
      this->vertexes[id] = newVertex;
      this->count_vertex++;
      return true;
    }
  }
  bool createEdge(string id1, string id2, TE w) override {
    if (this->vertexes.find(id1) != this->vertexes.end() &&
        this->vertexes.find(id2) != this->vertexes.end()) {
      auto *new_edge = new Edge<TV, TE>;
      new_edge->weight = w;
      new_edge->vertexes[0] = this->vertexes[id1];
      new_edge->vertexes[1] = this->vertexes[id2];

      this->vertexes[id1]->edges.push_front(new_edge);

      this->count_edge++;
      return true;
    } else {
      return false;
    }
  }
  bool deleteVertex(string id) override {
    if (this->vertexes.find(id) == this->vertexes.end()) {
      return false;
    } else {
      for (auto &vertexes : this->vertexes) {
        for (auto &edge : vertexes.second->edges) {
          if (edge->vertexes[0] == this->vertexes[id]) {
            vertexes.second->edges.remove(edge);
            edge = nullptr;
            delete edge;
            break;
          }
          if (edge->vertexes[1] == this->vertexes[id]) {
            vertexes.second->edges.remove(edge);
            edge = nullptr;
            delete edge;
            break;
          }
        }
      }
      this->vertexes[id]->edges.clear();
      delete this->vertexes[id];
      this->vertexes.erase(id);
      this->count_vertex--;
      return true;
    }
  }
  bool deleteEdge(string start, string end) override {
    if (this->vertexes.find(start) == this->vertexes.end() &&
        this->vertexes.find(start) == this->vertexes.end()) {
      return false;
    }

    for (auto edge : this->vertexes[start]->edges) {
      if (edge->vertexes[0] == this->vertexes[start] &&
          edge->vertexes[1] == this->vertexes[end]) {
        this->vertexes[start]->edges.remove(edge);
        this->vertexes[end]->edges.remove(edge);
        break;
      }
    }
    this->count_edge--;
    return true;
  }

  TE &operator()(string start, string end) {
      if (this->vertexes.find(start) == this->vertexes.end() &&
          this->vertexes.find(start) == this->vertexes.end()) {
          throw("There is no edge with these keys");
      }
      for (auto edge : this->vertexes[start]->edges) {
          if (edge->vertexes[0] == this->vertexes[start] &&
              edge->vertexes[1] == this->vertexes[end]) {
              return edge->weight;
          }
      }
  }

  float density() override {
    return (float)(this->count_edge) /
           (this->count_vertex * (this->count_vertex - 1));
  }

  bool isDense(float threshold = 0.5) override {
    if ((float)(this->count_edge) /
            (this->count_vertex * (this->count_vertex - 1)) <
        threshold)
      return true;
    return false;
  }

  // weakly connected
  bool isConnected() {
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
      Dfs<TV, TE> test(this, it->first);
      auto vector = test.apply();
      if (vector.size() == this->count_vertex) {
        return true;
      }
    }
    return false;
  }

  // strongly connected
  bool isStronglyConnected() throw() {
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
      Dfs<TV, TE> test(this, it->first);
      auto vector = test.apply();
      if (vector.size() != this->count_vertex) {
          return false;
      }
    }
    return true;
  }

  void displayVertex(string id) override {
    cout << id << "-" << this->vertexes.at(id)->data << endl;
  }
  bool findById(string id) override { return this->vertexes.at(id); }
  void display() override {
    cout << "DISPLAY: \n";
    for (auto &it : this->vertexes) {
      cout << "Id: " << it.first << " value: " << it.second->data << endl;
      cout << "Edges :" << endl;
      for (auto const &i : it.second->edges) {
        cout << "   {" << i->vertexes[0]->data << ", " << i->vertexes[1]->data
             << "} w: " << i->weight << endl;
      }
      std::cout << std::endl;
    }
  }
};

#endif
