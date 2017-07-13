/*
 * Implementation of driver.h
 */

#include "driver.h"

Driver::Driver(Args args) {
    this->args = args;

    colorManager = ColorManager();
    kmerFile = new ifstream();
    kmerFile->open(args.getKmerFilePath());
    kmerBank = KmerBank(kmerFile);
    bubbleBuilder = BubbleBuilder();
}

Driver::~Driver() {
    kmerFile->close();
    delete kmerFile;
}

void Driver::run() {

    return;
}
