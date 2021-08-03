#pragma once
#include "Graph/graph.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename TV, typename TE> struct entryBfs {
  TE cost;
  Vertex<TV, TE> *vertex;
  Vertex<TV, TE> *parent;
  entryBfs(Vertex<TV, TE> *vertex_)
      : vertex(vertex_), cost(0), parent(nullptr) {}
};

template <typename TV, typename TE> class CompareVertex {
public:
  bool operator()(entryBfs<TV, TE> *first, entryBfs<TV, TE> *second) {
    return first->cost > second->cost;
  }
};

template <typename TV, typename TE> class GreedyBfs {
  map<Vertex<TV, TE> *, bool> visited;
  priority_queue<entryBfs<TV, TE> *, vector<entryBfs<TV, TE> *>,
                 CompareVertex<TV, TE>>
      distancesQueue;
  Graph<TV, TE> *graph;

  entryBfs<TV, TE> *findEntryFromVertex(Vertex<TV, TE> *vertex,
                                        vector<entryBfs<TV, TE> *> target) {
    for (entryBfs<TV, TE> *each : target) {
      if (each->vertex == vertex) {
        return each;
      }
    }
    return nullptr;
  }

public:
  GreedyBfs(Graph<TV, TE> *graph) : graph(graph) {}

  vector<TV> apply(string start, string end) {
    if (graph->vertexes.find(start) == graph->vertexes.end() ||
        graph->vertexes.find(end) == graph->vertexes.end()) {
      return {};
    }
    vector<entryBfs<TV, TE>*> dataResult;

    Vertex<TV, TE> *startV = graph->vertexes[start];
    Vertex<TV, TE> *endV = graph->vertexes[end];

    distancesQueue.push(new entryBfs<TV, TE>(startV));
    visited[startV] = true;
    string s = start;

    while (!distancesQueue.empty()) {
      entryBfs<TV, TE> *top = distancesQueue.top();
      dataResult.push_back(top);
      distancesQueue.pop();
      if (top->vertex == endV) {
        entryBfs<TV, TE> *tempEntry = top;
        vector<TV> result;
        while (tempEntry != nullptr) {
          result.push_back(tempEntry->vertex->data);
          tempEntry = findEntryFromVertex(tempEntry->parent, dataResult);
        }
        reverse(result.begin(),result.end());
        return result;
      }
      for (Edge<TV, TE> *edge : top->vertex->edges) {
        Vertex<TV, TE> *edgeW = graph->findDifferent(edge, top->vertex);
        auto it = visited.find(edgeW);
        if (it == visited.end()) {
          visited[edgeW] = true;
          entryBfs<TV, TE> *target = new entryBfs<TV, TE>(edgeW);
          target->cost = edge->weight;
          target->parent = top->vertex;
          distancesQueue.push(target);
        }
      }
    }
    return {};
  }
};
