/*
 * Implementation of color.h.
 */

#include "color.h"

Color::Color(int id, string name, string pathToSequence) {
    this->id = id;
    this->name = name;
    this->pathToSequence = pathToSequence;
}

Color::Color(int id, int numColors, string name, string pathToSequence) {
    this->id = id;
    this->name = name;
    this->pathToSequence = pathToSequence;
    this->bitVector = bit_vector(numColors, 0);
    bitVector[id] = 1;
}

Color::~Color() { }

string Color::getName() const {
    return name;
}

int Color::getID() const {
    return id;
}

bit_vector Color::getBitVector() const {
    return bitVector;
}
