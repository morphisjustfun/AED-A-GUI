#ifndef DSARRAY_H
#define DSARRAY_H

#include "ds.h"

template <typename T>
class DisjoinSetArray: public DisjoinSet<T>
{
private:
    vector<T> data;
    int* parent;
    int* rank;
    int n;
public:

    void MakeSet(int x) {
        rank[x] = 0;
        parent[x] = x;
    }

    DisjoinSetArray(vector<T> data) {
        this->data = data;
        n = data.size();
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            MakeSet(i);
        }
    };

    ~DisjoinSetArray() {
        data.clear();
        delete[] parent;
        delete[] rank;
    }

    int sets() {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i) {
                count++;
            }
        }
        return count;
    }
    // implement all functions
    int Find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            Find(parent[x]);
        }
    };
    //Union two sets represented by x and y (apply rank)
    void Union(int x, int y) {
        int xparent = Find(x);
        int yparent = Find(y);
        if (xparent == yparent) return;

        if (rank[xparent] > rank[yparent])
            parent[yparent] = xparent;
        else if (rank[xparent] < rank[yparent])
            parent[xparent] = yparent;
        else {
            parent[yparent] = xparent;
            rank[xparent] = rank[xparent]+1;
        }
    };

    //number of sets
    int size(int x){
        int count = 0;
        int setParent =  Find(x);
        for (int i = 0; i < n; i++) {
            if (Find(i) == setParent) {
                count++;
            }
        }
        return count;
    };
    //add the element to the set of x
    void add(T element, int x){
        data.push_back(element);
        int* temp_parents = new int[n+1];
        int* temp_rank = new int[n+1];

        temp_parents[n] = Find(x);
        temp_rank[n] = 0;

        for (int i = 0; i < n; i++) {
            temp_parents[i] = i;
            temp_rank[i] = rank[i];
        }
        delete[] parent;
        delete[] rank;
        parent = temp_parents;
        rank = temp_rank;
        n++;
    };
    //return all elements that belong to the set of x
    vector<T> getElementsSet(int x){
        vector<T> subset;
        int setParent =  Find(x);
        for (int i = 0; i < n; i++) {
            if (Find(i) == setParent) {
                subset.push_back(data[i]);
            }
        }
        return subset;
    };
};

#endif