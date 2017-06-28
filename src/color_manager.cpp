/*
 * Implementation of color_manager.h
 */

#include "color_manager.h"

ColorManager::ColorManager() {
    numColors = 0;
}

ColorManager::~ColorManager() {
    removeAllColors();
}

Color* ColorManager::addColor(string& colorName, string& pathToBWT) {
    colors[numColors] = new Color(numColors, colorName, pathToBWT);
    numColors++;
}

Color* ColorManager::getColor(int colorID) {
    return colors[colorID];
}

void ColorManager::removeAllColors() {
    // iterate over each color in colors
    for(auto const& color : colors) {
        // deallocate the color
        delete color.second;
    }
}
