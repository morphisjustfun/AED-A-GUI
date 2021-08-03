#ifndef DFS
#define DFS

#include "Graph/graph.h"
#include <iostream>
#include <stack>
#include <string>

template <typename TV, typename TE> class Dfs {
public:
  Graph<TV, TE> *graph;
  string start_id;
  Dfs(Graph<TV, TE> *graph, string id) {
    this->graph = graph;
    this->start_id = id;
  }

  vector<Vertex<TV, TE> *> apply() {
    vector<Vertex<TV, TE> *> result;
    unordered_map<Vertex<TV, TE> *, bool> visited;
    auto it = this->graph->vertexes.begin();
    while (it != this->graph->vertexes.end()) {
      visited[it->second] = false;
      it++;
    }
    std::stack<Vertex<TV, TE> *> stack;

    stack.push(this->graph->vertexes[this->start_id]);

    while (!stack.empty()) {
      Vertex<TV, TE> *s = stack.top();
      stack.pop();

      if (!visited[s]) {
        result.push_back(s);
        visited[s] = true;
      }

      for (auto it = s->edges.begin(); it != s->edges.end(); ++it) {
        if (!visited[(*it)->vertexes[1]]) {
          stack.push((*it)->vertexes[1]);
        }
        if (!visited[(*it)->vertexes[0]]) {
          stack.push((*it)->vertexes[0]);
        }
      }
    }
    return result;
  }
};

#endif
