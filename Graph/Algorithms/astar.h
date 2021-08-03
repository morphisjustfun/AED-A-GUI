#pragma once

#include "Graph/graph.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#define MAX 999999999

using namespace std;

template <typename TV, typename TE> struct entryList {
  Vertex<TV, TE> *vertex;
  Vertex<TV, TE> *parent;
  // normal cost
  TE g;
  // heuristic
  TE h;
  entryList(Vertex<TV, TE> *vertex_) {
    this->g = 0;
    this->h = 0;
    this->vertex = vertex_;
    this->parent = nullptr;
  }
  TE getF() { return g + h; }
};

template <typename TV, typename TE> class AStar {
  Graph<TV, TE> *graph;
  unordered_map<TV, TE> heuristic;
  vector<entryList<TV, TE> *> openList;
  vector<entryList<TV, TE> *> closedList;

  bool entryExistsInVector(entryList<TV, TE> *target,
                           vector<entryList<TV, TE> *> object) {
    for (entryList<TV, TE> *each : object) {
      if (target->vertex == each->vertex) {
        return true;
      }
    }
    return false;
  }

  static bool cmpEntryList(const entryList<TV, TE> *lhs,
                           const entryList<TV, TE> *rhs) {
    return (lhs->g + lhs->h) < (rhs->g + rhs->h);
  }

  entryList<TV, TE> *findEntryFromVertex(Vertex<TV, TE> *vertex,
                                         vector<entryList<TV, TE> *> target) {
    for (entryList<TV, TE> *each : target) {
      if (each->vertex == vertex) {
        return each;
      }
    }
    return nullptr;
  }

public:
  AStar(Graph<TV, TE> *g, unordered_map<TV, TE> h) : graph(g), heuristic(h) {}

  vector<TV> apply(string start, string end) {
    if (graph->vertexes.find(start) == graph->vertexes.end() ||
        graph->vertexes.find(end) == graph->vertexes.end()) {
      return {};
    }
    vector<TV> dataResult;

    Vertex<TV, TE> *startV = graph->vertexes[start];
    Vertex<TV, TE> *endV = graph->vertexes[end];

    entryList<TV, TE> *entry = new entryList<TV, TE>(startV);
    entry->h = heuristic[startV->data];
    openList.push_back(entry);

    while (!openList.empty()) {
      auto it = min_element(openList.begin(), openList.end(), cmpEntryList);
      entryList<TV, TE> *currentEntry = *it;
      if (currentEntry->vertex == endV) {
        entryList<TV, TE> *tempEntry = currentEntry;

        vector<TV> result;
        while (tempEntry != nullptr) {
          result.push_back(tempEntry->vertex->data);
          tempEntry = findEntryFromVertex(tempEntry->parent, closedList);
        }
        reverse(result.begin(), result.end());
        return result;
      }
      openList.erase(it);
      closedList.push_back(currentEntry);

      for (Edge<TV, TE> *edge : currentEntry->vertex->edges) {
        Vertex<TV, TE> *neigh =
            graph->findDifferent(edge, currentEntry->vertex);
        entryList<TV, TE> *succesorEntry = new entryList<TV, TE>(neigh);
        if (entryExistsInVector(succesorEntry, closedList)) {
          continue;
        }
        float successor_current_cost =
            currentEntry->g +
            abs(graph->findEdge(currentEntry->vertex, succesorEntry->vertex)
                    ->weight);

        bool exO = entryExistsInVector(succesorEntry, openList);
        bool exC = entryExistsInVector(succesorEntry, closedList);

        if (exO && successor_current_cost < succesorEntry->g) {
          openList.erase(find(openList.begin(), openList.end(), succesorEntry));
        }
        if (exC && successor_current_cost < succesorEntry->g) {
          closedList.erase(
              find(openList.begin(), openList.end(), succesorEntry));
        }
        if (!exO && !exC) {
          openList.push_back(succesorEntry);
          succesorEntry->g = successor_current_cost;
          succesorEntry->parent = currentEntry->vertex;
          succesorEntry->h = heuristic[succesorEntry->vertex->data];
        }
      }
    }
    return {};
  };
};
