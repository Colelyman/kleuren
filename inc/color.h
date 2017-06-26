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

#include "fm_index.h"
#include "dbg_query.h"

using std::string;
using std::pair;

class Color {

    public:
        Color(int id, string name, string pathToFMIndex);

        ~Color();

        /*
         * The following methods are wrappers around the methods found in DBGQuery.
         */
        
        /// Returns whether or not s is a vertex of the color 
        bool isVertex(string& s);

        /// Returns whether or not there is an outgoing edge, b, present for node s
        bool isPrefixNeighbor(string& s, char b);

        /// Returns whether or not there is an incoming edge, b, present for node s
        bool isSuffixNeighbor(string& s, char b);

        /// Returns the outgoing edges of s. 
        /// @todo figure out what this really returns
        string getSuffixNeighbors(string& s);

        /// Returns the incoming edges of s. 
        /// @todo figure out what this really returns
        string getPrefixNeighbors(string& s);

        /**
         * Get the substring and index of a substring in the color.
         * @param idx the position of where the substring begins
         * @param len how long the substring is
         * @return a pair, where first is the substring, and second is the index
         */
        pair<string, size_t> extractSubstringAndIndex(size_t idx, size_t len);

        /// Returns the substring at index for a certain length
        string extractSubstring(size_t idx, size_t len);

        /*
         * Getters
         */

        /// Return the name of the color
        string getName();

        /// Return the ID of the color
        int getID();

        /// Return the FMIndex of the color
        FMIndex* getFMIndex();

    private:
        /// The name of the color
        string name;

        /// The ID of the color
        int id;

        /**
         * The pointer to the instance of the FMIndex. This is where
         * all of the data for the color are stored.
         */
        FMIndex* fmIndex;
};

#endif // COLOR_H
