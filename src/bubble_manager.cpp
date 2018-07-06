/*
 * Implementation of bubble_manager.h
 */

#include <iostream>

#include "bubble_manager.h"

using std::cout;
using std::endl;

BubbleManager::BubbleManager(ofstream* bubbleFile, Graph* graph) {
    this->bubbleFile = bubbleFile;
    this->graph = graph;
    n = 0;
}

vector<string> BubbleManager::getColorNames(set<uint32_t> colors) {
    vector<string> colorNames;
    for(auto const& colorId : colors) {
        string colorName(graph->getColorFilePath(colorId));
        colorNames.push_back(colorName);
    }
    return colorNames;
}

void BubbleManager::writeBubble(Bubble bubble) {
    cout << "Size of bubble.getPaths(): " << bubble.getPaths().size() << endl;
    for(auto const& path : bubble.getPaths()) {
        // write the header
        *bubbleFile << "> bubble " << n << " for ";
        set<uint32_t> colors = path.second;
        vector<string> colorNames = getColorNames(colors);
        auto firstColor = colorNames.begin();
        *bubbleFile << *firstColor;
        colorNames.erase(firstColor);
        for(auto const& colorName : colorNames) {
            *bubbleFile << ", " << colorName;
        }
        *bubbleFile << endl;
        string seq = path.first;
        cout << "seq: " << seq << endl;

        // print out the sequence
        if(seq.length() <= 80) {
            *bubbleFile << seq << endl;
        }
        else {
            uint32_t count = 1;
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
