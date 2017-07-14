/*
 * Implementation of driver.h
 */

#include "driver.h"

Driver::Driver(Args args) {
    this->args = args;

    colorFile = new ifstream();
    colorFile->open(args.getColorsFilePath());
    colorManager = ColorManager(colorFile);
    kmerFile = new ifstream();
    kmerFile->open(args.getKmerFilePath());
    kmerBank = KmerBank(kmerFile);
    bubbleBuilder = BubbleBuilder();
}

Driver::~Driver() {
    colorFile->close();
    delete colorFile;
    kmerFile->close();
    delete kmerFile;
}

void Driver::run() {

    return;
}
