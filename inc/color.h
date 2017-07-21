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

#include "fm_index.h"
#include "dbg_query.h"

using std::string;
using std::pair;
using std::vector;

class Color {

    public:
        Color(int id, string name, string pathToFMIndex);

        ~Color();

        /*
         * The following methods are wrappers around the methods found in DBGQuery.
         */
        
        /// Returns whether or not s is a vertex of the color 
        bool isVertex(string& s) const;

        /// Returns whether or not there is an outgoing edge, b, present for node s
        bool isPrefixNeighbor(string& s, char b) const;

        /// Returns whether or not there is an incoming edge, b, present for node s
        bool isSuffixNeighbor(string& s, char b) const;

        /// Returns the outgoing edges of s as a vector of kmers that are each outgoing edge
        vector<string> getSuffixNeighbors(string s) const;

        /// Returns the incoming edges of s as a vector of kmers that are each incoming edge
        vector<string> getPrefixNeighbors(string& s) const;

        /// Returns whether or not a node has suffix neighbors
        bool hasSuffixNeighbors(string& s) const;

        /// Returnes whether or not a node has prefix neighbors
        bool hasPrefixNeighbors(string& s) const;

        /**
         * Get the substring and index of a substring in the color.
         * @param idx the position of where the substring begins
         * @param len how long the substring is
         * @return a pair, where first is the substring at idx of length len, and second is 
         * the index of the substring
         */
        pair<string, size_t> extractSubstringAndIndex(size_t idx, size_t len) const;

        /// Returns the substring at index for a certain length
        string extractSubstring(size_t idx, size_t len) const;

        /*
         * Getters
         */

        /// Return the name of the color
        string getName() const;

        /// Return the ID of the color
        int getID() const;

        /// Return the FMIndex of the color
        FMIndex* getFMIndex() const;

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
