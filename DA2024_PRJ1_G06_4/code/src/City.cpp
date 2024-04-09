#include "City.h"

/* Constructor */

City::City(std::string name, int id, std::string code, float demand, std::string population) :
    Node(id, std::move(code)), name(std::move(name)), demand(demand), population(std::move(population)) {}

/* Getters */

std::string City::getName() const { return name; }

float City::getDemand() const { return demand; }

std::string City::getPopulation() const { return population; }

/* Setters */

void City::setName(std::string newName) { City::name = std::move(newName); }

void City::setDemand(float newDemand) { City::demand = newDemand; }

void City::setPopulation(std::string newPopulation) { City::population = std::move(newPopulation); }
