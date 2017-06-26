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

#include "args.h"
#include "color_manager.h"
#include "kmer_bank.h"
#include "bubble_builder.h"

using std::set;

class Driver {

    public:
        Driver();

        ~Driver();

        /// Starts the whole algorithm given the arguments
        void run(Args args);

    private:
        /// The only instance of the ColorManager, which regulates the addition,
        /// removal, and access of colors
        ColorManager colorManager;

        /// The KmerBank provides a super set of kmers for each color
        KmerBank kmerBank;

        /// Builds bubbles!
        BubbleBuilder bubbleBuilder;

        /// Holds the kmers that have been visited already so that they are not repeated
        /// @todo implement a bloom filter for efficiency instead of a set?
        set<string>* visitedKmers;

};

#endif // DRIVER_H
