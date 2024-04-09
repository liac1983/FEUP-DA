#include "Network.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "City.h"
#include "Station.h"
#include "Reservoir.h"

using namespace std;

void filterString(string& input) {
    string temp;
    for (char c : input)
        if (isalnum(c) || c == '_')
            temp += c;
    input = temp;
}

void Network::readStations(const std::string &fileLocation) {

    std::fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"readStations\" could not read the data");

    std::string line;
    getline(file, line); // Skip fist line

    std::string ID, Code;

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);

        getline(ss, ID, ',');
        getline(ss, Code);
        filterString(Code);

        if (ID.empty() || Code.empty()) continue;

        auto station = new Station(stoi(ID), Code);

        nodeSet[Code] = station;
        stationSet.push_back(station);
    }

    std::sort(stationSet.begin(), stationSet.end(), [](Station* a, Station* b) {
        return a->getID() < b->getID();
    });

    file.close();
}

void Network::readCities(const std::string &fileLocation) {

    std::fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"readCities\" could not read the data");

    std::string line;
    getline(file, line); // Skip fist line

    std::string ID, Code, Name, Demand, Population;

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);

        getline(ss, Name, ',');
        getline(ss, ID, ',');
        getline(ss, Code, ',');
        getline(ss, Demand, ',');
        getline(ss, Population, '\"');
        getline(ss, Population);
        filterString(Population);

        if (Name.empty() || ID.empty() || Code.empty() || Demand.empty() || Population.empty()) continue;

        auto city = new City(Name, stoi(ID), Code, stof(Demand), Population);
        city->setCapacity(stoi(Demand)); city->setCapacityValue(stoi(Demand));

        nodeSet[Code] = city;
        citySet.push_back(city);
    }

    std::sort(citySet.begin(), citySet.end(), [](City* a, City* b) {
        return a->getID() < b->getID();
    });

    file.close();
}

void Network::readReservoirs(const std::string &fileLocation) {

    std::fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"readReservoirs\" could not read the data");

    std::string line;
    getline(file, line); // Skip fist line

    std::string ID, Code, Name, Municipality, MaxDelivery;

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);

        getline(ss, Name, ',');
        getline(ss, Municipality, ',');
        getline(ss, ID, ',');
        getline(ss, Code, ',');
        getline(ss, MaxDelivery);
        filterString(MaxDelivery);

        if (Name.empty() || Municipality.empty() || ID.empty() || Code.empty() || MaxDelivery.empty()) continue;

        auto reservoir = new Reservoir(Name, Municipality, stoi(ID), Code, stoi(MaxDelivery));
        reservoir->setCapacity(stoi(MaxDelivery)); reservoir->setCapacityValue(stoi(MaxDelivery));

        nodeSet[Code] = reservoir;
        reservoirSet.push_back(reservoir);
    }

    std::sort(reservoirSet.begin(), reservoirSet.end(), [](Reservoir* a, Reservoir* b) {
        return a->getID() < b->getID();
    });

    file.close();
}

void Network::readPipes(const std::string &fileLocation) {

    std::fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"readPipes\" could not read the data");

    std::string line;
    getline(file, line); // Skip fist line

    std::string SRC, DEST, Capacity, Direction;

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);

        getline(ss, SRC, ',');
        getline(ss, DEST, ',');
        getline(ss, Capacity, ',');
        getline(ss, Direction);
        filterString(Direction);

        if (SRC.empty() || DEST.empty() || Capacity.empty() || Direction.empty()) continue;

        Node *src = findNode(SRC);
        Node *dest = findNode(DEST);

        if (src == nullptr || dest == nullptr) continue;

        src->addPipe(dest, stoi(Capacity));

        if (Direction == "0") dest->addPipe(src, 0);
    }

    file.close();
}

void Network::readSuperElements()
{
    for (const auto& pair : nodeSet)
    {
        if (pair.second->getCode().substr(0,1) == "R")
            superSrc->addPipe(pair.second, INT16_MAX);

        if (pair.second->getCode().substr(0,1) == "C")
            pair.second->addPipe(superSink, INT16_MAX);
    }

    nodeSet["S_SRC"] = superSrc;
    nodeSet["S_SINK"] = superSink;
}
