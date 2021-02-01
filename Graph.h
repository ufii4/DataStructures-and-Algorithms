//
// Created by pcxie on 2020/11/27.
//

#ifndef MST_GRAPH_H
#define MST_GRAPH_H

//The struct edge is used to represent the relationship between two nodes in the graph
struct edge {
    edge() = default;

    edge(unsigned int x, unsigned int y, double weight);

    unsigned int x, y;
    double weight;
};

class Graph {
    friend class GraphTests;
protected:
    unsigned int numberOfNodes;
    double **adjMatrix;
public:
    Graph() = default;

    Graph(unsigned int numberOfNodes);

    ~Graph();

    void init();

    void insertEdge(unsigned int v1, unsigned int v2, double weight);

    bool rmEdge(unsigned int v1, unsigned int v2);

    unsigned int getEdgeCount() const;

    unsigned int getDegreeOf(unsigned int vertex) const;

    bool tryGetMSTWeight(double &weight) const;

    unsigned int getSize() const;
};


#endif //MST_GRAPH_H
