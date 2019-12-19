#include "graph.h"

Graph::Graph(std::ifstream& input) 
{
    int x,y;

    // Parse header of input file
    input.ignore(255, '\n');
    input.ignore(255, ' ');
    input >> m >> n;
    input.ignore(255, '\n');

    ndeg = new int[n];
    for(int i = 0; i < n; ++i)
        ndeg[i] = 0;

    adj = new std::list<int>[n];

    for (int i = 0; i < m; ++i) {
        input >> x;
        input >> y;
        ++ndeg[x-1];
        ++ndeg[y-1];
        adj[x-1].push_back(y);
        adj[y-1].push_back(x);
    }

    nMinDeg = nMaxDeg = ndeg[0];
    for (int i = 1; i < n; ++i)
        if (ndeg[i] < nMinDeg)
            nMinDeg = ndeg[i];
        else if (ndeg[i] > nMaxDeg)
            nMaxDeg = ndeg[i];

    deg = new std::list<int>[nMaxDeg + 1];
    for (int i = 0; i < n; ++i)
        deg[ndeg[i]].push_back(i+1);

}

Graph::~Graph()
{
    delete[] adj;
    delete[] deg;
    delete[] ndeg;
}

void Graph::show(std::ostream& output)
{
    for (int i = 0; i < n; ++i) {
        output << "Nodes connected to node " << i+1 << ":" << std::endl;
        for (int j : adj[i])
            output << j << ' ';
        output << std::endl;
    }

    output << std::endl;
    for (int i = 0; i <= nMaxDeg; ++i) {
        output << "Nodes of degree " << i << ":" << std::endl;
        for (int j : deg[i])
            output << j << ' ';
        output << std::endl;
    }
}

void Graph::densest(std::ostream& output)
{
    int curM = m;
    int curN = n;
    int v;
    float maxDens = (static_cast<float>(m))/n;
    bool curV[n];
    bool maxV[n];

    for (int i = 0; i < n; ++i)
        curV[i] = true;
    for (int i = 0; i < n; ++i)
        maxV[i] = true;

    while (curM) {
        v = deg[nMinDeg].front();
        deg[nMinDeg].pop_front();
        curV[v-1] = false;
        --curN;
        curM -= ndeg[v-1];

        for (int it : adj[v-1]) {
            if (curV[it-1]) {
                deg[ndeg[it-1]].remove(it);
                --ndeg[it-1];
                deg[ndeg[it-1]].push_back(it);
                if (ndeg[it-1] < nMinDeg)
                    nMinDeg = ndeg[it-1];
            }
        }

        while (deg[nMinDeg].empty())
            ++nMinDeg;

        if ((static_cast<float>(curM))/curN >= maxDens) {
            maxDens = (static_cast<float>(curM))/curN;
            for (int i = 0; i < n; ++i)
                maxV[i] = curV[i];
        }
    }

    output << "Densest Graph:" << std::endl;
    for (int i = 0; i < n; ++i)
        if (maxV[i])
            output << i+1 << ' ';
    output << std::endl;
}
