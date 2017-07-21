/*
 * Implementation of bubble_manager.h
 */

#include "bubble_manager.h"

BubbleManager::BubbleManager(ofstream* file) {
    bubbleFile = file;
    n = 0;
}

void BubbleManager::writeBubble(Bubble bubble) {
    for(auto const& path : bubble.getPaths()) {
        // write the header
        *bubbleFile << "> bubble " << n++ << " for ";
        for(auto const& colorName : path.getColorNames()) {
            *bubbleFile << colorName << ", ";
        }
        *bubbleFile << endl;
        string seq = path.getSequence();

        // print out the sequence
        if(seq.length() <= 80) {
            *bubbleFile << seq << endl;
        }
        else {
            unsigned int count = 0;
            while(count < seq.length()) {
                *bubbleFile << seq.at(count);
                if(!(count % 80)) {
                    *bubbleFile << endl;
                }
                count++;
            }
        }
    }
}
