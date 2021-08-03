#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Airport {
  string city;
  string DBTZ;
  string name;
  string country;
  string IATA_FAA;
  double longitude;
  string ICAO;
  string airport_ID;
  double latitude;
  string timezone;
  string DST;
  vector<string> destinations;

  void display(){
      cout << "City: " <<city << endl;
      cout << "DBTZ: " <<DBTZ << endl;
      cout << "Name: " <<name << endl;
      cout << "Country: " <<country << endl;
      cout << "IATA_FAA: " <<IATA_FAA << endl;
      cout << "Longitude: " <<longitude << endl;
      cout << "ICAO: " <<ICAO << endl;
      cout << "Airport ID: " <<airport_ID << endl;
      cout << "Latitude: " <<latitude << endl;
      cout << "Timezone: " <<timezone << endl;
      cout << "DST: " <<DST << endl;
      // cout << "Destinations: " << endl;
      //
      // for (auto const& dest: destinations){
      //     cout << " " << dest << endl;
      // }
  }
};
