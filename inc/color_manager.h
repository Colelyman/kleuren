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
#include "color_set.h"
#include "graph_builder.h"

using std::string;
using std::map;
using std::ifstream;
using std::shared_ptr;
using std::vector;

class ColorManager {

    public:
        ColorManager() { }

        ColorManager(ifstream* fileStream, GraphBuilder* graphBuilder);

        /// Adds all of the colors from the color file
        void addColors();

        /**
         * Adds a color to the de Bruijn graph.
         * @param colorName a human readable name (preferably with no whitespace) for the color
         * @param the path to the BWT file to load into the FMIndex
         * @returns the instance of the color after it is added
         */
        shared_ptr<Color> addColor(string colorName, string pathToBWT);

        /// Returns the color given a colorID
        shared_ptr<Color> getColor(int colorID);

        /** 
         * Returns colors as a ColorSet, with n provided.
         * @param n the parameter to pass to the newly formed ColorSet.
         * @returns a ColorSet with the colors, and with the provided n
         */
        ColorSet getColors(unsigned int n);

		/**
		 * Parses through colors and returns the subsequent color names.
		 * @param colors the bit_vector of colors to parse through.
		 * @returns a vector of color names.
		 */
		vector<string> getColorNames(bit_vector colors);

        /// Returns the number of colors in the ColorManager
        unsigned int getNumColors();

    private:
        /// The pointer to the file handle of the color file
        ifstream* colorFile;

        GraphBuilder* graphBuilder;

        /// colors is where each Color is located.
        /// @key is of type int and represents the id of the Color.
        /// @value is of type shared_ptr<Color>.
        map<int, shared_ptr<Color> > colors;

        /// numColors is the total number of colors added.
        /// It also determines the ID of each Color.
        unsigned int numColors;

};

#endif // COLOR_MANAGER_H
