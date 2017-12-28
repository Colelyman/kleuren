/*
 * Implementation of color_manager.h
 */

#include <sstream>
#include <set>
#include <map>

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
    map<string, string> colorValues;
    // iterate over each line in the file and store it in colorValues
    while(getline(*colorFile, line)) {
        // parse each line
        stringstream sstream(line);
        sstream >> colorName;
        sstream >> pathToSequence;
        colorValues[colorName] = pathToSequence;
    }
    numColors = colorValues.size();
    // add each color from colorValues
    int id = 0;
    for(auto const& element : colorValues) {
        shared_ptr<Color> color = addColor(element.first, element.second, id++);
        graphBuilder->addColor(element.second, color->getBitVector());
    }
}

shared_ptr<Color> ColorManager::addColor(string colorName, string pathToSequence, int id) {
    colors[id] = shared_ptr<Color>(new Color(id, numColors, colorName, pathToSequence));
    return colors[id];
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

size_t ColorManager::getNumColors() {
    return numColors;
}
