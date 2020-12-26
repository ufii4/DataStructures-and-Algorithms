//
// Created by pcxie on 2020/12/26.
//

#include "DisjointSet.h"
#include <stdexcept>

DisjointSet::DisjointSet(unsigned int n) : n(n) {
    nodes = new unsigned int[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = i;
    }
}


DisjointSet::~DisjointSet() {
    delete[] nodes;
}

void DisjointSet::merge(unsigned int i1, unsigned int i2) {
    nodes[find(i1)] = find(i2);
}

// x<n
unsigned int DisjointSet::find(unsigned int x) {
    if (x >= n) {
        throw std::out_of_range("Invalid argument.");
    }
    if (x != nodes[x]) {
        nodes[x] = find(nodes[x]);
    }
    return nodes[x];
}
