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
#include <fstream>

#include "color.h"
#include "color_set.h"

using std::string;
using std::map;
using std::ifstream;

class ColorManager {

    public:
        ColorManager() { }

        ColorManager(ifstream* fileStream);

        ~ColorManager();

        /// Adds all of the colors from the color file
        void addColors();

        /**
         * Adds a color to the de Bruijn graph.
         * @param colorName a human readable name (preferably with no whitespace) for the color
         * @param the path to the BWT file to load into the FMIndex
         * @returns the instance of the color after it is added
         */
        Color* addColor(string& colorName, string& pathToBWT);

        /// Returns the color given a colorID
        Color* getColor(int colorID);

        /** 
         * Returns colors as a ColorSet, with n provided.
         * @param n the parameter to pass to the newly formed ColorSet.
         * @returns a ColorSet with the colors, and with the provided n
         */
        ColorSet getColors(unsigned int n);

    private:
        /// Removes all colors and properly deallocates them
        void removeAllColors();

        /// The pointer to the file handle of the color file
        ifstream* colorFile;

        /// colors is where each Color is located.
        /// @key is of type int and represents the id of the Color.
        /// @value is of type Color*.
        map<int, Color*> colors;

        /// numColors is the total number of colors added.
        /// It also determines the ID of each Color.
        unsigned int numColors;

};

#endif // COLOR_MANAGER_H
