/**
 * @class Driver
 *
 * This class is where the algorithms are started, and general logic
 * is performed to connect the various algorithms together.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 *
 */

#ifndef DRIVER_H
#define DRIVER_H

#include <set>
#include <fstream>

#include "args.h"
#include "color_manager.h"
#include "kmer_bank.h"
#include "bubble_builder.h"
#include "bubble_manager.h"
#include "graph.h"
#include "graph_builder.h"

using std::set;
using std::ifstream;
using std::ofstream;

class Driver {

    public:
        Driver(Args args);

        ~Driver();

        /// Starts the whole algorithm given the arguments
        void run();

    private:
        /// The only instance of the ColorManager, which regulates the addition,
        /// removal, and access of colors
        ColorManager colorManager;

        /// The pointer to the file handle that contains the colors
        ifstream* colorFile;

        /// The pointer to the file handle that contains the kmers
        ifstream* kmerFile;

        /// The pointer to the file handle that will output the bubbles
        ofstream* bubbleFile;

        /// The pointer to the file handle that will output the matrix
        ofstream* matrixFile;

        /// The KmerBank provides a super set of kmers for each color
        KmerBank* kmerBank;

		/// The Graph underlying structure to represent the Colored de Bruijn graph
		Graph* graph;

        /// The pointer to the object that builds the graph
        GraphBuilder* graphBuilder;

        /// Builds bubbles!
        BubbleBuilder* bubbleBuilder;

        /// Manages bubbles
        BubbleManager bubbleManager;

        /// The arguments for the current run
        Args args;

};

#endif // DRIVER_H
