#include <fstream>
#include <iostream>

void streamDensest
    (int eps, std::ifstream& input, std::ofstream& output)
{
    int m, n;
    int maxM, maxN;
    int x, y;
    float gDeg;
    float maxDens = 0;
    int* deg;
    bool* maxGraph;
    bool ready = false;

    input >> n >> m; 
    deg = new int[n]; //Stores node degrees and -1 when they are cut
    maxGraph = new bool[n];
    
    for (int i = 0; i < n; ++i) {
        deg[i] = 0;
        maxGraph[i] = true;
    }

    std::cout << "OK " << n << ' ' << m << std::endl << std::flush;

    while (!input.eof()) {
        input >> x >> y;
        ++deg[x-1];
        ++deg[y-1];
    }

    while (!ready) {
        ready = true;
        gDeg = static_cast<float>(m)/n;
        if (gDeg > maxDens) {
            maxDens = gDeg;
            maxM = m;
            maxN = n;
            for (int i = 0; i < n; ++i)
                if (deg[i] == -1)
                    maxGraph[i] = false;
        }
        for (int i = 0; i < n; ++i)
            if (deg[i] != -1 && deg[i] <= gDeg) {
                deg[i] = -1;
                --n;
            }
            else
                deg[i] = 0;
        m = 0;
        input.seekg(0, input.beg);
        input.ignore(255, '\n'); //Ignores original graph size
        while (!input.eof()) {
            input >> x >> y;
            if (deg[x-1] != -1 && deg[y-1] != -1) {
                ready = false;
                ++m;
                ++deg[x-1];
                ++deg[y-1];
            }
        }
    }

    output << maxN << maxM << std::endl;
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
