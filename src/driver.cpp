/*
 * Implementation of driver.h
 */

#include "driver.h"
#include "color_set.h"

Driver::Driver(Args args) {
    this->args = args;

    // open the color file
    colorFile = new ifstream();
    colorFile->open(args.getColorsFilePath());
    colorManager = ColorManager(colorFile);

    // open the kmer file
    kmerFile = new ifstream();
    kmerFile->open(args.getKmerFilePath());

    kmerBank = new KmerBank(kmerFile);
    bubbleBuilder = BubbleBuilder();

    // create the output bubble file
    if(!args.getBubbleFilePath().empty()) {
        bubbleFile = new ofstream();
        bubbleFile->open(args.getBubbleFilePath());
        bubbleManager = BubbleManager(bubbleFile);
    }
}

Driver::~Driver() {
    colorFile->close();
    delete colorFile;
    kmerFile->close();
    delete kmerFile;
    delete kmerBank;
    if(!args.getBubbleFilePath().empty()) {
        bubbleFile->close();
        delete bubbleFile;
    }
}

void Driver::run() {
    string kmer = kmerBank->getNextKmer();
    ColorSet colors = colorManager.getColors(args.getN());

    // iterate over the kmers
    while(kmer != "") {
        // find a start kmer for a bubble
        if(colors.nContainsKmer(kmer)) {
            // build the bubble
            Bubble bubble = bubbleBuilder.build(kmer, colors, 100);
            // write the bubble if there is a file to write to
            if(!args.getBubbleFilePath().empty()) {
                bubbleManager.writeBubble(bubble);
            }
        }
        // get the next kmer
        kmer = kmerBank->getNextKmer();
    }

    return;
}

