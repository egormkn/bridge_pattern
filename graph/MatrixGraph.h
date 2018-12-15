#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <random>

#include "Graph.h"

class MatrixGraph : public Graph {

private:
    std::vector<std::vector<bool>> matrix;
    size_t num_vertexes;

public:
    explicit MatrixGraph(std::shared_ptr<DrawingApi> &api);

    void read(const std::string &file) override;

    void draw() override;
};

#endif // MATRIXGRAPH_H
