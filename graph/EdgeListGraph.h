#ifndef EDGELISTGRAPH_H
#define EDGELISTGRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <random>

#include "Graph.h"

class EdgeListGraph : public Graph {
private:
    std::vector<std::pair<int, int>> edges;
    size_t num_vertexes;

public:
    explicit EdgeListGraph(std::shared_ptr<DrawingApi> &api);

    void read(const std::string &file) override;

    void draw() override;
};


#endif // EDGELISTGRAPH_H
