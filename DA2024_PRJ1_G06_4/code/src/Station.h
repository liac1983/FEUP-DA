#ifndef STATION_H
#define STATION_H

#include "Node.h"

/**
 * @brief Class representing a station in the water supply network.
 */
class Station : public Node {
public:

    /* Constructor */
    Station(int id, std::string code);

};

#endif /* STATION_H */
