/*
 * Implementation of driver.h
 */

#include "driver.h"

Driver::Driver() {
    visitedKmers = new set<string>();
}

Driver::~Driver() {
    delete visitedKmers;
}

void Driver::run(Args args) {

    return;
}
