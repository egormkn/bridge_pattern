#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(std::shared_ptr<DrawingApi> &api) : Graph(api), num_vertexes(0) {}

void MatrixGraph::read(const std::string &file) {
    std::ifstream input(file);
    if (!input) {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream is(line);
        matrix.emplace_back(std::istream_iterator<bool>(is), std::istream_iterator<bool>());
    }

    num_vertexes = matrix.size();

    input.close();
}

void MatrixGraph::draw() {
    std::pair<int, int> center(api->getWidth() / 2, api->getHeight() / 2);
    double radius = std::min(api->getWidth() / 2.0, api->getHeight() / 2.0) * 0.8;

    api->setDrawColor(255, 255, 255);
    api->clear();
    api->setDrawColor(250, 250, 250);
    api->drawCircle(center.first, center.second, static_cast<int>(radius));

    double vertex_raduis = std::min((2 * M_PI * radius) / num_vertexes * 0.8, 30.0);

    double angle = -M_PI / 2.0;
    double delta = 2 * M_PI / num_vertexes;

    std::vector<std::pair<int, int>> points;
    for (int i = 0; i < num_vertexes; i++) {
        int x = static_cast<int>(radius * cos(angle)) + center.first;
        int y = static_cast<int>(radius * sin(angle)) + center.second;
        points.emplace_back(x, y);
        angle += delta;
    }

    api->setDrawColor(200, 0, 0);

    for (int i = 0; i < num_vertexes; i++) {
        for (int j = 0; j < num_vertexes; j++) {
            if (!matrix[i][j]) continue;
            int from = i;
            int to = j;
            api->drawLine(points[from].first, points[from].second, points[to].first, points[to].second);
        }
    }

    std::mt19937 rng;
    std::uniform_int_distribution<int> random(0, 256);
    for (std::pair<int, int> &point : points) {
        int r = random(rng) % 256;
        int g = random(rng) % 256;
        int b = random(rng) % 256;
        api->setDrawColor(r, g, b);
        api->drawCircle(point.first, point.second, static_cast<int>(vertex_raduis));
    }

    api->show();
}
