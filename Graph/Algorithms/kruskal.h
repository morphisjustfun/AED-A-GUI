#include "Dset/dsarray.h"
#include "Graph/UndirectedGraph.h"
#include "algorithm"

template <typename TV, typename TE> struct wComparator {
  bool operator()(Edge<TV, TE> *a, Edge<TV, TE> *b) const {
    return a->weight < a->weight;
  }
};

/* TEST
    UnDirectedGraph<char, int> g;

   g.insertVertex("a", 'A');
   g.insertVertex("b", 'B');
   g.insertVertex("c", 'C');
   g.insertVertex("d", 'D');

   g.insertVertex("e", 'E');
   g.insertVertex("f", 'F');

    g.createEdge("a", "b", 2);
    g.createEdge("c", "d", 1);
    g.createEdge("c", "b", 2);
    g.createEdge("a", "d", 5);
    g.createEdge("a", "c", 10);
    //unconnected
    g.createEdge("e", "f", 4);

    Kruskal<char, int> kruskal(&g);

    UnDirectedGraph<char, int> result = kruskal.apply();
    result.display();
*/
template <typename TV, typename TE> class Kruskal {
public:
  UnDirectedGraph<TV, TE> graph;
  Kruskal(UnDirectedGraph<TV, TE> *graph) { this->graph = *graph; }
  UnDirectedGraph<TV, TE> apply() {
    if (!this->graph.isConnected()) {
      throw("Kruskal can not be applied");
    }
    auto *result = new UnDirectedGraph<TV, TE>();
    string id = "a";
    std::unordered_map<Vertex<TV, TE> *, string> ids;

    vector<Edge<TV, TE> *> edges;
    vector<Vertex<TV, TE> *> vecVertexes;
    for (auto &vertex : graph.vertexes) {
      vecVertexes.push_back(vertex.second);
      ids[vertex.second] = id;
      id[id.size()-1]++;
      if (id[id.size()-1] >= 254) {
          id += "a";
      }
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

    sort(edges.begin(), edges.end(), [](Edge<TV, TE> *a, Edge<TV, TE> *b) {
      return a->weight < b->weight;
    });

    auto *ds = new DisjoinSetArray<Vertex<TV, TE> *>(vecVertexes);

    std::unordered_map<Vertex<TV, TE> *, int> dsIdx;
    int idx = 0;
    for (auto &vertex : vecVertexes) {
      dsIdx[vertex] = idx;
      idx++;
    }

    for (auto &edge : edges) {
      if (ds->Find(dsIdx[edge->vertexes[0]]) !=
          ds->Find(dsIdx[edge->vertexes[1]])) {
        result->insertVertex(ids[edge->vertexes[0]], edge->vertexes[0]->data);
        result->insertVertex(ids[edge->vertexes[1]], edge->vertexes[1]->data);
        result->createEdge(ids[edge->vertexes[0]], ids[edge->vertexes[1]],
                           edge->weight);

        ds->Union(ds->Find(dsIdx[edge->vertexes[0]]),
                  ds->Find(dsIdx[edge->vertexes[1]]));
      }
    }
    ds->Union(dsIdx[vecVertexes[1]], dsIdx[vecVertexes[1]]);

    cout << ds->sets() << endl;

    return *result;
  }
};
