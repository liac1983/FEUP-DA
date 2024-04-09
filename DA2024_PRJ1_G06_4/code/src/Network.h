#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Node.h"

#include "City.h"
#include "Station.h"
#include "Reservoir.h"

/**
 * @brief Class representing the water supply network.
 */
class Network {
public:

    /* Constructor */
    Network();

    /* Destructor */
    ~Network();

    /* Getters */
    Node *getSuperSrc() const;
    Node *getSuperSink() const;
    const std::vector<City *> &getCitySet() const;
    const std::vector<Station *> &getStationSet() const;
    const std::vector<Reservoir *> &getReservoirSet() const;
    const std::unordered_map<std::string, Node *> &getNodeSet() const;

    /* Setters */
    void setSuperSrc(Node *superSrc);
    void setSuperSink(Node *superSink);
    void setCitySet(const std::vector<City *> &citySet);
    void setStationSet(const std::vector<Station *> &stationSet);
    void setReservoirSet(const std::vector<Reservoir *> &reservoirSet);
    void setNodeSet(std::unordered_map<std::string, Node *> &nodeSet);

    /* Functions */
    void deleteNetwork(); /**< Delete the network. */
    void createNetwork(const std::string& dataPath); /**< Create the network from data files. */
    Node *findNode(const std::string& nodeCode); /**< Find a node by its code. */
    void removeReservoir(Reservoir *r); /**< Remove a reservoir from the network. */
    void removeStation(Station *s); /**< Remove a station from the network. */
    void resetNetwork(); /**< Reset the network. */

    /* Parsing */
    void readStations(const std::string &fileLocation); /**< Read station data from a file. */
    void readCities(const std::string &fileLocation); /**< Read city data from a file. */
    void readReservoirs(const std::string &fileLocation); /**< Read reservoir data from a file. */
    void readPipes(const std::string &fileLocation); /**< Read pipe data from a file. */
    void readSuperElements(); /**< Read super elements of the network. */

    /* Max-Flow */
    bool findAugmentingPath(Node *s, Node *t); /**< Find an augmenting path for the given source and sink nodes. */
    static int findMinResidualAlongPath(Node *s, Node *t); /**< Find the minimum residual along an augmenting path. */
    static void augmentFlowAlongPath(Node *s, Node *t, int f); /**< Augment flow along an augmenting path. */
    int edmondsKarp(); /**< Perform the Edmonds-Karp algorithm to find the maximum flow in the network. */

private:

    Node* superSrc; /**< Super source node of the network. */
    Node* superSink; /**< Super sink node of the network. */

    std::vector<City*> citySet; /**< Set of cities in the network. */
    std::vector<Station*> stationSet; /**< Set of stations in the network. */
    std::vector<Reservoir*> reservoirSet; /**< Set of reservoirs in the network. */

    std::unordered_map<std::string, Node *> nodeSet; /**< Set of nodes in the network. */

};

#endif /* NETWORK_H */
