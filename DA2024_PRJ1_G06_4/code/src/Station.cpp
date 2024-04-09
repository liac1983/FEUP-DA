#include "Station.h"

/* Constructor */

Station::Station(int id, std::string code) : Node(id, std::move(code)) {}
