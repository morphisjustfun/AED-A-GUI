#ifndef PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_FLOYDWARSHALL_H
#define PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_FLOYDWARSHALL_H

#include <climits>
#include "Graph/DirectedGraph.h"
#include <iomanip>

template <typename TV, typename TE>
class FloydWarshall {
private:
    vector<vector<int>> sDist;
    vector<vector<string>> sRec;
    std::unordered_map<int, Vertex<TV, TE>*> sVer;
    std::unordered_map<Vertex<TV, TE>*, string> sIds;
public:
    DirectedGraph <TV, TE> *graph;

    FloydWarshall(DirectedGraph <TV, TE> *graph) {
        this->graph = graph;
    }

    pair<vector<vector<int>>, vector<vector<string>>> apply() {
        int nv = graph->count_vertex;
        vector<vector<int>> dist(nv);
        vector<vector<string>> rec(nv);
        for (int i = 0; i < nv; i++) {
            dist[i].resize(nv);
            for (int j = 0; j < nv; j++) {
                if (i != j)
                    dist[i][j] = INT_MAX;
                else
                    dist[i][j] = 0;
            }
        }

        std::unordered_map<int, Vertex<TV, TE>*> v;
        std::unordered_map<Vertex<TV, TE>*, int> idx;
        std::unordered_map<Vertex<TV, TE>*, string> ids;

        int i = 0;

        for (auto& vertex: graph->vertexes) {
            idx[vertex.second] = i;
            ids[vertex.second] = vertex.first;
            v[i] = vertex.second;
            i++;
        }

        for (int i = 0; i < nv; i++) {
            rec[i].resize(nv);
            for (int j = 0; j < nv; j++) {
                if (i != j)
                    rec[i][j] = ids[v[j]];
                else
                    rec[i][j] = "-";
            }
        }


        for (auto &vertex : graph->vertexes) {
            for (auto &edge: vertex.second->edges) {
                dist[idx[edge->vertexes[0]]][idx[edge->vertexes[1]]] = edge->weight;
            }
        }

        for (int k = 0; k < nv; k++) {
            for (int i = 0; i < nv; i++) {
                for (int j = 0; j < nv; j++) {
                    if((dist[k][j] != INT_MAX && dist[i][k] != INT_MAX) && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        rec[i][j] = ids[v[k]];
                    }
                }
            }
        }


        //sort(dist.begin(), dist.end());
        sRec = rec;
        sDist = dist;
        sIds = ids;
        sVer = v;
        pair<vector<vector<int>>, vector<vector<string>>> result {dist, rec};
        return result;
    }

    void display() {
        cout << "Distancias:\n";
        int i = 0;
        cout << setw(10);
        for (int i = 0; i < sIds.size(); i++) {
            cout << sIds[sVer[i]] << setw(4);
        }
        cout << endl << setw(10);

        for (int i = 0; i < sIds.size(); i++) {
            cout << "____" << setw(3);
        }
        cout << endl << setw(3);


        for (auto &row : sDist) {
            cout << setw(3) << sIds[sVer[i]] << "  | ";
            for (int &n: row) {
                if (n == INT_MAX) {
                    cout << setw(3) << "inf" << " ";
                } else {
                    cout << setw(3) << n << " ";
                }
            }
            cout << endl;
            i++;
        }


        cout << "Recorridos:\n";
        i = 0;
        cout << setw(10);
        for (int i = 0; i < sIds.size(); i++) {
            cout << sIds[sVer[i]] << setw(4);
        }
        cout << endl << setw(10);

        for (int i = 0; i < sIds.size(); i++) {
            cout << "____" << setw(3);
        }
        cout << endl << setw(3);


        for (auto &row : sRec) {
            cout << setw(3) << sIds[sVer[i]] << "  | ";
            for (auto &n: row) {
                  cout << setw(3) << n << " ";
            }
            cout << endl;
            i++;
        }
    }
};
/* TEST
  DirectedGraph<char, int> dg;
  dg.insertVertex("1", '1');
  dg.insertVertex("2", '2');
  dg.insertVertex("3", '3');
  dg.insertVertex("4", '4');
  dg.insertVertex("5", '5');

  dg.createEdge("1", "3", 6);
  dg.createEdge("1", "4", 3);
  dg.createEdge("2", "1", 3);
  dg.createEdge("3", "4", 2);
  dg.createEdge("4", "3", 1);
  dg.createEdge("4", "2", 1);
  dg.createEdge("5", "2", 4);
  dg.createEdge("5", "4", 2);

  FloydWarshall<char, int> floydWarhsall = FloydWarshall(&dg);

  pair<vector<vector<int>>, vector<vector<string>>> result = floydWarhsall.apply();
  floydWarhsall.display();

 */
#endif //PROYECTO_DE_CURSO_TEAM_TRIPLE_FOR_FLOYDWARSHALL_H
