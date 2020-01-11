#include <fstream>
#include <iostream>

void streamDensest
    (float eps, std::ifstream& input, std::ofstream& output)
{
    int m, n;
    int maxM, maxN;
    int curM, curN;
    int x, y;
    float gDens;
    float maxDens = 0;
    int* deg;
    bool* maxGraph;


    input >> n >> m; 
    deg = new int[n]; //Stores node degrees and -1 when they are cut
    maxGraph = new bool[n];
    curM = maxM = m;
    curN = maxN = n;
    maxDens = static_cast<float>(maxM)/maxN;
    
    //Initially, the densest subgraph is the whole graph
    for (int i = 0; i < n; ++i) {
        deg[i] = 0;
        maxGraph[i] = true;
    }

    while (true) {
        input >> x >> y;
        if (input.eof())
            break;
        ++deg[x-1];
        ++deg[y-1];
    }

    while (curM != 0) {
        //Updates densest subgraph
        gDens = static_cast<float>(curM)/curN;
        if (gDens > maxDens) {
            maxDens = gDens;
            maxM = curM;
            maxN = curN;
            for (int i = 0; i < n; ++i)
                if (deg[i] == -1)
                    maxGraph[i] = false;
        }

        //Cuts nodes whose degrees are lower than the threshold
        for (int i = 0; i < n; ++i)
            if (deg[i] != -1 && deg[i] <= 2*(1+eps)*gDens) {
                deg[i] = -1;
                --curN;
            }
            //Prepares to count the degree of the remaining nodes
            else if (deg[i] != -1)
                deg[i] = 0;

        curM = 0;
        input.clear();
        input.seekg(0, input.beg); //Rewinds file
        input.ignore(255, '\n'); //Ignores original graph size

        while (true) {
            //Counts the degree of the remaining nodes
            input >> x >> y;
            if (input.eof())
                break;
            if (deg[x-1] != -1 && deg[y-1] != -1) {
                ++curM;
                ++deg[x-1];
                ++deg[y-1];
            }
        }

    }

    //Stores the answer in a file
    output << maxN << ' ' << maxM << std::endl;
    input.clear();
    input.seekg(0, input.beg);
    input.ignore(255, '\n');
    while (!input.eof()) {
        input >> x >> y;
        if (maxGraph[x-1] && maxGraph[y-1])
            output << x << ' ' << y << std::endl;
    }

    delete[] deg;
    delete[] maxGraph;
}
