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
#include <memory>
#include <vector>

#include "color.h"
#include "graph.h"

using std::string;
using std::map;
using std::ifstream;
using std::shared_ptr;
using std::vector;

class ColorManager {

    public:
        ColorManager(Graph* graph);

        ~ColorManager();

        /// Adds all of the colors from the color file
        void addColors();

        /**
         * Adds a color to the de Bruijn graph.
         * @param colorName a human readable name (preferably with no whitespace) for the color
         * @param the path to the BWT file to load into the FMIndex
         * @returns the instance of the color after it is added
         */
        Color* addColor(string colorName, string pathToBWT, uint32_t id);

        /// Returns the color given a colorID
        Color* getColor(uint32_t colorID);

		/**
		 * Parses through colors and returns the subsequent color names.
		 * @param colors the bit_vector of colors to parse through.
		 * @returns a vector of color names.
		 */
		vector<string> getColorNames(uint32_t* colors);

        /// Returns the number of colors in the ColorManager
        size_t getNumColors();

    private:
        /// Extracts the name of the genome file 
        string parseNameFromPath(char* path);

        /// The pointer to the file handle of the color file
        Graph* graph;

        /// colors is where each Color is located.
        /// @key is of type uint32_t and represents the id of the Color.
        /// @value is of type Color*.
        map<uint32_t, Color*> colors;

};

#endif // COLOR_MANAGER_H
