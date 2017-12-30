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

#include <utility>
#include <string>
#include <vector>
#include <sdsl/bit_vectors.hpp>

using std::string;
using std::pair;
using std::vector;
using sdsl::bit_vector;

class Color {

    public:
        Color(int id, string name, string pathToSequence);

		Color(int id, int numColors, string name, string pathToSequence);

        ~Color();

        /*
         * Getters
         */

        /// Return the name of the color
        string getName() const;

        /// Return the ID of the color
        int getID() const;

        /// Return the bitVector of the color
        bit_vector getBitVector() const;

    private:
        /// The name of the color
        string name;

        /// The ID of the color, which is also used as the index of the bit to set in
        /// the bit_vector. For example, if there are 4 colors and the id is 3, then
        /// the bit_vector with only this color in it would be {0, 1, 0, 0}.
        int id;

        /// Represents what the bit_vector for only this color would be.
        bit_vector bitVector;

        /// The path to the sequence file
        string pathToSequence;

};

#endif // COLOR_H
