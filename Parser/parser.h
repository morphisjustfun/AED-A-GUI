#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string.h>
#include <string>
#include <unordered_map>
#include "Graph/UndirectedGraph.h"
#include "airport.h"

using json = nlohmann::json;
using namespace std;

double toRadians(const double target);

double distance(double lat1, double long1, double lat2, double long2);
json getJsonFromFile(string fileName);

unordered_map<string, double> getHeuristic(string airportId, json target);

UnDirectedGraph<string, double> getGraph(json target);

Airport getairportfromid(string id, json target);
