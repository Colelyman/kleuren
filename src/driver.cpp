/*
 * Implementation of driver.h
 */

#include "driver.h"

class Driver {

    public:

        Driver() {
            visitedKmers = new set<string>();
        }

        ~Driver() {
            delete visitedKmers;
        }

        void run(Args args) {

            return;
        }

    private:

        ColorManager colorManager;

        KmerBank kmerBank;

        BubbleBuilder bubbleBuilder;

        set<string>* visitedKmers;

}
