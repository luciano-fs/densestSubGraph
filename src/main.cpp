#include <fstream>
#include <iostream>
#include "graph.h"

int main(int argc, char *argv[])
{
    std::ifstream input;
    std::ofstream output;
    input.open(argv[1], std::ifstream::in);
    output.open(argv[2], std::ofstream::out);

    Graph g(input);
    g.densest(output);

    input.close();
    output.close();
    return EXIT_SUCCESS;
}
