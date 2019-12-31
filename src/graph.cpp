#include "graph.h"

Graph::Graph(std::ifstream& input) 
{
    int x,y;

    /* Parse two line header of input file
    input.ignore(255, '\n');
    input.ignore(255, ' ');
    input >> m >> n;
    input.ignore(255, '\n');
    */

    input >> n >> m;

    ndeg = new int[n];
    for(int i = 0; i < n; ++i)
        ndeg[i] = 0;

    adj = new std::list<int>[n];
    ideg = new std::list<int>::iterator[n];

    for (int i = 0; i < m; ++i) {
        input >> x >> y;
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
    for (int i = 0; i < n; ++i) {
        deg[ndeg[i]].push_front(i+1);
        ideg[i] = deg[ndeg[i]].begin();
    }

}

Graph::~Graph()
{
    delete[] adj;
    delete[] deg;
    delete[] ndeg;
    delete[] ideg;
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
    int maxM = m;
    int curN = n;
    int maxN = n;
    int v;
    float maxDens = (static_cast<float>(m))/n;
    bool curV[n];
    bool maxV[n];
    std::list<int> modif;

    for (int i = 0; i < n; ++i)
        curV[i] = maxV[i] = true;

    while (curM) {
        v = deg[nMinDeg].front();
        deg[nMinDeg].pop_front();
        modif.push_back(v);
        curV[v-1] = false;
        --curN;
        curM -= ndeg[v-1];

        for (int it : adj[v-1]) {
            if (curV[it-1]) {
                deg[ndeg[it-1]].erase(ideg[it-1]);
                --ndeg[it-1];
                deg[ndeg[it-1]].push_front(it);
                ideg[it-1] = deg[ndeg[it-1]].begin();
                if (ndeg[it-1] < nMinDeg)
                    nMinDeg = ndeg[it-1];
            }
        }

        while (deg[nMinDeg].empty())
            ++nMinDeg;

        if ((static_cast<float>(curM))/curN >= maxDens) {
            maxDens = (static_cast<float>(curM))/curN;
            maxM = curM;
            maxN = curN;
            for (int i : modif)
                maxV[i-1] = false;
            modif.clear();
        }
    }

    output << maxN << ' ' << maxM << std::endl;
    for (int i = 0; i < n; ++i)
        if (maxV[i])
            for (int it : adj[i])
                if (maxV[it-1] && (i + 1) < it)
                   output << i + 1 << ' ' << it << std::endl; 
}
