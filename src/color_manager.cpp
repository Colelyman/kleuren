/*
 * Implementation of color_manager.h
 */

#include <sstream>
#include <set>

#include "color_manager.h"

using std::stringstream;
using std::set;

ColorManager::ColorManager(ifstream* fileStream) {
    colorFile = fileStream;
    numColors = 0;
}

ColorManager::~ColorManager() {
    removeAllColors();
}

void ColorManager::addColors() {
    string line, colorName, pathToBWT;
    // iterate over each line in the file
    while(getline(*colorFile, line)) {
        // parse each line
        stringstream sstream(line);
        sstream >> colorName;
        sstream >> pathToBWT;
        addColor(colorName, pathToBWT);
    }
}

Color* ColorManager::addColor(string& colorName, string& pathToBWT) {
    colors[numColors] = new Color(numColors, colorName, pathToBWT);
    return colors[numColors++];
}

Color* ColorManager::getColor(int colorID) {
    return colors[colorID];
}

ColorSet ColorManager::getColors(unsigned int n) {
    set<Color*> colorSet;
    for(auto const& color : colors) {
        colorSet.insert(color.second);
    }
    return ColorSet(colorSet, n);
}

void ColorManager::removeAllColors() {
    // iterate over each color in colors
    for(auto const& color : colors) {
        // deallocate the color
        delete color.second;
    }
}
