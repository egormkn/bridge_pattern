#ifndef BRIDGE_PATTERN_GRAPH_H
#define BRIDGE_PATTERN_GRAPH_H

#include <memory>

#include "../api/DrawingApi.h"

class Graph {

protected:
    std::shared_ptr<DrawingApi> api;

public:
    explicit Graph(std::shared_ptr<DrawingApi> &api);

    virtual void read(const std::string &file) = 0;

    virtual void draw() = 0;
};


#endif //BRIDGE_PATTERN_GRAPH_H
