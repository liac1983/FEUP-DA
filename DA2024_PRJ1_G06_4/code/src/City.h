#ifndef CITY_H
#define CITY_H

#include "Node.h"

/**
 * @brief Class representing a city in the water supply network.
 */
class City : public Node {
public:

    /* Constructor */
    City(std::string name, int id, std::string code, float demand, std::string population);

    /* Getters */
    std::string getName() const;
    float getDemand() const;
    std::string getPopulation() const;

    /* Setters */
    void setName(std::string newName);
    void setDemand(float newDemand);
    void setPopulation(std::string newPopulation);

private:

    std::string name;
    float demand;
    std::string population;

};

#endif /* CITY_H */
