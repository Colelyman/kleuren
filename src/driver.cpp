/*
 * Implementation of driver.h
 */

#include "driver.h"

Driver::Driver(Args args) {
    this->args = args;

    colorManager = ColorManager();
    kmerBank = KmerBank();
    bubbleBuilder = BubbleBuilder();
    visitedKmers = new set<string>();
}

Driver::~Driver() {
    delete visitedKmers;
}

void Driver::run() {

    return;
}
