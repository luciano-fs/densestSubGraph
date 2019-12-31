#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "graph.h"

void streamDensest(int, std::ifstream&, std::ofstream&);

int main(int argc, char *argv[])
{
    std::ifstream input;
    std::ofstream output;

    if (!strcmp(argv[1], "-s")) {
        int epsilon = atoi (argv[2]);
        input.open(argv[2], std::ifstream::in);
        output.open(argv[3], std::ofstream::out);
        streamDensest(epsilon, input, output);
    }
    else {
        input.open(argv[1], std::ifstream::in);
        output.open(argv[2], std::ofstream::out);
        Graph g(input);
        g.densest(output);
    }

    input.close();
    output.close();
    return EXIT_SUCCESS;
}
