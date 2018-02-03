/**
 * @class Color
 *
 * Color represents a single sample or species, which make up
 * the colored de Bruijn graph. This class is essentially a wrapper for the
 * DBGQuery class in the dbgfm package.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/21
 *
 */

#ifndef COLOR_H
#define COLOR_H

#include <string>

using std::string;

class Color {

    public:
        Color(uint32_t id, string name);

        /*
         * Getters
         */

        /// Return the name of the color
        string getName() const;

        /// Return the ID of the color
        uint32_t getID() const;

    private:
        /// The name of the color
        string name;

        /// The ID of the color, which is also used as the index of the bit to set in
        /// the bit_vector. For example, if there are 4 colors and the id is 3, then
        /// the bit_vector with only this color in it would be {0, 1, 0, 0}.
        uint32_t id;

};

#endif // COLOR_H
