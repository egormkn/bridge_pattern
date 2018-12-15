#include <iostream>

#include <boost/program_options.hpp>

#include "graph/Graph.h"
#include "api/SDLDrawingApi.h"
#include "api/SFMLDrawingApi.h"
#include "graph/MatrixGraph.h"
#include "graph/EdgeListGraph.h"

namespace opt = boost::program_options;

using namespace std;

int main(int argc, const char *argv[]) {

    opt::command_line_parser parser(argc, argv);
    opt::variables_map args;

    try {
        opt::options_description options("Program options");
        options.add_options()
                ("help,h", "Help screen")
                ("api,a", opt::value<string>()->required()->default_value("sdl"), "Graphic API (sdl/sfml)")
                ("type,t", opt::value<string>()->required(), "Graph data type (matrix/list)")
                ("file,f", opt::value<string>()->required(), "Input file");

        opt::positional_options_description pos;
        pos.add("file", -1);

        opt::parsed_options parsed_options = parser.options(options).positional(pos).run();
        opt::store(parsed_options, args);

        if (args.count("help")) {
            cout << options << '\n';
            return 0;
        }

        opt::notify(args);

        cout << "Using api: " << args["api"].as<string>() << '\n';
        cout << "Using type: " << args["type"].as<string>() << '\n';
        cout << "Using file: " << args["file"].as<string>() << '\n';

        string filename = args["file"].as<string>();
        shared_ptr<DrawingApi> api;
        shared_ptr<Graph> graph;

        if (args["api"].as<string>() == "sdl") {
            api = make_shared<SDLDrawingApi>("SDL Window", 1280, 720);
        } else {
            api = make_shared<SFMLDrawingApi>("SFML Window", 1280, 720);
        }

        if (args["type"].as<string>() == "matrix") {
            graph = make_shared<MatrixGraph>(api);
        } else {
            graph = make_shared<EdgeListGraph>(api);
        }

        graph->read(args["file"].as<string>());
        graph->draw();

    } catch (const exception &ex) {
        cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}