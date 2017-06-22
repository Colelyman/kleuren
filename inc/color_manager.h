/**
 * @class ColorManager
 *
 * ColorManager holds all of the colors, and manages when they
 * will be created and destroyed. 
 *
 * @author Cole Lyman
 *
 * @date 2017/6/21
 *
 */

#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <string>
#include <map>

#include "color.h"

using std::string;
using std::map;

class ColorManager {

    public:
        ColorManager();

        ~ColorManager();

        /**
         * Adds a color to the de Bruijn graph.
         * @param colorName a human readable name (preferably with no whitespace) for the color
         * @param the path to the BWT file to load into the FMIndex
         * @returns the instance of the color after it is added
         */
        Color* addColor(string& colorName, string& pathToBWT);

        /// Returns the color given a colorID
        Color* getColor(int colorID);

    private:
        /// Removes all colors and properly deallocates them
        void removeAllColors();

        // colors is where each Color is located.
        // @key is of type int and represents the id of the Color.
        // @value is of type Color*.
        map<int, Color*> colors;

        // numColors is the total number of colors added.
        // It also determines the ID of each Color.
        int numColors;

};

#endif // COLOR_MANAGER_H
