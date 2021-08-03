#include "parser.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#define RADIO 6371

double toRadians(const double target) {
  double one_deg = M_PI / 180;
  return one_deg * target;
}

double distance(double lat1, double long1, double lat2, double long2) {
  lat1 = toRadians(lat1);
  long1 = toRadians(long1);
  lat2 = toRadians(lat2);
  long2 = toRadians(long2);

  double dlong = long2 - long1;
  double dlat = lat2 - lat1;

  double result =
      pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);

  result = 2 * asin(sqrt(result));

  result = result * RADIO;

  return result;
}

json getJsonFromFile(string fileName) {
  ifstream ifs;
  ifs.open(fileName, ifstream::in);
  json result = json::parse(ifs);
  return result;
}

unordered_map<string, double> getHeuristic(string airportId, json target) {
  unordered_map<string, double> result;
  double lat1;
  double long1;
  for (auto &airport : target) {
    string objectId = airport["Airport ID"];
    if (objectId == airportId) {
      lat1 = stod(airport["Latitude"].get<string>());
      long1 = stod(airport["Longitude"].get<string>());
      break;
    }
  }

  for (auto &airport : target) {
    string objectId = airport["Airport ID"];
    if (objectId == airportId) {
      result[objectId] = 0;
    } else {
      double lat2 = stod(airport["Latitude"].get<string>());
      double long2 = stod(airport["Longitude"].get<string>());
      result[objectId] = distance(lat1, long1, lat2, long2);
    }
  }
  return result;
}

UnDirectedGraph<string, double> getGraph(json target) {
  UnDirectedGraph<string, double> result;
  for (auto &airport : target) {
    string objectId = airport["Airport ID"].get<string>();
    result.insertVertex(objectId, objectId);
  }
  for (auto &airport : target) {
    string objectId = airport["Airport ID"].get<string>();
    vector<string> dest = airport["destinations"].get<vector<string>>();
    double lat1 = stod(airport["Latitude"].get<string>());
    double long1 = stod(airport["Longitude"].get<string>());
    for (auto &airportS : target) {
      if (dest.size() == 0) {
        break;
      }
      string target = airportS["Airport ID"].get<string>();
      auto it = find(dest.begin(), dest.end(), target);
      if (it != dest.end()) {
        double lat2 = stod(airportS["Latitude"].get<string>());
        double long2 = stod(airportS["Longitude"].get<string>());
        result.createEdge(objectId, target, distance(lat1, long1, lat2, long2));
        dest.erase(it);
      }
    }
  }
  return result;
}

Airport getairportfromid(string id, json target){
  Airport result;
  for (auto &airport : target) {
    string objectId = airport["Airport ID"].get<string>();
    if (objectId == id) {
      result.airport_ID = id;
      result.city = airport["City"].get<string>();
      result.DBTZ = airport["DBTZ"].get<string>();
      result.name = airport["Name"].get<string>();
      result.country = airport["Country"].get<string>();
      result.IATA_FAA = airport["IATA/FAA"].get<string>();
      result.longitude = stod(airport["Longitude"].get<string>());
      result.ICAO = airport["ICAO"].get<string>();
      result.latitude = stod(airport["Latitude"].get<string>());
      result.timezone = airport["Timezone"].get<string>();
      result.DST = airport["DST"].get<string>();
      vector<string> destinations =
          airport["destinations"].get<vector<string>>();
      result.destinations = destinations;
      break;
    }
  }
  return result;
}
