/*
 * Implementation of driver.h
 */

#include <iostream>
#include <memory>

#include "driver.h"
#include "color_set.h"

using std::cout;
using std::endl;

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
    shared_ptr<Color> color0 = colorManager.getColor(0);
    ColorSet colors = colorManager.getColors(args.getN());

    // iterate over the kmers
    while(kmer != "") {
        // find a start kmer for a bubble
        if(colors.nContainsKmer(kmer)) {
            cout << "startKmer: " << kmer << endl;
            // build the bubble
            Bubble bubble = bubbleBuilder.build(kmer, colors, 200);
            if(bubble.getPaths().empty()) { // no bubble was found, try next kmer
                cout << "no bubble: " << kmer << endl;
                kmer = kmerBank->getNextKmer();
                continue;
            }
            if(!bubble.isValid()) { // the bubble is not valid, try next kmer
                kmer = kmerBank->getNextKmer();
                continue;
            }
            // write the bubble if there is a file to write to
            if(!args.getBubbleFilePath().empty()) {
                cout << "bubble found: " << kmer << endl;
                bubbleManager.writeBubble(bubble);
            }
        }
        // get the next kmer
        kmer = kmerBank->getNextKmer();
    }

    return;
}

