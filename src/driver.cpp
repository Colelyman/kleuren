/*
 * Implementation of driver.h
 */

#include <iostream>
#include <memory>

#include "driver.h"

using std::cout;
using std::endl;

unsigned int Graph::kmerLen;

Driver::Driver(Args args) {
    this->args = args;

    // open the color file
    colorFile = new ifstream();
    colorFile->open(args.getColorsFilePath());
    Graph::kmerLen = args.getKmerLen();
	graph = new Graph();
    graphBuilder = new GraphBuilder(graph, args.getKmerLen());
    colorManager = ColorManager(colorFile, graphBuilder);
    graph->setNumColors(colorManager.getNumColors());

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

    // create the output matrix file
    if(!args.getMatrixFilePath().empty()) {
        matrixFile = new ofstream();
        matrixFile->open(args.getMatrixFilePath());
    }

    bubbleManager = BubbleManager(bubbleFile, matrixFile, &colorManager);
}

Driver::~Driver() {
    colorFile->close();
    delete colorFile;
    kmerFile->close();
    delete kmerFile;
    delete kmerBank;
	delete graph;
    delete graphBuilder;
	delete bubbleBuilder;
    if(!args.getBubbleFilePath().empty()) {
        bubbleFile->close();
        delete bubbleFile;
    }
    if(!args.getMatrixFilePath().empty()) {
        matrixFile->close();
        delete matrixFile;
    }
}

void Driver::run() {
    string kmer = kmerBank->getNextKmer();
    shared_ptr<Color> color0 = colorManager.getColor(0);
    //ColorSet colors = colorManager.getColors(args.getN());

    // iterate over the kmers
    while(kmer != "") {
        // find a start kmer for a bubble
        if(graph->isKmer(kmer)) {
            cout << "startKmer: " << kmer << endl;
            // build the bubble
			Vertex v = Vertex(kmer, colorManager.getNumColors());
            Bubble bubble = bubbleBuilder->build(v, args.getN(), args.getMaxDepth());
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
            // construct matrix if there is a file 
            if(!args.getMatrixFilePath().empty()) {
                bubbleManager.countSharedKmers(bubble, kmer.length()); 
            }
        }
        // get the next kmer
        kmer = kmerBank->getNextKmer();
    }

    // write the matirx to the file 
    if(!args.getMatrixFilePath().empty()) {
        //bubbleManager.writeSharedKmerMatrix(bubbleManager.averageSharedKmerMatrix());
    }

    return;
}

