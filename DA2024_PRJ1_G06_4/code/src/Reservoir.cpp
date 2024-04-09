#include "Reservoir.h"

/* Constructor */

Reservoir::Reservoir(std::string name, std::string municipality, int id, std::string code, int maxDelivery) :
    Node(id, std::move(code)), name(std::move(name)), municipality(std::move(municipality)), max_delivery(maxDelivery) {}

/* Getters */

std::string Reservoir::getName() const { return name; }

std::string Reservoir::getMunicipality() const { return municipality; }

int Reservoir::getMaxDelivery() const { return max_delivery; }

/* Setters */

void Reservoir::setName(std::string newName) { Reservoir::name = std::move(newName); }

void Reservoir::setMunicipality(std::string newMunicipality) { Reservoir::municipality = std::move(newMunicipality); }

void Reservoir::setMaxDelivery(int newMaxDelivery) { max_delivery = newMaxDelivery; }
