#ifndef BFS
#define BFS

#include "Graph/graph.h"
#include <iostream>

template <typename TV, typename TE> class Bfs {
public:
  Graph<TV, TE> *graph;
  string start_id;
  Bfs(Graph<TV, TE> *graph, string id) {
    this->graph = graph;
    this->start_id = id;
  }

  vector<Vertex<TV, TE> *> apply() {
    if (!this->graph->isConnected()) {
      throw("BFS can not be applied");
    }
    vector<Vertex<TV, TE> *> result;

    unordered_map<Vertex<TV, TE> *, bool> visited;
    auto it = this->graph->vertexes.begin();
    while (it != this->graph->vertexes.end()) {
      visited[it->second] = false;
      it++;
    }

    std::list<Vertex<TV, TE> *> queue;
    visited[this->graph->vertexes[this->start_id]] = true;

    queue.push_back(this->graph->vertexes[this->start_id]);

    while (!queue.empty()) {
      Vertex<TV, TE> *s = queue.front();
      result.push_back(s);
      //cout << s->data << endl;
      queue.pop_front();

      for (auto it = s->edges.begin(); it != s->edges.end(); ++it) {
        if (!visited[(*it)->vertexes[0]]) {
          visited[(*it)->vertexes[0]] = true;
          queue.push_back((*it)->vertexes[0]);
        }
        if (!visited[(*it)->vertexes[1]]) {
          visited[(*it)->vertexes[1]] = true;
          queue.push_back((*it)->vertexes[1]);
        }
      }
    }
    return result;
  }
};

#endif
