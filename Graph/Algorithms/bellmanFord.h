#ifndef PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_BELLMANFORD_H
#define PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_BELLMANFORD_H

#include <climits>
#include "Graph/DirectedGraph.h"

template <typename TV, typename TE>
class bellmanFord {
public:
    DirectedGraph <TV, TE> *graph;
    string id;

    bellmanFord(DirectedGraph <TV, TE> *graph, string id) {
        this->graph = graph;
        this->id = id;
    }

    pair<unordered_map<string, int>, unordered_map<string, string>> apply() {
        unordered_map<string, int> dist;
        unordered_map<Vertex<TV, TE>*, string> ids;
        unordered_map<string, string> parent;

        for (auto &vertex : graph->vertexes) {
            dist[vertex.first] = INT_MAX;
            ids[vertex.second] = vertex.first;
            //parent[vertex.first] = nullptr;
        }

        dist[id] = 0;
        //dist[graph->vertexes[id]] = 0;

        /* storing the edges */
        vector<Edge<TV, TE> *> edges;
        for (auto &vertex : graph->vertexes) {
            if (vertex.second != nullptr) {
                for (auto &edge : vertex.second->edges) {
                    bool found = false;
                    for (int i = 0; i < edges.size(); ++i) {
                        if (edges[i] == edge) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        edges.push_back(edge);
                    }
                }
            }
        }



        for (int i = 0; i < graph->count_vertex - 1; i++) {
            for (auto edge: edges) {
                /* update */
                if (dist[ids[edge->vertexes[0]]] != INT_MAX) {
                    int newDist = dist[ids[edge->vertexes[0]]] + edge->weight;
                    if (dist[ids[edge->vertexes[1]]] > newDist) {
                        dist[ids[edge->vertexes[1]]] = newDist;
                        parent[ids[edge->vertexes[1]]] = ids[edge->vertexes[0]];
                    }
                }

            }
        }

        return make_pair(dist, parent);
    }
};
#endif //PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_BELLMANFORD_H

/*
 DirectedGraph<char, int> dg;

    dg.insertVertex("S", 'S');
    dg.insertVertex("A", 'A');
    dg.insertVertex("B", 'B');
    dg.insertVertex("C", 'C');
    dg.insertVertex("D", 'D');
    dg.insertVertex("E", 'E');

  dg.createEdge("S", "E", 8);
  dg.createEdge("S", "A", 10);
  dg.createEdge("B", "A", 1);
  dg.createEdge("A", "C", 2);
  dg.createEdge("C", "B", -2);
  dg.createEdge("D", "C", -1);
  dg.createEdge("D", "A", -4);
  dg.createEdge("E", "D", 1);

  bellmanFord<char, int> bellmanford = bellmanFord(&dg, "S");

  pair<unordered_map<string, int>, unordered_map<string, string>> result = bellmanford.apply();
  cout << "Distancias: \n";
  for (auto& key: result.first) {
      cout << key.first << ": " << key.second << std::endl;
  }
    cout << "Padres: \n";
    for (auto& key: result.second) {
      cout << key.first << ": " << key.second << std::endl;
  }
 * */
