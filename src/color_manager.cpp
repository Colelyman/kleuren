/*
 * Implementation of color_manager.h
 */

#include <sstream>
#include <set>
#include <map>

#include "color_manager.h"

using std::stringstream;
using std::set;

ColorManager::ColorManager(Graph* graph) {
    this->graph = graph;
    addColors();
}

ColorManager::~ColorManager() {
    // TODO delete all the color pointers in colors
}

void ColorManager::addColors() {
    for(uint32_t i = 0; i < graph->getNumColors(); i++) {
        char* colorFilePath = graph->getColorFilePath(i);
        string colorName = parseNameFromPath(colorFilePath);
        addColor(colorName, string(colorFilePath), i);
    }
}

string ColorManager::parseNameFromPath(char* path) {
    char* fileName = basename(path);
    // strip any file extensions if present
    char* running = strdup(fileName);
    const char delimiter[] = ".";
    // assign upto the first delimiter as the name
    char* name = strsep(&running, delimiter);
    free(running);
    return string(name);
}

Color* ColorManager::addColor(string colorName, string pathToSequence, uint32_t id) {
    colors[id] = new Color(id, colorName);
    return colors[id];
}

Color* ColorManager::getColor(uint32_t colorID) {
    return colors[colorID];
}

vector<string> ColorManager::getColorNames(uint32_t* colorIds) {
	vector<string> names;
	for(uint32_t i = 1; i <= colorIds[0]; i++) {
        names.push_back(string((colors[i])->getName()));
	}
    return names;
}

size_t ColorManager::getNumColors() {
    return graph->getNumColors();
}
