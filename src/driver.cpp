/*
 * Implementation of driver.h
 */

#include <iostream>
#include <memory>

#include "driver.h"

extern "C" {
    #include <bft/bft.h>
}

using std::cout;
using std::endl;

Driver::Driver(Args args) {
    this->args = args;

    char* bftFilePath = (char*) malloc(args.getBFTFilePath().length());
    bftFilePath = args.getBFTFilePath().c_str();
	graph = new Graph(bftFilePath);
    //colorManager = ColorManager(colorFile);
    //graph->setNumColors(colorManager.getNumColors());

    // open the kmer file
    kmerFile = new ifstream();
    kmerFile->open(args.getKmerFilePath());

    kmerBank = new KmerBank(kmerFile);

    bubbleBuilder = new BubbleBuilder(graph);

    // create the output bubble file
    if(!args.getBubbleFilePath().empty()) {
        bubbleFile = new ofstream();
        bubbleFile->open(args.getBubbleFilePath());
    }

    //bubbleManager = BubbleManager(bubbleFile, matrixFile, &colorManager);
}

Driver::~Driver() {
    kmerFile->close();
    delete kmerFile;
    delete kmerBank;
	delete graph;
	delete bubbleBuilder;
    if(!args.getBubbleFilePath().empty()) {
        bubbleFile->close();
        delete bubbleFile;
    }
}

void Driver::run() {
    string kmer = kmerBank->getNextKmer();
    shared_ptr<Color> color0 = colorManager.getColor(0);

    // iterate over the kmers
    while(kmer != "") {
        char* strKmer = const_cast<char*>(kmer.c_str());
        // find a start kmer for a bubble
        if(graph->isBFTKmer(strKmer)) {
            cout << "startKmer: " << strKmer << endl;
            BFT_kmer* bftKmer = graph->getBFTKmer(strKmer);
            // build the bubble
            Bubble bubble = bubbleBuilder->build(bftKmer, args.getN(), args.getMaxDepth());
            if(bubble.getPaths().empty()) { // no bubble was found, try next kmer
                cout << "\tno bubble" << endl;
                kmer = kmerBank->getNextKmer();
                continue;
            }
            if(!bubble.isValid(kmer.length())) { // the bubble is not valid, try next kmer
                cout << "\tinvalid bubble" << endl;
                kmer = kmerBank->getNextKmer();
                continue;
            }
            // write the bubble if there is a file to write to
            if(!args.getBubbleFilePath().empty()) {
                cout << "\tbubble found" << endl;
                bubbleManager.writeBubble(bubble);
            }
        }
        // get the next kmer
        kmer = kmerBank->getNextKmer();
    }

    return;
}

