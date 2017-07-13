/*
 * Implementation of driver.h
 */

#include "driver.h"

Driver::Driver(Args args) {
    this->args = args;

    colorManager = ColorManager();
    kmerBank = KmerBank(args.getKmerFilePath());
    bubbleBuilder = BubbleBuilder();
}

void Driver::run() {

    return;
}
