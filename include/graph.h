#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <list>

class Graph
{
private:
    std::list<int>* adj; //Graph's adjancency matrix
    std::list<int>* deg; //Lists of nodes indexed by their degrees
    int m; //Graph number of edges
    int n; //Graph number of vertices
    int nMinDeg; //Min degree of a node in given graph
    int nMaxDeg; //Min degree of a node in given graph

public:
    Graph(std::ifstream&);
    virtual ~Graph();

    void show(std::ostream&);
};

#endif /* GRAPH_H */