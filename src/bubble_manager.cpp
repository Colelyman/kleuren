/*
 * Implementation of bubble_manager.h
 */

#include <iostream>

#include "bubble_manager.h"

using std::cout;
using std::endl;

BubbleManager::BubbleManager(ofstream* file) {
    bubbleFile = file;
    n = 0;
}

void BubbleManager::writeBubble(Bubble bubble) {
    cout << "Size of bubble.getPaths(): " << bubble.getPaths().size() << endl;
    for(auto const& path : bubble.getPaths()) {
        // write the header
        *bubbleFile << "> bubble " << n << " for ";
        vector<string> colorNames = bubble.getColorNames(path.first);
        *bubbleFile << colorNames.at(0);
        colorNames.erase(colorNames.begin());
        for(auto const& colorName : colorNames) {
            *bubbleFile << ", " << colorName;
        }
        *bubbleFile << endl;
        string seq = path.first.getSequence();
        cout << "seq: " << seq << endl;

        // print out the sequence
        if(seq.length() <= 80) {
            *bubbleFile << seq << endl;
        }
        else {
            unsigned int count = 1;
            while(count < seq.length()) {
                *bubbleFile << seq.at(count);
                if(!(count % 80)) {
                    *bubbleFile << endl;
                }
                count++;
            }
            *bubbleFile << endl;
        }
    }
    // increment the bubble counter
    n++;
}
