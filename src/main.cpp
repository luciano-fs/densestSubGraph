#include <fstream>
#include <iostream>
#include "graph.h"

int main(int argc, char *argv[])
{
    std::ifstream myFile;
    myFile.open(argv[1], std::ifstream::in);

    Graph g(myFile);
    g.densest(std::cout);

    myFile.close();
    return EXIT_SUCCESS;
}
