#include <iostream>
#include <fstream>
#include "aads.h"
#include "lab_3.h"

int main() {
    namespace br3 = ::br3nder;

    std::ifstream file(R"(C:\Users\brend\Documents\ETU\tests_lab_3\tests_lab_3\f.txt)");

    adjacency_matrix adj_matrix;
    make_adjacency_matrix(file, adj_matrix);

    ford_focus(adj_matrix); //nice car brrrm brrrm...

    file.close();

	return 0;
}