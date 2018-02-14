/*
 * Implementation of color.h.
 */

#include "color.h"

Color::Color(uint32_t id, string name) {
    this->id = id;
    this->name = name;
}

string Color::getName() const {
    return name;
}

uint32_t Color::getID() const {
    return id;
}
