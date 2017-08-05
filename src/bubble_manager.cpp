/*
 * Implementation of bubble_manager.h
 */

#include <iostream>

#include "bubble_manager.h"

using std::cout;
using std::endl;

BubbleManager::BubbleManager(ofstream* bubbleFile, ofstream* matrixFile) {
    this->bubbleFile = bubbleFile;
    this->matrixFile = matrixFile;
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

pair<int, int> flipPair(pair<int, int> p) {
    pair<int, int> flippedPair = pair<int, int>(p.second, p.first);
    return flippedPair;
}

void BubbleManager::countSharedKmers(Bubble bubble, unsigned int kmerLen) {
    // count the shared kmers in the bubble
    map<pair<int, int>, unsigned int> results = bubble.runSharedKmerCount(kmerLen);

    // insert the results into the matrix
    for(auto const& result : results) {
        // check if the flipped color pair is in the matrix
        pair<int, int> flippedColors = flipPair(result.first);
        if(sharedKmerMatrix.find(flippedColors) != sharedKmerMatrix.end()) {
            // add the number of shared kmers to the existing count
            sharedKmerMatrix[flippedColors].first += result.second;
            // increment the count of the number of bubbles the colors occur in
            sharedKmerMatrix[flippedColors].second += 1;
        }
        else if(sharedKmerMatrix.find(result.first) != sharedKmerMatrix.end()) {
            // add the number of shared kmers to the existing count
            sharedKmerMatrix[result.first].first += result.second;
            // increment the count of the number of bubbles the colors occur in
            sharedKmerMatrix[result.first].second += 1;
        }
        else { // the pair and the flipped pair are not found in sharedKmerMatrix
            // create a new entry with the number of shared kmers and 1 bubble present
            sharedKmerMatrix[result.first] = pair<unsigned int, unsigned int>(result.second, 1);
        }
    }
}

map<int, map<int, float> > BubbleManager::averageSharedKmerMatrix() {
    map<int, map<int, float> > averagedMatrix;
    for(auto const& entry : sharedKmerMatrix) {
        unsigned int numSharedKmers = entry.second.first;
        unsigned int totalNumBubbles = entry.second.second;
        averagedMatrix[entry.first.first][entry.first.second] = (float) numSharedKmers / (float) totalNumBubbles;
    }
    
    return averagedMatrix;
}

void BubbleManager::writeSharedKmerMatrix(map<int, map<int, float> > matrix, ColorManager& colorManager) {
    // write how many colors are present in the matrix on the first line
    *matrixFile << colorManager.getNumColors() << endl;
    for(unsigned int i = 0; i < colorManager.getNumColors(); i++) {
        // write the name of the color, essentiall the left-most column
        *matrixFile << colorManager.getColor(i)->getName();
        for(unsigned int j = 0; j < i; j++) {
            // write the corresponding score
            *matrixFile << " " << matrix[i][j];
        }
        // move to the next row
        *matrixFile << endl;
    }
}
