/*
 * Implementation of color_manager.h
 */

#include <sstream>
#include <set>

#include "color_manager.h"

using std::stringstream;
using std::set;

ColorManager::ColorManager(ifstream* fileStream, GraphBuilder* graphBuilder) {
    colorFile = fileStream;
    numColors = 0;
    this->graphBuilder = graphBuilder;
    addColors();
}

void ColorManager::addColors() {
    string line, colorName, pathToSequence;
    // iterate over each line in the file
    while(getline(*colorFile, line)) {
        // parse each line
        stringstream sstream(line);
        sstream >> colorName;
        sstream >> pathToSequence;
        shared_ptr<Color> color = addColor(colorName, pathToSequence);
        graphBuilder->addColor(pathToSequence, color->getBitVector());
    }
}

shared_ptr<Color> ColorManager::addColor(string colorName, string pathToSequence) {
    colors[numColors] = shared_ptr<Color>(new Color(numColors, colorName, pathToSequence));
    return colors[numColors++];
}

shared_ptr<Color> ColorManager::getColor(int colorID) {
    return colors[colorID];
}

/*
ColorSet ColorManager::getColors(unsigned int n) {
    set<shared_ptr<Color> > colorSet;
    for(auto const& color : colors) {
        colorSet.insert(color.second);
    }
    return ColorSet(colorSet, n);
}
*/

vector<string> ColorManager::getColorNames(bit_vector colorVector) {
	vector<string> names;
	for(unsigned int i = 0; i < colorVector.size(); i++) {
		if(colorVector[i]) {
			names.push_back(colors[i]->getName());
		}
	}
}

unsigned int ColorManager::getNumColors() {
    return numColors;
}
