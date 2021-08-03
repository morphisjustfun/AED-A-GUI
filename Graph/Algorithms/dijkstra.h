#ifndef DIJKSTRA
#define DIJKSTRA

#include <climits>
#include "Graph/graph.h"

template <typename TV, typename TE>
class Dijkstra {
public:
    Graph <TV, TE> *graph;
    string start_id;

    Dijkstra(Graph <TV, TE> *graph, string id) {
        this->graph = graph;
        this->start_id = id;
    }
    bool any_false(std::unordered_map<Vertex<TV, TE>*, bool> array) {
        for (auto &vertex : array) {
            if (vertex.second == false) {
                return true;
            }
        }
        return false;
    }
    vector<tuple<string, int, string>> apply() {

        if (!this->graph->isConnected()) {
            throw("BFS can not be applied");
        }

        vector<tuple<string, int, string>> result;

        std::unordered_map<Vertex<TV, TE>*, string> ids;
        std::unordered_map<Vertex<TV, TE>*, int> dist;
        std::unordered_map<Vertex<TV, TE>*, bool> visited;
        std::unordered_map<Vertex<TV, TE>*, Vertex<TV, TE>*> parent;

        for (auto &vertex : graph->vertexes) {
            dist[vertex.second] = INT_MAX;
            visited[vertex.second] = false;
            ids[vertex.second] = vertex.first;
        }

        dist[graph->vertexes[start_id]] = 0;

        while(any_false(visited)){
            Vertex<TV, TE>* min_vertex;
            int min = INT_MAX;
            for (auto &k : dist) {
                if (k.second < min && !visited[k.first]) {
                    min = k.second;
                    min_vertex = k.first;
                }
            }
            visited[min_vertex] = true;
            for (auto& edge: min_vertex->edges){
                Vertex<TV, TE>* other_vertex = edge->vertexes[0] != min_vertex ? edge->vertexes[0] : edge->vertexes[1];
                if (dist[min_vertex] + edge->weight < dist[other_vertex]){
                    dist[other_vertex] = dist[min_vertex] + edge->weight;
                    parent[other_vertex] = min_vertex;
                }
            }
        }

        for (auto &vertex : graph->vertexes) {
            tuple<string, int, string> row = make_tuple(vertex.first, dist[vertex.second], ids[parent[vertex.second]]);

            result.push_back(row);
        }
        return result;
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
    g.createEdge("e", "f", 4);
    g.createEdge("a","e",29);

    Dijkstra<char, int> dijkstra(&g, "a");

    vector<tuple<string, int, string>> result = dijkstra.apply();
    cout << setw(5)<< "ver" << setw(5) << "dist" << setw(5) << "par" << endl;
    for (auto& row: result) {
        cout << setw(5) << get<0>(row) << setw(5) << get<1>(row) << setw(5) << get<2>(row) << endl;
    }

    DirectedGraph<char, int> dg;
    dg.insertVertex("a", 'A');
    dg.insertVertex("b", 'B');
    dg.insertVertex("c", 'C');
    dg.insertVertex("d", 'D');
    dg.insertVertex("e", 'E');
    dg.insertVertex("f", 'F');

    dg.createEdge("a", "b", 2);
    dg.createEdge("c", "d", 1);
    dg.createEdge("c", "b", 2);
    dg.createEdge("a", "d", 5);
    dg.createEdge("a", "c", 10);
    dg.createEdge("e", "f", 4);
    dg.createEdge("a","e",29);

    Dijkstra<char, int> dijkstra_dg(&dg, "a");

    vector<tuple<string, int, string>> result_dg = dijkstra_dg.apply();
    cout << setw(5)<< "ver" << setw(5) << "dist" << setw(5) << "par" << endl;
    for (auto& row: result_dg) {
        cout << setw(5)<< get<0>(row) << setw(5) << get<1>(row) << setw(5) << get<2>(row) << endl;
    }
 */

#endif
